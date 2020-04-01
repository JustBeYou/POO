#include "RoomType.hpp"
#include <stdexcept>

// Blank state is invalid to use
RoomType::RoomType(): 
    id(INVALID_ROOM_ID),
    availableSpace(0),
    splittable(false),
    usedSpace(1),
    hasFeatures(false) {}

RoomType::RoomType(const size_t id, const size_t availableSpace, const bool splitable):
    id(id),
    availableSpace(availableSpace),
    splittable(splittable),
    usedSpace(0),
    hasFeatures(false) {}

RoomType::RoomType(const size_t id, const size_t availableSpace, const bool splitable, const std::vector<std::string>& features):
    id(id),
    availableSpace(availableSpace),
    splittable(splittable),
    usedSpace(0),
    hasFeatures(true) {

    for (auto it: features) {
        this->features.insert(it);
    }
}

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

bool RoomType::checkAdditionalFeatures(const std::vector<std::string>& features) const {
    if (not hasFeatures) throw std::logic_error("No additional features.");
    for (auto it: features) {
        if (this->features.find(it) == this->features.end()) return false;
    }
    return true;
}

RoomType& RoomType::operator=(const RoomType& rhs) {
    id = rhs.id;
    availableSpace = rhs.availableSpace;
    usedSpace = rhs.usedSpace;
    splittable = rhs.splittable;
    hasFeatures = rhs.hasFeatures;
    features = rhs.features;
    return *this;
}

RoomType::RoomType(const RoomType& other) {
    operator=(other);
}

std::ostream& operator<<(std::ostream& out, RoomType& rhs) {
    rhs.write(out);
    return out;
}

std::istream& operator>>(std::istream& in, RoomType& rhs) {
    rhs.read(in);
    return in; 
}