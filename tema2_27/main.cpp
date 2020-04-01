#include "DefaultRooms.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main() {
    shared_ptr<RoomType> c = make_shared<ConferenceRoom>(ConferenceRoom(0, 100, {"test", "test1"}));
    cout << c << endl;
    auto d = c;
    cout << d << endl;

    return 0;
}