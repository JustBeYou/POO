#include "DefaultRooms.hpp"

void BedRoom::read(std::istream& in) {
    in >> id;
}

void BedRoom::write(std::ostream& out) {
    out << "Bedroom #" << id << " : " << usedSpace << "/" << availableSpace << std::endl; 
}

void Apartment::read(std::istream& in) {
    in >> id;
}

void Apartment::write(std::ostream& out) {
    out << "Apartment #" << id << " : " << usedSpace << "/" << availableSpace << std::endl; 
}

void Restaurant::read(std::istream& in) {
    in >> id >> availableSpace;
}

void Restaurant::write(std::ostream& out) {
    out << "Restaurant #" << id << " : " << usedSpace << "/" << availableSpace << std::endl; 
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