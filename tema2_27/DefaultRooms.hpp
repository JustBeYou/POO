#pragma once

#include "RoomType.hpp"
#include <cstddef>

class Bedroom: public RoomType {
    public:
        Bedroom();
        Bedroom(const size_t id);
};

class Apartment: public RoomType {
    public:
        Apartment();
        Apartment(const size_t id);
};

class Restaurant: public RoomType {
    public:
        Restaurant();
        Restaurant(const size_t id, const size_t availableSpace);
};

class ConferenceRoom: public RoomType {
    protected:
        struct ConferenceRoomFeatures {
            bool hasProjector;
            bool hasScene;
        } features;

    public:
        ConferenceRoom();
        ConferenceRoom(const size_t id, const size_t availableSpace, const ConferenceRoomFeatures& features);
        bool checkAdditionalFeatures(const ConferenceRoomFeatures& features) const;
};