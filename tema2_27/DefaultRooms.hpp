#pragma once

#include "RoomType.hpp"
#include <cstddef>

class NonSplittableRoom: public RoomType {
    public:
    NonSplittableRoom(size_t id, size_t availableSpace): RoomType(id, availableSpace, false) {}
};

class SplittableRoom: public RoomType {
    public:
    SplittableRoom(size_t id, size_t availableSpace): RoomType(id, availableSpace, true) {}
};

class FeaturesRoom: public RoomType {
    public:
    FeaturesRoom(size_t id, size_t availableSpace, std::vector<std::string> features): 
        RoomType(id, availableSpace, false, features) {}
};

class BedRoom: public NonSplittableRoom {
    public:
    BedRoom(size_t id): NonSplittableRoom(id, 2) {}
    RoomType* clone() const;
    void read(std::istream& in);
    void write(std::ostream& out);
};


class Apartment: public NonSplittableRoom {
    public:
    Apartment(size_t id): NonSplittableRoom(id, 4) {}
    RoomType* clone() const;
    void read(std::istream& in);
    void write(std::ostream& out);
};

class Restaurant: public SplittableRoom {
    public:
    Restaurant(size_t id, size_t availableSpace): SplittableRoom(id, availableSpace) {}
    RoomType* clone() const;
    void read(std::istream& in);
    void write(std::ostream& out);
};

class ConferenceRoom: public FeaturesRoom {
    public:
    ConferenceRoom(size_t id, size_t availableSpace, std::vector<std::string> features): 
        FeaturesRoom(id, availableSpace, features) {}
    RoomType* clone() const;
    void read(std::istream& in);
    void write(std::ostream& out);
};