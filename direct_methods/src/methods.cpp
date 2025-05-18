#include "methods.h"
#include "linal.h"
#include <cmath>
#include <iostream>

size_t n = 64;
size_t M = n - 2;
size_t N = n - 1;
Matrix f(N);


Matrix matr_sweep(Matrix& c) {
	Vector<Matrix> alph;
	Matrix x(N), bet(N);
	Matrix tmp = c;
	alph.push_back(inv(std::move(tmp)));
	bet[0] = alph[0] * f[0];
	for (size_t i = 0; i < M; ++i) {
		alph.push_back(inv(c - alph[i]));
		bet[i + 1] = alph[i + 1] * (bet[i] + f[i + 1]);
	}
	x[M] = bet[M];
	for (int i = N - 2; i >= 0; --i) x[i] = alph[i] * x[i + 1] + bet[i];
	return x;
}
Matrix Ax(const Matrix& x) {
	Matrix matr(N);
	for (size_t i = 0; i < N; ++i) {
		matr(0, i) = 4 * x(0, i) - x(1, i);
		if (i > 0) matr(0, i) -= x(0, i - 1);
		if (i < M) matr(0, i) -= x(0, i + 1);
	}
	for (size_t j = 1; j < M; ++j) {
		for (size_t i = 0; i < N; ++i) {
			matr(j, i) = 4 * x(j, i) - x(j - 1, i) - x(j + 1, i);
			if (i > 0) matr(j, i) -= x(j, i - 1);
			if (i < M) matr(j, i) -= x(j, i + 1);
		}
	}
	for (size_t i = 0; i < N; ++i) {
		matr(M, i) = 4 * x(M, i) - x(N - 2, i);
		if (i > 0) matr(M, i) -= x(M, i - 1);
		if (i < M) matr(M, i) -= x(M, i + 1);
	}
	return matr;
}	
Matrix CG(double& eps, size_t& max_iter, bool& flag) { 
	Matrix z(N), x(N), p(N), r(N);
	p = r = f;
	double sr1 = r * r;
	double nf = std::sqrt(sr1);
	if (!nf) nf = 1.0;
	double res = 1.0; 
	if (res <= eps) {
		eps = res;
		max_iter = 0;
		return x;
	}
	for (size_t k = 1; k < max_iter; ++k) {
		z = Ax(p);
		double v = sr1 / (p * z);
		x += p * v;
		r -= z * v;
		double sr2 = r * r;
		res = std::sqrt(sr2) / nf;
		if (res <= eps) {
			eps = res;
			max_iter = k;
			return x;
		}
		double m = sr2 / sr1;		
		p = r + p * m;
		sr1 = sr2;
	}
	eps = res;
	flag = true;
	return x;
}