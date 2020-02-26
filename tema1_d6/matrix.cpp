#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <functional>

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

Matrix& Matrix::operator=(const MatrixElementType element) {
	for (auto& column: this->rows) {
		std::fill(column.begin(), column.end(), element);
	}

	return *this;
}


Row& Matrix::operator[](const uint64_t i) {
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
		result[i] = lhs[i] + rhs[i];
	}

	return result;
}

Matrix& operator+=(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		lhs[i] += rhs[i];
	}

	return lhs;
}

Matrix operator-(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	Matrix result(lhs.rowsCount, lhs.columnsCount);
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		result[i] = lhs[i] - rhs[i];
	}

	return result;
}
Matrix& operator-=(Matrix& lhs, Matrix& rhs) {
	checkIfSameDimensions(lhs, rhs);

	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		lhs[i] -= rhs[i];
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
		for (uint64_t j = 0; j < rhs.columnsCount; j++) {
			MatrixElementType temporaryResult = 0;
			
			for (uint k = 0; k < lhs.columnsCount; k++) {
				temporaryResult += lhs[i][k] * rhs[k][j];
			}

			result[i][j] = temporaryResult;
		}
	}

	return result;
}

Matrix operator*(MatrixElementType lhs, Matrix& rhs) {
	return rhs * lhs;
}

Matrix& operator*=(Matrix& lhs, Matrix& rhs) {
	lhs = lhs * rhs;
	return lhs;
}

Matrix operator*(Matrix& lhs, MatrixElementType rhs) {
	Matrix result(lhs.rowsCount, lhs.columnsCount);
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		result[i] = lhs[i] * rhs;
	}

	return result;
}

Matrix& operator*=(Matrix& lhs, MatrixElementType rhs) {
	for (uint64_t i = 0; i < lhs.rowsCount; i++) {
		lhs[i] *= rhs;
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
	if (matrix.rowsCount != matrix.columnsCount) {
		throw std::invalid_argument("Only square matrices can be inversed.");
	}
	uint64_t size = matrix.rowsCount;

	Matrix matrixCopy(matrix);
	Matrix inverse(size, size);
	inverse = 0;
	for (uint64_t i = 0; i < size; ++i) {
		inverse[i][i] = 1;
	}

	// I am using Gauss-Jordan algorithm

	// Step 1: Row echelon form
	for (uint64_t i = 0; i < size; ++i) {
		for (uint64_t j = i + 1; j < size; ++j) {
			double factor = matrixCopy[j][i] / matrixCopy[i][i];

			Row eliminationRow = factor * matrixCopy[i];
			matrixCopy[j] -= eliminationRow;

			Row inverseEliminationRow = factor * inverse[i];
			inverse[j] -= inverseEliminationRow;
		}
	}

	// Step 2: Diagonal only
	for (uint64_t i = 0; i < size; ++i) {
		for (uint64_t j = i + 1; j < size; ++j) {
			double factor = matrixCopy[size - j - 1][size - i - 1] / matrixCopy[size - i - 1][size - i - 1];

			Row eliminationRow = factor * matrixCopy[size - i - 1];
			matrixCopy[size - j - 1] -= eliminationRow;

			Row inverseEliminationRow = factor * inverse[size - i - 1];
			inverse[size - j - 1] -= inverseEliminationRow;
		}
	}

	// Step 3: Multiply each line by its inverse factor
	for (uint64_t i = 0; i < size; ++i) {
		double factor = 1 / matrixCopy[i][i];
		matrixCopy[i] *= factor;
		inverse[i] *= factor;
	}

	return inverse;
}

// No safety checks as std::vector will throw exceptions anyway

Row operator+(Row& lhs, Row& rhs) {
	Row result;
	for (size_t i = 0; i < lhs.size(); ++i) {
		result.push_back(lhs[i] + rhs[i]);
	}

	return result;
}

Row& operator+=(Row& lhs, Row& rhs) {
	for (size_t i = 0; i < lhs.size(); ++i) {
		lhs[i] += rhs[i];
	}

	return lhs;
}

Row operator-(Row& lhs, Row& rhs) {
	Row result;
	for (size_t i = 0; i < lhs.size(); ++i) {
		result.push_back(lhs[i] - rhs[i]);
	}

	return result;
}

Row& operator-=(Row& lhs, Row& rhs) {
	for (size_t i = 0; i < lhs.size(); ++i) {
		lhs[i] -= rhs[i];
	}

	return lhs;
}

Row operator*(Row& lhs, MatrixElementType rhs) {
	Row result;
	for (size_t i = 0; i < lhs.size(); ++i) {
		result.push_back(lhs[i] * rhs);
	}

	return result;
}

Row operator*(MatrixElementType lhs, Row& rhs) {
	return rhs * lhs;
}

Row& operator*=(Row& lhs, MatrixElementType rhs) {
	for (size_t i = 0; i < lhs.size(); ++i) {
		lhs[i] *= rhs;
	}

	return lhs;
}
