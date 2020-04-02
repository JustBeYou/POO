#pragma once

#include <fstream>
#include <string>
#include <map>
#include <list>
#include "ServiceManager.hpp"

#define INVALID_BOOKING_ID 0

struct Booking {
    size_t id;
    std::map<std::string, std::list<size_t>> services; // each service has a list of room ids
    size_t days;
    size_t startDay;
};


struct BookingOptions {
    size_t people;
    std::vector<std::string> features;
};

struct BookingCotainer {
    size_t days;
    std::map<std::string, BookingOptions> services;
};

class Hotel {
    public:
    const Booking& book(const BookingCotainer& booking);
    void unbook(size_t id);
    friend std::istream& operator>>(std::istream& in, Hotel& hotel);
    friend std::ostream& operator<<(std::ostream& out, Hotel& hotel);

    private:
    void internalBook(const BookingCotainer& booking, size_t day, Booking& solution);

    const size_t daysInAYear = 365;
    std::string name;
    std::map<std::string, ServiceManager> services;
    std::vector<std::map<std::string, ServiceManager>> servicesPerDay;
    size_t currentBookingId = 1;
    Booking invalidBooking = {INVALID_BOOKING_ID, {}, 0, 0};
    std::map<size_t, Booking> bookings;

};