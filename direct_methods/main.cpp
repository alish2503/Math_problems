#include "plot.h"
#include "Matrix.h"
#include "funcs.h"
#include "methods.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

int main(void) {
	double h = 1.0 / n;
	double h2 = h * h;
	dv x(n + 1), y(n + 1);
    for (size_t i = 0; i <= n; ++i) x[i] = y[i] = i * h;
	Matrix u(N), ua(N), c(N);
	for (size_t j = 0; j < N; ++j) {
		for (size_t i = 0; i < N; ++i) {
			f(j, i) += fun1(x[i + 1], y[j + 1]) * h2;
			if (!j) f(0, i) += south(x[i + 1]);
			else if (j == M) f(M, i) += north(x[i + 1]);
		}
		f(j, 0) += west(y[j + 1]);
		f(j, M) += east(y[j + 1]);
	}
	size_t max_iter = 100;
	bool flag = false;
	bool opt;
	double eps = 1.e-5;
	std::cout << "Method 0 or 1: ";
	std::cin >> opt;
	auto start = std::chrono::high_resolution_clock::now();
	if (opt) u = CG(eps, max_iter, flag);
	else {
		for (size_t i = 0; i < N; ++i) {
			c(i, i) = 4.0;
			if (i > 0) c(i - 1, i) = -1.0;
			if (i < M) c(i + 1, i) = -1.0;
		}	
		u = matr_sweep(c);
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start) * 1.0e-6;
	std::cout << duration.count() << " secs" << std::endl;
	double dlt = 0.0;
	size_t I, J;
	for (size_t j = 0; j < N; ++j) {
		for (size_t i = 0; i < N; ++i) { 
			ua(j, i) = u_a1(x[i + 1], y[j + 1]);     
			double t = fabs(u(j, i) - ua(j, i));
			if (t > dlt) {
				I = i;
				J = j;
				dlt = t;
			}
		}
    }
	if (opt) std::cout << "flag = " << flag << ", eps = " << eps << ", iterations = " << max_iter << std::endl;
	std::cout << "dlt = " << dlt << ", x[i]= " << x[I] << ", y[j]= " << y[J] << std::endl;
	std::ofstream ofs("data.txt");
	for (size_t j = 0; j < N; ++j) {
		for (size_t i = 0; i < N; ++i) ofs << x[i + 1] << ' ' << y[j + 1] << ' ' << u(j, i) << std::endl;
	}
	plot();
	ofs.close();
	std::remove("data.txt");
	return 0;
}




