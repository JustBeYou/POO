#include "ServiceManager.hpp"

ServiceManager::ServiceManager(const std::vector<std::shared_ptr<RoomType>>& rooms) {
    totalUsedSpace = 0;
    for (auto roomPtr: rooms) {
        this->rooms.push_back(std::make_shared<RoomType>(*roomPtr));
        totalAvailableSpace += roomPtr->getAvailableSpace();
        for (auto feature: roomPtr->getFeatures()) {
            featuresCount[feature] += 1;
        }
    }
}

bool ServiceManager::checkIfAvailable(const size_t requestedSpace, const std::vector<std::string>& features) const {
    return false;
}


bool ServiceManager::checkIfRoomIsUsable() const {

}

size_t ServiceManager::getFreeRoom() const {

}

size_t ServiceManager::occupyRoom(size_t id) {

}

