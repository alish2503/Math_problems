#include "norms.h"

double c_norm(const Matrix& a) {
	double norm = 0.0;
	for (size_t i = 0; i < np; ++i) {
		for (size_t j = 0; j < np; ++j) norm = std::max(norm, fabs(a(i, j)));	
	}
	return norm;
}
double approx() {
	double norm = 0.0;
	for (size_t i = 1; i < n; ++i) {	
		for (size_t j = 1; j < n; ++j) {
            double max = fabs((u(i - 1, j) + u(i + 1, j) + u(i, j - 1) + u(i, j + 1) - 4 * u(i, j)) / h2 + f(i, j));
            norm = std::max(norm, max);
        }
    }        
	return norm;
}
