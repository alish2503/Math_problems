#include "linal.h"

dv operator+(const dv& a, const dv& b) {
    dv res(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        res[i] = a[i] + b[i];
    }
    return res;
}

Matrix inv(Matrix&& a) {
	Matrix e(N);
	for (size_t i = 0; i < N; ++i) e(i, i) = 1;
	double eps = 1.0e-9;
	for (size_t k = 0; k < M; ++k) {
		double max = std::fabs(a(k, k));
		size_t pos = k;
		for (size_t t = k + 1; t < N; ++t) {
			if (std::fabs(a(t, k)) > max) {
				max = std::fabs(a(t, k));
				pos = t;
			}
		}
		if (max < eps) throw "Error!";		
		if (pos != k) {
			std::swap(a[pos], a[k]);
			std::swap(e[pos], e[k]);		
		}
		for (size_t i = k + 1; i < N; ++i) {
			double tmp = a(i, k) / a(k, k);
			a(i, k) = 0;
			for (size_t j = k + 1; j < N; ++j) a(i, j) -= tmp * a(k, j);
			for (size_t s = 0; s < N; ++s) e(i, s) -= tmp * e(k, s);
		}
	}
	Matrix x(N);
	for (size_t k = 0; k < N; ++k) {
		for (int i = M; i >= 0; --i) {
			x(i, k) = e(i, k);
			double sum = 0 ;
			for (int j = M; j > i; --j) sum += a(i, j) * x(j, k);
			x(i, k) = (x(i, k) - sum) / a(i, i);
		}
	}
	return x;
}
dv operator+(const dv&, const dv&);