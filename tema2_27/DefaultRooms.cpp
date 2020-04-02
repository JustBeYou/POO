#include "DefaultRooms.hpp"
#include <stdexcept>

void BedRoom::read(std::istream& in) {
    in >> id;
}

void BedRoom::write(std::ostream& out) {
    out << "Bedroom #" << id << " : " << usedSpace << "/" << availableSpace << std::endl; 
}

RoomType* BedRoom::clone() const {
    return new BedRoom(*this);
}

void Apartment::read(std::istream& in) {
    in >> id;
}

void Apartment::write(std::ostream& out) {
    out << "Apartment #" << id << " : " << usedSpace << "/" << availableSpace << std::endl; 
}

RoomType* Apartment::clone() const {
    return new Apartment(*this);
}

void Restaurant::read(std::istream& in) {
    in >> id >> availableSpace;
}

void Restaurant::write(std::ostream& out) {
    out << "Restaurant #" << id << " : " << usedSpace << "/" << availableSpace << std::endl; 
}

RoomType* Restaurant::clone() const {
    return new Restaurant(*this);
}

void ConferenceRoom::read(std::istream& in) {
    in >> id >> availableSpace;
    size_t featuresCount;
    in >> featuresCount;
    for (size_t i = 0; i < featuresCount; ++i) {
        std::string feature;
        in >> feature;
        features.insert(feature);
    }
}

void ConferenceRoom::write(std::ostream& out) {
    out << "Conference room #" << id << " : " << usedSpace << "/" << availableSpace << std::endl;
    out << "Features: " << std::endl;
    for (auto it: features) {
        out << " - " << it << std::endl;
    }
}

RoomType* ConferenceRoom::clone() const {
    return new ConferenceRoom(*this);
}

std::shared_ptr<RoomType> DefaultRoomFactory::operator()(const std::string& type) const {
    if (type == "BEDROOM") {
        return std::make_shared<BedRoom>(INVALID_ROOM_ID);
    } else if (type == "APARTMENT") {
        return std::make_shared<Apartment>(INVALID_ROOM_ID);
    } else if (type == "RESTAURANT") {
        return std::make_shared<Restaurant>(INVALID_ROOM_ID, 0);
    } else if (type == "CONFERENCE_ROOM") {
        return std::make_shared<ConferenceRoom>(INVALID_ROOM_ID, 0);
    }

    throw std::runtime_error("Unknown room type!");
}