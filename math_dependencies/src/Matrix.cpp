#include "Matrix.h"
#include <numeric>

Matrix::Matrix() : size(0) {}

Matrix::Matrix(size_t n) : matrix(n, dv(n, 0.0)), size(n) {}

Matrix& Matrix::operator+=(const Matrix& B) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            matrix[i][j] += B(i, j);
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& B) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            matrix[i][j] -= B(i, j);
        }
    }
    return *this;
}

Matrix operator+(const Matrix& A, const Matrix& B) {
    Matrix Sum = A;
    Sum += B;
    return Sum;
}

Matrix operator-(const Matrix& A, const Matrix& B) {
    Matrix Sub = A;
    Sub -= B;
    return Sub;
}

dv operator*(const Matrix& A, const dv& v) {
    dv res(A.getSize(), 0.0);
    for (size_t i = 0; i < A.getSize(); ++i) {
        res[i] = std::inner_product(A[i].begin(), A[i].end(), v.begin(), 0.0);
    }
    return res;
}

Matrix operator*(const Matrix& A, double a) {
    Matrix Res(A.getSize());
    for (size_t i = 0; i < Res.getSize(); ++i) {
        for (size_t j = 0; j < Res.getSize(); ++j) {
            Res(i, j) = A(i, j) * a;
        }
    }
    return Res;
}

double& Matrix::operator()(size_t i, size_t j) { 
    if (i >= size || j >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return matrix[i][j];
}

const double& Matrix::operator()(size_t i, size_t j) const { 
    if (i >= size || j >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return matrix[i][j]; 
}

dv& Matrix::operator[](size_t i) { 
    if (i >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return matrix[i];
}

const dv& Matrix::operator[](size_t i) const { 
    if (i >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return matrix[i];
}

size_t Matrix::getSize() const { return size; }

double Matrix::operator*(const Matrix& B) const {
    double res = 0.0;  
    for (size_t i = 0; i < size; ++i) {
        res += std::inner_product(matrix[i].begin(), matrix[i].end(), B[i].begin(), 0.0);
    }
    return res;
}
