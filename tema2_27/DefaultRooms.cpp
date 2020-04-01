#include "DefaultRooms.hpp"

// Blank state
Bedroom::Bedroom(): RoomType(INVALID_ROOM_ID, 2, false) {}
Apartment::Apartment(): RoomType(INVALID_ROOM_ID, 4, false) {}
Restaurant::Restaurant(): RoomType(INVALID_ROOM_ID, 0, true) {}
ConferenceRoom::ConferenceRoom(): RoomType(INVALID_ROOM_ID, 0, true) {}

Bedroom::Bedroom(const size_t id): RoomType(id, 2, false) {}
Apartment::Apartment(const size_t id): RoomType(id, 4, false) {}
Restaurant::Restaurant(const size_t id, const size_t availableSpace): RoomType(id, availableSpace, true) {}
ConferenceRoom::ConferenceRoom(const size_t id, const size_t availableSpace, const ConferenceRoomFeatures& features): 
    RoomType(id, availableSpace, true) {

    this->features.hasProjector = features.hasProjector;
    this->features.hasScene = features.hasScene;
}
bool ConferenceRoom::checkAdditionalFeatures(const ConferenceRoomFeatures& features) const {
    bool valid = true;
    if (features.hasProjector) valid = valid and this->features.hasProjector;
    if (features.hasScene) valid = valid and this->features.hasScene;
    return valid;
}
