#include "Hotel.hpp"

std::istream& operator>>(std::istream& in, Hotel& hotel) {
    std::getline(in, hotel.name);
    size_t serviceCount;
    in >> serviceCount;

    for (size_t i = 0; i < serviceCount; ++i) {
        ServiceManager manager; 
        in >> manager;
        hotel.services[manager.getName()] = manager;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, Hotel& hotel) {
    out << "Welcome to the " << hotel.name << std::endl;
    out << "Our services: " << std::endl;
    for (auto it: hotel.services) {
        out << " - " << it.second << std::endl;
    }
    
    return out;
}