#include "RoomType.hpp"
#include <stdexcept>

// Blank state is invalid to use
RoomType::RoomType(): 
    id(INVALID_ROOM_ID),
    availableSpace(0),
    splittable(false),
    usedSpace(1) {}

RoomType::RoomType(const size_t id, const size_t availableSpace, const bool splitable):
    id(id),
    availableSpace(availableSpace),
    splittable(splittable),
    usedSpace(0) {}

void RoomType::occupyBy(const size_t people) {
    if (not canOccupyBy(people)) throw std::logic_error("Not enough space in the room.");
    usedSpace += people; 
}

void RoomType::freeBy(const size_t people) {
    checkInvalidState();
    if (not splittable and people < usedSpace) throw std::logic_error("Can't partially free a non-splittable room.");
    if (people > usedSpace) throw std::logic_error("Trying to free more than existing in the room.");
    usedSpace -= people;
}

bool RoomType::canOccupyBy(const size_t people) const {
    checkInvalidState();
    if (not splittable and usedSpace > 0) return false;
    if (usedSpace + people > availableSpace) return false;
    return true; 
}

void RoomType::occupy() {
    if (not canOccupyBy(availableSpace - usedSpace)) throw std::logic_error("Room already in use.");
    occupyBy(availableSpace - usedSpace);
}

void RoomType::free() {
    if (isFree()) throw std::logic_error("Room already free.");
    freeBy(usedSpace);
}

bool RoomType::isFree() const {
    checkInvalidState();
    return usedSpace == 0;
}

size_t RoomType::getId() const {
    checkInvalidState();
    return id;
}

void RoomType::checkInvalidState() const {
    if (id == INVALID_ROOM_ID) throw std::logic_error("Object is not initialized properly.");
}

bool RoomType::checkAdditionalFeatures() const {
    throw std::logic_error("No additional features.");
    return false;
}