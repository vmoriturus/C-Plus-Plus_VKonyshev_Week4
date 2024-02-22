#ifndef MATRIX_H
#define MATRIX_H

#include <vector>


// Type aliases for convenience and readability
typedef std::vector<double> MatrixVector;
typedef std::vector<MatrixVector> VectorOfMatrixVector;
typedef std::pair<size_t, size_t> SizePair;

// Matrix class representing a real-valued matrix
class Matrix {
public:
private:
    VectorOfMatrixVector _matrix;



public:
//    Stages 1-2
    static MatrixVector createVector(size_t sz, double val);


//    Stage 4
    Matrix(size_t m, size_t n, double def);
    Matrix();
    void resize(size_t m, size_t n, double def);


//    Stage 5
    SizePair getSize() const;
    MatrixVector& operator[](const size_t i);
    const MatrixVector& operator[](const size_t i) const;
    double getEl(size_t i, size_t j) const;
    void setEl(size_t i, size_t j, double val);


//    Stage 6
    bool operator==(const Matrix& rhv) const;
    bool operator!=(const Matrix& rhv) const;

    Matrix operator+(const Matrix& rhv) const;

    friend Matrix operator*(const Matrix& m, double k);
    friend Matrix operator*(double k, const Matrix& m);

    Matrix operator*(double k) const;
    Matrix operator*(const Matrix& m) const;

};

Matrix operator*(const Matrix& lhv, double rhv);
Matrix operator*(double lhv, const Matrix& rhv);


#endif // MATRIX_H

