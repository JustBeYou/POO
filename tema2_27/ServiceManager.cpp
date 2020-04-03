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
    return freeRooms.cend();
}

ServiceManager::FreeRoomIter ServiceManager::getFreeRoomById(size_t id) const {
    for (FreeRoomIter it = freeRooms.cbegin(); it != freeRooms.cend(); ++it) {
        if ((*it)->getId() == id) return it;
    }

    return freeRooms.cend();
}

bool ServiceManager::checkIfRoomIsUsable(FreeRoomIter& room, size_t request, const std::vector<std::string>& features) const {
    return (*room)->isFree(request) and (*room)->checkAdditionalFeatures(features);
}

ServiceManager::FreeRoomIter ServiceManager::getFreeRoomIter() const {
    return freeRooms.cbegin();
}

void ServiceManager::occupyRoom(FreeRoomIter& room) {
    size_t unusedSpace = (*room)->getUnusedSpace();
    (*room)->occupy();
    
    for (auto feature: (*room)->getFeatures()) {
        featuresCount[feature].roomsCount -= 1;
        featuresCount[feature].spaceCount -= unusedSpace;
    }
    totalAvailableSpace -= unusedSpace;
    totalUsedSpace += unusedSpace;
    
    freeRooms.erase(room);
}

void ServiceManager::occupyRoom(FreeRoomIter& room, size_t request) {
    (*room)->occupyBy(request);
    totalAvailableSpace -= request;
    totalUsedSpace += request;
    for (auto feature: (*room)->getFeatures()) {
        featuresCount[feature].spaceCount -= request;
    }

    if ((*room)->isFree(1) == false) {
        for (auto feature: (*room)->getFeatures()) {
            featuresCount[feature].roomsCount -= 1;
        }
        freeRooms.erase(room);
    }
}

void ServiceManager::freeRoom(size_t id) {
    throw std::runtime_error("Not implemented!");
}

void ServiceManager::freeRoom(size_t id, size_t request) {
    std::shared_ptr<RoomType> room = nullptr;
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (id == (*it)->getId()) {
            room = *it;
            break;
        }
    }

    if (room == nullptr) {
        throw std::logic_error("Room not found!");
    }

    if (room->isFree(1)) {
        room->freeBy(request);
        for (auto feature: room->getFeatures()) {
                featuresCount[feature].spaceCount += request;
        }
    } else {
        room->freeBy(request);
        if (room->isFree(1)) {
            for (auto feature: room->getFeatures()) {
                featuresCount[feature].spaceCount += request;
                featuresCount[feature].roomsCount += 1;
            }
            freeRooms.push_back(room);
        }
    }

    totalUsedSpace -= request;
    totalAvailableSpace += request;
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