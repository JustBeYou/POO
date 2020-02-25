#include <iostream>
#include <cstdlib>
#include "matrix.hpp"

using namespace std;

int main() {
    freopen("to_solve.in", "r", stdin);

    uint64_t A_rows, A_cols;
    cin >> A_rows >> A_cols;

    Matrix A(A_rows, A_cols);
    cin >> A;

    uint64_t B_rows, B_cols;
    cin >> B_rows >> B_cols;
    
    Matrix B(B_rows, B_cols);
    cin >> B;

    Matrix X(0, 0);
    X = -B;

    cout << X << endl;
}