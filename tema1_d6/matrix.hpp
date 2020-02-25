#pragma once

#include <cstdint>
#include <vector>
#include <fstream>

class Matrix {
    // Maybe templates would be a thing here, but it's seems like over-engineering
    typedef double ElementType;
    typedef std::vector<ElementType> Row;
    typedef std::vector<Row> RowsContainer;

    public:
        Matrix(const uint64_t rowsCount, const uint64_t columnsCount);
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(const ElementType element);

        Row& operator[](const uint64_t i);

        double determinant();

        friend std::istream& operator>>(std::istream& in, Matrix& out);
        friend std::ostream& operator<<(std::ostream& out, Matrix& in);

        void scale(const uint64_t rowsCount, const uint64_t columnsCount);

        friend uint64_t getColumnsCount(Matrix& matrix);
        friend uint64_t getRowsCount(Matrix& matrix);
        friend uint64_t getElementsCount(Matrix& matrix);

        friend Matrix operator+(Matrix& matrix);
        friend Matrix operator-(Matrix& matrix);

        friend void checkIfSameDimensions(Matrix &lhs, Matrix& rhs);

        friend Matrix operator+(Matrix& lhs, Matrix& rhs);
        friend Matrix& operator+=(Matrix& lhs, Matrix& rhs);
        
        friend Matrix operator-(Matrix& lhs, Matrix& rhs);
        friend Matrix& operator-=(Matrix& lhs, Matrix& rhs);

        friend void checkIfCanMultiply(Matrix& lhs, Matrix& rhs);

        friend Matrix operator*(Matrix& lhs, Matrix& rhs);
        friend Matrix& operator*=(Matrix& lhs, Matrix& rhs);

        friend Matrix operator*(Matrix& lhs, ElementType rhs);
        friend Matrix& operator*=(Matrix& lhs, ElementType rhs);

        friend bool operator==(Matrix& lhs, Matrix& rhs);
        friend bool operator!=(Matrix& lhs, Matrix& rhs);

        friend Matrix operator~(Matrix& matrix);

    private:
        uint64_t columnsCount, rowsCount;
        RowsContainer rows;
};