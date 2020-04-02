#pragma once

#include <fstream>
#include <string>
#include <map>
#include <list>
#include "ServiceManager.hpp"

struct Booking {
    std::map<std::string, std::list<size_t>> services; // each service has a list of room ids
    size_t days;
};

class Hotel {
    public:
    friend std::istream& operator>>(std::istream& in, Hotel& hotel);
    friend std::ostream& operator<<(std::ostream& out, Hotel& hotel);

    private:
    std::string name;
    std::map<std::string, ServiceManager> services;
};

struct BookingOptions {
    size_t people;
    size_t days;
    std::vector<std::string> features;
};

typedef std::map<std::string, BookingOptions> BookingsCotainer;