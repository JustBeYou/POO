#include "Hotel.hpp"

#include <iostream>
const Booking& Hotel::book(const BookingCotainer& booking) {
    size_t streak = 0;
    for (size_t i = 0; i < daysInAYear; ++i) {
        bool valid = true;
        for (auto service: booking.services) {
            bool seemsAvailable = servicesPerDay[i].at(service.first).checkIfSeemsAvailable(service.second.people, service.second.features);
            valid = valid and seemsAvailable;
        }

        if (valid) {
            streak++;
            if (streak == booking.days) {
                Booking solution = {INVALID_BOOKING_ID, {}, 0, i - booking.days};
                internalBook(booking, i - booking.days, solution);

                if (solution.id != INVALID_BOOKING_ID) return bookings[solution.id];

                //std::cout << "Found streak on day: " << i << std::endl;
                streak = 0;
            } 
        } else {
            streak = 0;
        }
    }

    return invalidBooking;
}

void Hotel::internalBook(const BookingCotainer& booking, size_t day, Booking& solution) {
    bool done = true;
    for (auto service: booking.services) {
        done = done and (service.second.people == 0);
    }
    if (done) {
        solution.id = currentBookingId++;
        bookings[solution.id] = solution;
        return ;
    }

    // TODO actual backtracking
}

void Hotel::unbook(size_t id) {

}

std::istream& operator>>(std::istream& in, Hotel& hotel) {
    std::getline(in, hotel.name);
    size_t serviceCount;
    in >> serviceCount;

    for (size_t i = 0; i < serviceCount; ++i) {
        ServiceManager manager; 
        in >> manager;
        hotel.services[manager.getName()] = manager;
    }

    for (size_t i = 0; i < hotel.daysInAYear; ++i) {
        hotel.servicesPerDay.push_back(hotel.services);
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