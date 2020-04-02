#include "DefaultRooms.hpp"
#include "ServiceManager.hpp"
#include "Hotel.hpp"
#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

int main() {
    ifstream in("hotel.txt");

    Hotel hotel;
    in >> hotel;
    //cout << hotel;

    size_t commands;
    in >> commands;
    for (size_t i = 0; i < commands; ++i) {
        string action;
        in >> action;

        if (action == "BOOKING") {
            size_t days, services;
            in >> days >> services;

            BookingsCotainer requestedServices;
            for (size_t j = 0; j < services; ++j) {
                string serviceName;
                size_t people, featuresCount;
                in >> serviceName >> people >> featuresCount;

                vector<string> features;
                for (size_t k = 0; k < featuresCount; ++k) {
                    string featureName;
                    in >> featureName;
                    features.push_back(featureName);
                }

                requestedServices[serviceName] = {people, days, features};
            }
        } else if (action == "CANCEL") {
            size_t reservationId;
            in >> reservationId;
        }
    }

    return 0;
}