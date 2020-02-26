#include <iostream>
#include <cstdlib>
#include <cassert>
#include "matrix.hpp"

using namespace std;

int main() {
    cout << "Solver for A * X + B = 0" << endl;
    //freopen("to_solve.in", "r", stdin);

    cout << "A(rows, columns) = ";
    uint64_t A_rows, A_cols;
    cin >> A_rows >> A_cols;

    cout << "A = " << endl;
    Matrix A(A_rows, A_cols);
    cin >> A;

    cout << "B(rows, columns) = ";
    uint64_t B_rows, B_cols;
    cin >> B_rows >> B_cols;
    
    cout << "B = " << endl;
    Matrix B(B_rows, B_cols);
    cin >> B;

    Matrix X(0, 0);
    X = -B;

    Matrix A_inverse(~A);
    X = A_inverse * X;

    cout << "X = " << endl;
    cout << X << endl;
    
    return 0;
}