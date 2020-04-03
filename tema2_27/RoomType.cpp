#include "RoomType.hpp"
#include <stdexcept>

// Blank state is invalid to use
RoomType::RoomType(): 
    id(INVALID_ROOM_ID),
    availableSpace(0),
    splittable(false),
    usedSpace(1),
    hasFeatures(false) {}

RoomType::RoomType(const size_t id, const size_t availableSpace, const bool splittable):
    id(id),
    availableSpace(availableSpace),
    splittable(splittable),
    usedSpace(0),
    hasFeatures(false) {}

RoomType::RoomType(const size_t id, const size_t availableSpace, const bool splittable, const std::vector<std::string>& features):
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

bool RoomType::isFree(size_t request) const {
    checkInvalidState();
    if (splittable and request + usedSpace <= availableSpace) return true;
    if (not splittable and isFree()) return true;
    return false;
}

size_t RoomType::getId() const {
    checkInvalidState();
    return id;
}

void RoomType::checkInvalidState() const {
    if (id == INVALID_ROOM_ID) throw std::logic_error("Object is not initialized properly.");
}

bool RoomType::hasAnyFeature() const {
    return hasFeatures;
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

size_t RoomType::getAvailableSpace() const {
    return availableSpace;
}

size_t RoomType::getUnusedSpace() const {
    return availableSpace - usedSpace;
}

const std::set<std::string>& RoomType::getFeatures() const {
    return features;
}

void RoomType::read(std::istream& in) {
    throw std::logic_error("Read should not be called in RoomType!");
}

void RoomType::write(std::ostream& out) {
    throw std::logic_error("Write should not be called in RoomType!");
}

RoomType* RoomType::clone() const {
    throw std::logic_error("Clone should not be called in RoomType!");
    return nullptr;
}

bool RoomType::isSplittable() const {
    return splittable;
}