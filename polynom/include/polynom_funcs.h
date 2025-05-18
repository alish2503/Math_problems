#ifndef POLYNOM_FUNCS
#define POLYNOM_FUNCS

#include <cmath>

double fun1(double x) {
    return 3.14 * pow(x, 3) - 1.7 * pow(x, 2) + 6.145 * x + 1;
}
double fun2(double x) {
    return -3.15 * pow(x, 2) + 1.21 * x - 1;
}
double fun3(double x) {
    return sin(x) * exp(x);
}

#endif
