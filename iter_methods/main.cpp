#include "plot.h"
#include "Matrix.h"
#include "funcs.h"
#include "iter_methods.h"
#include "norms.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

int main(void) { 
	size_t p = 3;
	double h = 1.0 / n;
	h2 = h * h;
	dv x(n + 1), y(n + 1);
    for (size_t i = 0; i <= n; ++i) x[i] = y[i] = i * h;
	Matrix ua(np);
	for (size_t i = 1; i < n; ++i) {
		for (size_t j = 1; j < n; ++j) f(i, j) = fun1(x[i], y[j]);
	}
	for (size_t i = 0; i < np; ++i) {
    		for (size_t j = 0; j < np; ++j) ua(i, j) = u_a1(x[i], y[j]);   
    }
	for (size_t i = 0; i < np; ++i) {
		u1[i].front() = u[i].front() = south(x[i]); u1(0, i) = u(0, i) = west(y[i]);
		u1[i].back() = u[i].back() = north(x[i]); u1(n, i) = u(n, i) = east(y[i]);
	}
	double t1 = approx();
	double t4 = c_norm(u1 - ua);
	double rs, r, tmp, omega; 
	size_t opt, m;
	std::cout << "Method from 1 to 4: ";
	std::cin >> opt;
	switch (opt) {
		case 1:
			m = ceil(2 * p * log(10) / (M_PI * M_PI * h2));
			rs = cos(M_PI * h);
			break;
		case 2:
			m = ceil(p * log(10) / (M_PI * M_PI * h2));
			rs = 1.0 - M_PI * M_PI * h2;
			break;
		case 3:
			m = ceil(2 * p * log(10) / (M_PI * h));
			r = cos(M_PI * h);
			omega = 2.0 / (1.0 + sqrt(1.0 - r * r));
			rs = omega - 1.0;
			break;
		case 4:
			m = ceil(p * log(10) / (M_PI * M_PI * h2));
			rs = 1.0 - M_PI * M_PI * h2;
			break;
		default:
			std::cout << "Ошибка!" << std::endl;
			return 1;
	}
	std::cout << std::endl << "Iterations " << m << std::endl;
	std::cout << "Spectral radius " << rs << std::endl << std::endl;
	std::cout << std::setw(5) << std::left << "k"
		<< std::setw(15) << std::right << "|F-AUk|"
		<< std::setw(22) << std::right << "|F-AUk|/|F-AU0|"
		<< std::setw(12) << std::right << "|Uk-aU|"
		<< std::setw(18) << std::right << "|Uk-aU|/|U0-aU|"
		<< std::setw(15) << std::right << "|Uk-U(k-1)|"
		<< std::setw(28) << std::right << "Error estimate"
		<< std::setw(12) << std::right << "rs_exp"
		<< std::endl;	
	auto start = std::chrono::high_resolution_clock::now();
	for (size_t k = 1; k <= m; k++) {
		switch (opt) {
			case 1:
				Jacobi();
				break;
			case 2:
				Seidel();
				break;
			case 3:
				Sor(omega);
				break;
			case 4:
				modified_Seidel();
				break;
		}
		double t5 = c_norm(u - u1);
		double t2 = approx();
		double t3 = c_norm(u - ua);
		
		std::cout << std::fixed << std::setprecision(7);
		
		if (opt == 3) {
			if ((k % 10 == 0) || k == m) {
				std::cout << std::setw(5) << std::left << k
						<< std::setw(15) << std::right << t2
						<< std::setw(20) << std::right << t2 / t1
						<< std::setw(15) << std::right << t3
						<< std::setw(15) << std::right << t3 / t4
						<< std::setw(15) << std::right << t5
						<< std::setw(18) << std::right << rs * t5 / (1.0 - rs)
						<< std::setw(15) << std::right << t5 / tmp
						<< std::endl;
			}
		} else if (k % 100 == 0 || k == m) {
			std::cout << std::setw(5) << std::left << k
					<< std::setw(15) << std::right << std::setprecision(4) << t2
					<< std::setw(20) << std::right << std::setprecision(7) << t2 / t1
					<< std::setw(15) << std::right << std::setprecision(5) << t3
					<< std::setw(15) << std::right << std::setprecision(5) << t3 / t4
					<< std::setw(15) << std::right << std::setprecision(7) << t5
					<< std::setw(18) << std::right << std::setprecision(6) << rs * t5 / (1.0 - rs)
					<< std::setw(15) << std::right << std::setprecision(5) << t5 / tmp
					<< std::endl;
		}
		tmp = t5;
		u1 = u;
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start) * 1.0e-6;
	std::cout << std::endl << duration.count() << " secs" << std::endl;
	std::cout << std::endl << "Umax = " << matr_extr([](double a, double b) { return std::max(a, b); }) << std::endl;
    std::cout << "Umin = " << matr_extr([](double a, double b) { return std::min(a, b); }) << std::endl;
	std::ofstream ofs("data.txt");
    for (size_t i = 0; i < np; ++i) {
		for (size_t j = 0; j < np; ++j) ofs << x[i] << ' ' << y[j] << ' ' << u1(i, j) << std::endl;
	}
	plot();
	ofs.close();
	std::remove("data.txt");
	return 0;
}

 

