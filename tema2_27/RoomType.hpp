#pragma once

#include <cstddef>

#define INVALID_ROOM_ID 0 

class RoomType {
    public:
    RoomType();
    RoomType(const size_t id, const size_t availableSpace, const bool splittable);
    void occupyBy(const size_t people);
    void freeBy(const size_t people);
    bool canOccupyBy(const size_t people) const;
    void occupy();
    void free();
    bool isFree() const;
    size_t getId() const;

    bool checkAdditionalFeatures() const;

    protected:
    size_t id;
    size_t availableSpace;
    size_t usedSpace;
    bool splittable;

    private:
    void checkInvalidState() const;
};