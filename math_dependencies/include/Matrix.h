#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include "Vector.h"

class Matrix {
private:
    Vector<dv> matrix;
    size_t size;

public:
    Matrix();
    Matrix(size_t n);

    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);

    double& operator()(size_t, size_t);
    const double& operator()(size_t, size_t) const;
    dv& operator[](size_t);
    const dv& operator[](size_t) const;

    size_t getSize() const;
    double operator*(const Matrix&) const;
};

Matrix operator+(const Matrix& A, const Matrix& B);
Matrix operator-(const Matrix& A, const Matrix& B);
dv operator*(const Matrix& A, const dv& v);
Matrix operator*(const Matrix& A, double a);

#endif
