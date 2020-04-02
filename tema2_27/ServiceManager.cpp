#include "ServiceManager.hpp"
#include "DefaultRooms.hpp"

ServiceManager::ServiceManager() {
    totalUsedSpace = totalAvailableSpace = 0;
}

ServiceManager::ServiceManager(const std::vector<std::shared_ptr<RoomType>>& rooms) {
    init(rooms);
}

#include <iostream>
ServiceManager::ServiceManager(const ServiceManager &other) {
    //std::cout << "COPY!!!" << std::endl;
    operator=(other);
}

ServiceManager& ServiceManager::operator=(const ServiceManager& other) {
    init(other.rooms);
    return *this;
}

//#include <iostream>

void ServiceManager::init(const std::vector<std::shared_ptr<RoomType>>& rooms) {
    totalUsedSpace = 0;
    for (auto roomPtr: rooms) {
        std::shared_ptr<RoomType> copyRoomPtr(roomPtr->clone());
        //std::cout << roomPtr << " " << copyRoomPtr << std::endl;
        //std::cout << "c: " << dynamic_cast<BedRoom*>(roomPtr.get()) << " " << dynamic_cast<BedRoom*>(copyRoomPtr.get()) << std::endl;
        this->rooms.push_back(copyRoomPtr);
        this->freeRooms.push_back(copyRoomPtr);
        totalAvailableSpace += roomPtr->getAvailableSpace();
        for (auto feature: roomPtr->getFeatures()) {
            featuresCount[feature].roomsCount += 1;
            featuresCount[feature].spaceCount += roomPtr->getAvailableSpace();
        }
    }
}

bool ServiceManager::checkIfSeemsAvailable(const size_t requestedSpace, const std::vector<std::string>& features) const {
    if (requestedSpace + totalUsedSpace > totalAvailableSpace) return false;
    for (auto feature: features) {
        if (featuresCount.at(feature).roomsCount == 0 or featuresCount.at(feature).spaceCount < requestedSpace) return false;
    }
    
    return true;
}

ServiceManager::FreeRoomIter ServiceManager::getFreeRoomEnd() const {
    return freeRooms.end();
}

ServiceManager::FreeRoomIter ServiceManager::getRoom(size_t id) const {
    for (FreeRoomIter it = freeRooms.begin(); it != freeRooms.end(); ++it) {
        if ((*it)->getId() == id) return it;
    }

    return freeRooms.end();
}

bool ServiceManager::checkIfRoomIsUsable(FreeRoomIter& room, size_t request, const std::vector<std::string>& features) const {
    return (*room)->isFree(request) and (*room)->checkAdditionalFeatures(features);
}

ServiceManager::FreeRoomIter ServiceManager::getFreeRoomIter() const {
    return freeRooms.cbegin();
}

void ServiceManager::occupyRoom(FreeRoomIter& room) {
    (*room)->occupy();
    freeRooms.erase(room);
}

void ServiceManager::occupyRoom(FreeRoomIter& room, size_t request) {
    (*room)->occupyBy(request);
    if ((*room)->isFree(1) == false) {
        freeRooms.erase(room);
    }
}

std::string ServiceManager::getName() const { 
    return name;
}

std::istream& operator>>(std::istream& in, ServiceManager& manager) {
    in >> manager.name;
    size_t roomsCount;
    in >> roomsCount;

    DefaultRoomFactory factory;
    std::vector<std::shared_ptr<RoomType>> rooms;
    for (size_t i = 0; i < roomsCount; ++i) {
        std::string roomType;
        in >> roomType;
        std::shared_ptr<RoomType> newRoom = factory(roomType);
        //std::cout << roomType << " " << newRoom << std::endl; 
        in >> (*newRoom);
        rooms.push_back(newRoom);
    }
    manager.init(rooms);
    
    return in;
}

std::ostream& operator<<(std::ostream& out, ServiceManager& manager) {
    out << manager.name << " has " << manager.rooms.size() << " rooms." << std::endl;
    for (auto it: manager.rooms) {
        out << (*it);
    }

    return out;
}