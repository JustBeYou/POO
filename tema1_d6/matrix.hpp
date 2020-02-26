#pragma once

#include <cstdint>
#include <vector>
#include <fstream>


// Maybe templates would be a thing here, but it seems like over-engineering

typedef double MatrixElementType;

class Row: public std::vector<MatrixElementType> {
    public:
        friend Row operator+(Row& lhs, Row& rhs);
        friend Row& operator+=(Row& lhs, Row& rhs);

        friend Row operator-(Row& lhs, Row& rhs);
        friend Row& operator-=(Row& lhs, Row& rhs);

        friend Row operator*(Row& lhs, MatrixElementType rhs);
        friend Row operator*(MatrixElementType lhs, Row& rhs);
        friend Row& operator*=(Row& lhs, MatrixElementType rhs);
};

class Matrix {
    typedef std::vector<Row> RowsContainer;

    public:
        Matrix(const uint64_t rowsCount, const uint64_t columnsCount);
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(const MatrixElementType element);

        Row& operator[](const uint64_t i);

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

        friend Matrix operator*(Matrix& lhs, MatrixElementType rhs);
        friend Matrix operator*(MatrixElementType lhs, Matrix& rhs);
        friend Matrix& operator*=(Matrix& lhs, MatrixElementType rhs);

        friend bool operator==(Matrix& lhs, Matrix& rhs);
        friend bool operator!=(Matrix& lhs, Matrix& rhs);

        friend Matrix operator~(Matrix& matrix);

    private:
        uint64_t columnsCount, rowsCount;
        RowsContainer rows;
};
