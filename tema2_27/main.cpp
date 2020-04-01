#include "DefaultRooms.hpp"
#include <iostream>

using namespace std;

int main() {
    auto *c = new ConferenceRoom(0, 100, {.hasProjector = false, .hasScene = true});
    cout << c->checkAdditionalFeatures({.hasProjector = true, .hasScene = false}) << endl;
    cout << c->checkAdditionalFeatures({.hasProjector = false, .hasScene = false}) << endl;
    cout << c->checkAdditionalFeatures({.hasProjector = false, .hasScene = true}) << endl;

    return 0;
}