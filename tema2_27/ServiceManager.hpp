#pragma once

#include "RoomType.hpp"

#include <vector>
#include <memory>
#include <map>
#include <list>

class ServiceManager {
    typedef std::list<std::shared_ptr<RoomType>>::const_iterator FreeRoomIter;

    public:
    ServiceManager();
    ServiceManager(const std::vector<std::shared_ptr<RoomType>>& rooms);
    bool checkIfSeemsAvailable(const size_t requestedSpace, const std::vector<std::string>& features) const;
    
    bool checkIfRoomIsUsable(FreeRoomIter& room, size_t request, const std::vector<std::string>& features) const;
    FreeRoomIter getFreeRoomEnd() const;
    FreeRoomIter getRoom(size_t id) const;
    FreeRoomIter getFreeRoomIter() const;
    void occupyRoom(FreeRoomIter& room);
    void occupyRoom(FreeRoomIter& room, size_t request);
    std::string getName() const;

    friend std::istream& operator>>(std::istream& in, ServiceManager& manager);
    friend std::ostream& operator<<(std::ostream& out, ServiceManager& manager);

    private:
    void init(const std::vector<std::shared_ptr<RoomType>>& rooms);

    struct FeaturesCountStore {
        size_t spaceCount;
        size_t roomsCount;
    };

    std::vector<std::shared_ptr<RoomType>> rooms;
    std::list<std::shared_ptr<RoomType>> freeRooms;
    size_t totalAvailableSpace;
    size_t totalUsedSpace;
    std::map<std::string, FeaturesCountStore> featuresCount;
    std::string name;
};