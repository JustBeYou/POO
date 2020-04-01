#pragma once

#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>

#define INVALID_ROOM_ID 0 

class RoomType {
    public:
    RoomType();
    RoomType(const size_t id, const size_t availableSpace, const bool splittable);
    RoomType(const size_t id, const size_t availableSpace, const bool splittable, const std::vector<std::string>& features);
    RoomType(const RoomType& other);
    void occupyBy(const size_t people);
    void freeBy(const size_t people);
    bool canOccupyBy(const size_t people) const;
    void occupy();
    void free();
    bool isFree() const;
    size_t getId() const;
    size_t getAvailableSpace() const;
    const std::set<std::string>& getFeatures() const;
    RoomType& operator=(const RoomType& rhs);

    bool checkAdditionalFeatures(const std::vector<std::string>& features) const;

    virtual void read(std::istream& in);
    virtual void write(std::ostream& out);
    virtual RoomType* clone() const;

    friend std::ostream& operator<<(std::ostream& out, RoomType& rhs);
    friend std::istream& operator>>(std::istream& in, RoomType& rhs); 

    protected:
    size_t id;
    size_t availableSpace;
    size_t usedSpace;
    bool splittable;
    bool hasFeatures;
    std::set<std::string> features;

    private:
    void checkInvalidState() const;
};