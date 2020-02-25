#include <iostream>
#include <cassert>
#include <cstdint>

#include "matrix.hpp"

using namespace std;

int main() {
    Matrix M1(10, 10);
    
    M1 = 123;
    for (uint64_t i = 0; i < 10; i++) {
        for (uint64_t j = 0; j < 10; j++) {
            assert(M1[i][j] == 123);
        }
    }

    M1[0][0] = 321;
    assert(M1[0][0] == 321);

    Matrix M2(M1);
    assert(M2[0][0] == M1[0][0]);

    Matrix M3(1, 1);
    M3 = M1;
    assert(M3[0][0] == M1[0][0]);

    ifstream in("matrix.in");
    Matrix M4(3, 3);
    in >> M4;
    cout << M4 << endl;

    assert(getElementsCount(M4) == 9);
    M4.scale(9, 9);
    assert(getElementsCount(M4) == 81);

    return 0;
}