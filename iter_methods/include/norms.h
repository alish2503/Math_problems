#ifndef NORMS_H
#define NORMS_H

#include "globals1.h"
#include <cmath>

double c_norm(const Matrix&);
double approx();
template <typename F> double matr_extr(const F& extr) {
	double find_extr = u1(0, 0);
	for (size_t i = 0; i < np; ++i) {
		for (size_t j = 0; j < np; ++j) find_extr = extr(find_extr, u1(i, j));
	}
	return find_extr;
}

#endif