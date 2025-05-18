#include "iter_methods.h"

double h2;
size_t n = 16;
size_t np = n + 1;
Matrix f(n), u(np), u1(np);

template <typename F>
void genericMethod(const F& func) {
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 1; j < n; ++j) u(i, j) = func(i, j);
    }
}

void Jacobi() {
	genericMethod([](size_t i, size_t j) {
		return (u1(i - 1, j) + u1(i + 1, j) + u1(i, j - 1) + u1(i, j + 1) + h2 * f(i, j)) / 4;
		});	
}
void Seidel() {
	genericMethod([](size_t i, size_t j) {
		return u(i, j) = (u(i - 1, j) + u(i + 1, j) + u(i, j - 1) + u(i, j + 1) + h2 * f(i, j)) / 4;
		});	
}
void modified_Seidel()  {
	genericMethod([](size_t i, size_t j) {
			if ((i + j) % 2 == 0) {
				return u(i, j) = (u(i - 1, j) + u(i + 1, j) + u(i, j - 1) + u(i, j + 1) + h2 * f(i, j)) / 4;
			}
			return u(i, j);
		});
	genericMethod([](size_t i, size_t j) {
			if ((i + j) % 2 == 1) {
				u(i, j) = (u(i - 1, j) + u(i + 1, j) + u(i, j - 1) + u(i, j + 1) + h2 * f(i, j)) / 4;
			}
			return u(i, j);
		});		
}
void Sor(double omega) {
	genericMethod([omega](size_t i, size_t j) {
			double tmp = (u(i - 1, j) + u(i + 1, j) + u(i, j - 1) + u(i, j + 1) + h2 * f(i, j)) / 4 - u(i, j);
			tmp *= omega;
			return u(i, j) + tmp;
		});	
}