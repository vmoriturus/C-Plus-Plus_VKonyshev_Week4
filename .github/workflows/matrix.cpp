//Implementation part of a module for the Matrix class.
#include <stdexcept>
#include "matrix.h"

//Stages 1-2
//Implementation of the static method createVector()
MatrixVector Matrix::createVector(size_t sz, double val) {
    if (sz)
        return MatrixVector(sz, val); // Create a vector of size sz, initialized with val
    else
        return MatrixVector();
}


//Stage 3
//Implementation a constructor that creates a matrix of a given size with given values of all elements.
Matrix::Matrix(size_t m, size_t n, double def) {
    for (size_t row = 0; row < m; ++row) {
        _matrix.push_back(createVector(n, def));
    }
}

//Implementation a default constructor that delegates the creation of a new instance of the class to a previously created constructor
Matrix::Matrix() : Matrix(0, 0, 0.0) {}

//Implementation a resize() method to resize existing Matrix.
void Matrix::resize(size_t m, size_t n, double def) {
    _matrix.resize(m);
    for (size_t i = 0; i < m; ++i) {
     if (i < _matrix.size()) {
       _matrix[i].resize(n, def);
     } else {
       _matrix[i] = createVector(n, def);
     }
    }
 }


//Stage 4
//Implementation a method that returns the current size of a matrix.
 SizePair Matrix::getSize() const{
     if (_matrix.empty()) {
         return std::make_pair(0, 0); // Return (0, 0) for an empty matrix
     } else {
         return std::make_pair(_matrix.size(), _matrix[0].size()); // Valid matrix, return size
     }
 }


// Stage 5
// Overloaded [] operator for non-const instances
MatrixVector& Matrix::operator[](const size_t i) {
    if (i >= _matrix.size()) {
        throw std::out_of_range("There is no such row");
    }
    return _matrix[i];
}

// Overloaded [] operator for const instances
const MatrixVector& Matrix::operator[](const size_t i) const {
    if (i >= _matrix.size()) {
        throw std::out_of_range("There is no such row");
    }
    return _matrix[i];
}

double Matrix::getEl(size_t i, size_t j) const {
    if (i >= _matrix.size() || j >= _matrix[0].size()) {
        throw std::out_of_range("Invalid element indices");
    }
    return _matrix[i][j];
}

void Matrix::setEl(size_t i, size_t j, double val) {
    if (i >= _matrix.size() || j >= _matrix[0].size()) {
        throw std::out_of_range("Invalid element indices");
    }
    _matrix[i][j] = val;
}

//Stage 6
bool Matrix::operator==(const Matrix& rhv) const {

    if (not _matrix.empty() & not rhv._matrix.empty()) {
        // Check if dimensions are equal
        if (_matrix.size() != rhv._matrix.size() ||
            _matrix[0].size() != rhv._matrix[0].size()) {
            return false;
        }

        // Compare elements
        for (size_t i = 0; i < _matrix.size(); ++i) {
            for (size_t j = 0; j < _matrix[i].size(); ++j) {
                if (_matrix[i][j] != rhv._matrix[i][j]) {
                    return false;
                }
            }
        }
    }
    if (_matrix.empty() & not rhv._matrix.empty())
        return false;
    if (not _matrix.empty() & rhv._matrix.empty())
        return false;
    return true;
}

bool Matrix::operator!=(const Matrix& rhv) const {
    // Use negation of the equality operator for efficiency
    return !(*this == rhv);
}

Matrix Matrix::operator+(const Matrix& rhv) const {
    Matrix result;
    if (not _matrix.empty() & not rhv._matrix.empty()) {
        // Check if dimensions are equal
        if (_matrix.size() != rhv._matrix.size() ||
            _matrix[0].size() != rhv._matrix[0].size()) {
            throw std::invalid_argument("Matrix sizes are incompatible");
        }

        // Create a new matrix for the sum
        result.resize(_matrix.size(), _matrix[0].size(), 0);

        // Add corresponding elements
        for (size_t i = 0; i < _matrix.size(); ++i) {
            for (size_t j = 0; j < _matrix[i].size(); ++j) {
                result[i][j] = _matrix[i][j] + rhv._matrix[i][j];
            }
        }
    }
    if (_matrix.empty() & not rhv._matrix.empty())
        throw std::invalid_argument("Matrix sizes are incompatible");
    if (not _matrix.empty() & rhv._matrix.empty())
        throw std::invalid_argument("Matrix sizes are incompatible");
    return result;
}

// Implementation of friend matrix multiplication by a real number (Matrix * double)
Matrix operator*(const Matrix& m, double k) {
    Matrix result(m.getSize().first, m.getSize().second, 0);
    for (size_t i = 0; i < result._matrix.size(); ++i) {
        for (size_t j = 0; j < result._matrix[i].size(); ++j) {
            result._matrix[i][j] = m._matrix[i][j] * k;
        }
    }
    return result;
}

// Implementation of friend matrix multiplication by a real number (double * Matrix)
Matrix operator*(double k, const Matrix& m) {
    Matrix result(m.getSize().first, m.getSize().second, 0);
    for (size_t i = 0; i < result._matrix.size(); ++i) {
        for (size_t j = 0; j < result._matrix[i].size(); ++j) {
            result._matrix[i][j] = m._matrix[i][j] * k;
        }
    }
    return result;
}
