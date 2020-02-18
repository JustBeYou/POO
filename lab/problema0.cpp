#include <iostream>
#include <cstdint>

using namespace std;

uint64_t sum(uint64_t a, uint64_t b) {
    return a + b;
}

int main() {
    uint64_t a, b;
    cin >> a >> b;
    cout << sum(a, b) << endl;

    return 0;
}