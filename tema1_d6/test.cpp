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

    M4 = -M4;
    cout << M4 << endl;

    Matrix M5(2, 2), M6(2, 2), M7(2, 2), M8(2, 2), M9(2, 2);
    M5 = 1;
    M6 = 2;
    M7 = 3;

    M8 = M5 + M6;
    M9 = M7 - M7;
    M5 = 0;
    assert(M7 == M8);
    assert(M9 == M5);

    Matrix M10(2, 3), M11(3, 1);
    in >> M10 >> M11;

    Matrix M12(0, 0);
    M12 = M10 * M11;
    cout << M12 << endl;

    Matrix M13(2, 2), M14(2, 2);

    M13 = 2;
    M13 *= 2;
    M14 = 4;
    assert(M13 == M14);

    return 0;
}