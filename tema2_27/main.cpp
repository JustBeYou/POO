#include "DefaultRooms.hpp"
#include "ServiceManager.hpp"
#include <iostream>
#include <memory>

using namespace std;

int main() {
    shared_ptr<RoomType> c = make_shared<ConferenceRoom>(ConferenceRoom(0, 100, {"test", "test1"}));
    vector<shared_ptr<RoomType>> v({c});
    ServiceManager mgr(v);

    return 0;
}