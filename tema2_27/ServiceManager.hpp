#pragma once

#include "RoomType.hpp"

#include <vector>
#include <memory>
#include <map>

class ServiceManager {
    public:
    ServiceManager(const std::vector<std::shared_ptr<RoomType>>& rooms);
    bool checkIfAvailable(const size_t requestedSpace, const std::vector<std::string>& features) const;
    
    bool checkIfRoomIsUsable() const;
    size_t getFreeRoom() const;
    size_t occupyRoom(size_t id);

    private:
    std::vector<std::shared_ptr<RoomType>> rooms;
    size_t totalAvailableSpace;
    size_t totalUsedSpace;
    std::map<std::string, size_t> featuresCount;
};