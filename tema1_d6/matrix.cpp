#include <cstdint>
#include <vector>
#include <fstream>

#include "matrix.hpp"

Matrix::Matrix(const uint64_t rowsCount, const uint64_t columnsCount): rowsCount(rowsCount), columnsCount(columnsCount) {
	this->rows.resize(rowsCount);
	for (auto& row: this->rows) {
		row.resize(columnsCount);
	}
}

// Assignment operator and copy constructor shares the same code 
// because std::vector handles the memory
Matrix::Matrix(const Matrix& other) {
	this->rowsCount = other.rowsCount;
	this->columnsCount = other.columnsCount;
	this->rows = other.rows;
}

Matrix& Matrix::operator=(const Matrix& other) {
	this->rowsCount = other.rowsCount;
	this->columnsCount = other.columnsCount;
	this->rows = other.rows;

	return *this;
}

Matrix& Matrix::operator=(const ElementType element) {
	for (auto& column: this->rows) {
		std::fill(column.begin(), column.end(), element);
	}

	return *this;
}


Matrix::Row& Matrix::operator[](const uint64_t i) {
	return this->rows[i];
}


std::istream& operator>>(std::istream& in, Matrix& out) {
	for (auto& row: out.rows) {
		for (auto& elem: row) {
			in >> elem;
		}
	}

	return in;
}

std::ostream& operator<<(std::ostream& out, Matrix& in) {
	for (auto& row: in.rows) {
		for (auto& elem: row) {
			out << elem << " ";
		}
		out << std::endl;
	}

	return out;
}


void Matrix::scale(const uint64_t rowsCount, const uint64_t columnsCount) {
	this->rows.resize(rowsCount);
	for (auto& row: this->rows) {
		row.resize(columnsCount);
	}

	this->rowsCount = rowsCount;
	this->columnsCount = columnsCount;
}


uint64_t getColumnsCount(Matrix& matrix) {
	return matrix.columnsCount;
}

uint64_t getRowsCount(Matrix& matrix) {
	return matrix.rowsCount;
}

uint64_t getElementsCount(Matrix& matrix) {
	return matrix.rowsCount * matrix.columnsCount;
}

