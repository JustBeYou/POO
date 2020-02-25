#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>

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

// Some things may seem code duplicate, but it's the cleanest way without
// wasting additional memory or doing useless loops multiple times
Matrix operator+(Matrix& matrix) {
	return matrix;
}

Matrix operator-(Matrix& matrix) {
	Matrix opposite(matrix);
	for (auto& row: opposite.rows) {
		for (auto& element: row) {
			element = -element;
		}
	}

	return opposite;
}

void checkIfSameDimensions(Matrix& lhs, Matrix& rhs) {
	if (lhs.rowsCount != rhs.rowsCount || lhs.columnsCount != rhs.columnsCount) {
		throw std::invalid_argument("Matrix dimensions differ");
	}
}

Matrix operator+(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	Matrix result(lhs.rowsCount, lhs.columnsCount);
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (int64_t j = 0; j < lhs.columnsCount; j++) {
			result[i][j] = lhs[i][j] + rhs[i][j];
		}
	}

	return result;
}

Matrix& operator+=(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (int64_t j = 0; j < lhs.columnsCount; j++) {
			lhs[i][j] += rhs[i][j];
		}
	}

	return lhs;
}

Matrix operator-(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	Matrix result(lhs.rowsCount, lhs.columnsCount);
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (int64_t j = 0; j < lhs.columnsCount; j++) {
			result[i][j] = lhs[i][j] - rhs[i][j];
		}
	}

	return result;
}
Matrix& operator-=(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (int64_t j = 0; j < lhs.columnsCount; j++) {
			lhs[i][j] -= rhs[i][j];
		}
	}

	return rhs;
}

void checkIfCanMultiply(Matrix& lhs, Matrix& rhs) {
	if (lhs.columnsCount != rhs.rowsCount) {
		throw std::invalid_argument("Columns of the first matrix should match the rows of the second matrix");
	}
}

Matrix operator*(Matrix& lhs, Matrix& rhs) {
	checkIfCanMultiply(lhs, rhs);

	Matrix result(lhs.rowsCount, rhs.columnsCount);
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (uint j = 0; j < rhs.columnsCount; j++) {
			Matrix::ElementType temporaryResult = 0;
			
			for (uint k = 0; k < lhs.columnsCount; k++) {
				temporaryResult += lhs[i][k] * rhs[k][j];
			}

			result[i][j] = temporaryResult;
		}
	}

	return result;
}

Matrix& operator*=(Matrix& lhs, Matrix& rhs) {
	lhs = lhs * rhs;
	return lhs;
}

Matrix operator*(Matrix& lhs, Matrix::ElementType rhs) {
	Matrix result(lhs.rowsCount, lhs.columnsCount);
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (int64_t j = 0; j < lhs.columnsCount; j++) {
			result[i][j] = lhs[i][j] * rhs;
		}
	}

	return result;
}

Matrix& operator*=(Matrix& lhs, Matrix::ElementType rhs) {
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (int64_t j = 0; j < lhs.columnsCount; j++) {
			lhs[i][j] *= rhs;
		}
	}

	return lhs;
}

bool operator==(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	bool allEqual = true;
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		for (uint64_t j = 0; j < lhs.columnsCount; j++) {
			allEqual &= lhs[i][j] == rhs[i][j];
		}
	} 

	return allEqual;
}

bool operator!=(Matrix& lhs, Matrix& rhs) {
	return !(lhs == rhs);
}

Matrix operator~(Matrix& matrix) {
	Matrix inverse(matrix.rowsCount, matrix.columnsCount);

	double determinant = matrix.determinant();
}

double Matrix::determinant() {
	if (this->rowsCount != this->columnsCount) {
		throw std::invalid_argument("Only square matrices can have a determinant");
	}

	uint64_t size = this->rowsCount;
	double determinant = 0;

	if (size == 1) {
		return this->rows[0][0];
	}
}
