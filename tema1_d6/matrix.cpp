#include <cstdint>
#include <vector>
#include <fstream>

#include "matrix.hpp"

Matrix::Matrix(const uint64_t rowsCount, const uint64_t columnsCount): rowsCount(rowsCount), columnsCount(columnsCount) {
	this->rows.resize(rowsCount);
	for (auto row: this->rows) {
		row.resize(columnsCount);
	}
}

// Assignment operator and copy constructor shares the same code 
// as std::vector handles the memory
Matrix::Matrix(const Matrix& other) {
	this->rowsCount = other.rowsCount;
	this->columnsCount = other.columnsCount;
	
	this->rows.resize(this->rowsCount);
	for (uint64_t i = 0; i < this->rowsCount; ++i) {
		this->rows[i].resize(this->columnsCount);
		for (uint64_t j = 0; j < this->columnsCount; ++j) {
			this->rows[i][j] = other.rows[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& other) {
	this->rowsCount = other.rowsCount;
	this->columnsCount = other.columnsCount;
	
	this->rows.resize(this->rowsCount);
	for (uint64_t i = 0; i < this->rowsCount; ++i) {
		this->rows[i].resize(this->columnsCount);
		for (uint64_t j = 0; j < this->columnsCount; ++j) {
			this->rows[i][j] = other.rows[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator=(const ElementType element) {

}


Matrix::Row& Matrix::operator[](const uint64_t i) {

}


std::istream& operator>>(std::istream& in, Matrix& out) {

}

std::ostream& operator<<(std::ostream& out, Matrix& in) {

}


void Matrix::scale(const uint64_t rows, const uint64_t cols) {

}


uint64_t getColumnsCount(Matrix& matrix) {

}

uint64_t getRowsCount(Matrix& matrix) {

}

uint64_t getElementsCount(Matrix& matrix) {

}

