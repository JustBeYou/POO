#pragma once

#include <cstdint>
#include <vector>
#include <fstream>

class Matrix {
    typedef double ElementType;
    typedef std::vector<ElementType> Row;
    typedef std::vector<Row> RowsContainer;

    public:
        Matrix(const uint64_t rowsCount, const uint64_t columnsCount);
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(const ElementType element);

        Row& operator[](const uint64_t i);

        friend std::istream& operator>>(std::istream& in, Matrix& out);
        friend std::ostream& operator<<(std::ostream& out, Matrix& in);

        void scale(const uint64_t rows, const uint64_t cols);

        friend uint64_t getColumnsCount(Matrix& matrix);
        friend uint64_t getRowsCount(Matrix& matrix);
        friend uint64_t getElementsCount(Matrix& matrix);

    private:
        uint64_t columnsCount, rowsCount;
        RowsContainer rows;
};