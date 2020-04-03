#include "Hotel.hpp"

#include <iostream>
#include <stdexcept>

std::ostream& operator<<(std::ostream& out, const Booking& booking) {
    out << "Booking #" << booking.id << ", time period " << booking.startDay << "-" << booking.startDay + booking.days - 1 << ": " << std::endl;
    for (const auto& service: booking.services) {
        const auto& serviceName = service.first;
        const auto& roomIds = service.second;

        out << "For " << serviceName << ": ";
        for (const auto roomId: roomIds) {
            out << roomId.first << " ";
        }
        out << std::endl;
    }
    return out;
}

const Booking& Hotel::book(const BookingCotainer& booking) {
    size_t streak = 0;
    for (size_t i = 0; i < daysInAYear; ++i) {
        bool valid = true;
        for (const auto& service: booking.services) {
            bool seemsAvailable = servicesPerDay[i].at(service.first).checkIfSeemsAvailable(service.second.people, service.second.features);
            valid = valid and seemsAvailable;
        }

        if (valid) {
            streak++;
            if (streak == booking.days) {
                const auto startDay = i - (booking.days - 1);
                Booking solution = {INVALID_BOOKING_ID, {}, booking.days, startDay};
                internalBook(booking, startDay, solution);

                if (solution.id != INVALID_BOOKING_ID) return bookings[solution.id];

                //std::cout << "Found streak on day: " << i << std::endl;
                streak--;
            } 
        } else {
            streak = 0;
        }
    }

    return invalidBooking;
}

void Hotel::internalBook(const BookingCotainer& booking, size_t startDay, Booking& solution) {
    for (const auto& service: booking.services) {
        const auto& serviceName = service.first;
        auto options = service.second;

        //std::cout << serviceName << std::endl;

        std::list<std::pair<size_t, size_t>> freeRoomIds;
        const auto& currentService = servicesPerDay[startDay].at(serviceName);
        auto freeRoomIterBegin = currentService.getFreeRoomIter();
        auto freeRoomIterEnd = currentService.getFreeRoomEnd();
        for (; freeRoomIterBegin != freeRoomIterEnd; ++freeRoomIterBegin) {
            //std::cout << (*freeRoomIterBegin)->getId() << std::endl;

            if (options.features.size() != 0 and ((*freeRoomIterBegin)->hasAnyFeature() == false or
                (*freeRoomIterBegin)->checkAdditionalFeatures(options.features) == false)) continue;

            size_t unusedSpace = (*freeRoomIterBegin)->getUnusedSpace();
            size_t peopleRequest = std::min(unusedSpace, options.people);

            size_t roomId = (*freeRoomIterBegin)->getId();
            bool freeInAllDays = true;
            for (size_t currentDay = startDay; currentDay < startDay + booking.days; ++currentDay) {
                auto &currentService = servicesPerDay[currentDay].at(serviceName);
                auto currentRoom = currentService.getFreeRoomById(roomId);

                if (currentRoom != currentService.getFreeRoomEnd() and
                    (*currentRoom)->isFree(peopleRequest)) {

                    // is free
                    //std::cout << *(*currentRoom) << " found free on day " << currentDay << std::endl; 
                } else {
                    freeInAllDays = false;
                    break;
                }
            }

            if (freeInAllDays) {
                //std::cout << roomId << " found free for booking" << std::endl;
                freeRoomIds.push_back({roomId, peopleRequest});
                options.people -= peopleRequest;
                //std::cout << "remaining: " << options.people << std::endl; 
            }

            if (options.people == 0) {
                break;
            }
        }

        if (options.people == 0) {
            //std::cout << "Request for service " << serviceName << " is fullfilled" << std::endl;
            solution.services[serviceName] = freeRoomIds;
        } else {
            //std::cout << "Request for service " << serviceName << " could not be fullfilled" << std::endl;
            return ;
        }
    }

    solution.id = currentBookingId++;
    bookings[solution.id] = solution;

    for (const auto &service: solution.services) {
        const auto& serviceName = service.first;
        const auto& rooms = service.second;
        for (const auto roomId: rooms) {
            const auto id = roomId.first;
            const auto request = roomId.second;

            for (size_t currentDay = startDay; currentDay < startDay + booking.days; ++currentDay) {
                auto &currentService = servicesPerDay[currentDay].at(serviceName);
                auto roomIter = currentService.getFreeRoomById(id);
                currentService.occupyRoom(roomIter, request);
            }
        }
    }
}

void Hotel::unbook(size_t id) {
    if (bookings.find(id) == bookings.end()) {
        throw std::logic_error("There is no booking with this id!");
    }

    auto &booking = bookings[id];
    for (const auto& service: booking.services) {
        const auto& serviceName = service.first;
        const auto& rooms = service.second;

        for (const auto roomId: rooms) {
            const auto id = roomId.first;
            const auto request = roomId.second;

            for (size_t currentDay = booking.startDay; currentDay < booking.startDay + booking.days; ++currentDay) {
                auto &currentService = servicesPerDay[currentDay].at(serviceName);
                currentService.freeRoom(id, request);
            }
        }
    }

    bookings.erase(id);
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

static size_t hotelDayToShow = 0;

HotelShowDay setHotelDay(size_t day) {
    HotelShowDay obj = {day};
    return obj;
}

std::ostream& operator<<(std::ostream& out, HotelShowDay obj) {
    hotelDayToShow = obj.day;
    return out;
}

std::ostream& operator<<(std::ostream& out, Hotel& hotel) {
    if (hotel.daysInAYear < hotelDayToShow) {
        throw std::logic_error("Non-existent day!");
    }
    
    out << "Welcome to the " << hotel.name << std::endl;
    out << "Our services for day " << hotelDayToShow << " are:" << std::endl;
    for (auto& it: hotel.servicesPerDay[hotelDayToShow]) {
        out << " - " << it.second << std::endl;
    }
    
    return out;
}