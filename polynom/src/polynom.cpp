#include <algorithm>
#include <cmath>
#include "polynom.h"

size_t N, k;
dv X, Y, polinom, gradient, V;

double P(double point, const dv& array) {
    double result = 0;
    for (size_t i = 0; i <= k; ++i) {
        result = array[k - i] + result * point;
    }
    return result;
}

void get_gradient() {
    for (size_t j = 0; j < k + 1; ++j) {
        gradient[j] = 0.0;
        for (size_t i = 0; i < N + 1; ++i) {
            gradient[j] += 2 * std::pow(X[i], j) * (P(X[i], polinom) - Y[i]);
        }
    } 
}

double G(const dv& array) {
    double result = 0;
    for (size_t i = 0; i < N + 1; ++i) {
        result += std::pow((Y[i] - P(X[i], array)), 2);
    }
    return result;
}

void get_V(bool first) {
    if (first) {
        get_gradient();
        V = gradient;
        Transform(V.begin(), V.end(), V.begin(), [](double v) {
            return -v;
        });
    } else {
        double tmpVal1 = std::inner_product(gradient.begin(), gradient.end(), gradient.begin(), 0.0);
        get_gradient();
        double tmpVal2 = std::inner_product(gradient.begin(), gradient.end(), gradient.begin(), 0.0);
        Transform(gradient.begin(), gradient.end(), V.begin(), V.begin(), [tmpVal1, tmpVal2](double g, double v) {
            return -g + (tmpVal2 / tmpVal1) * v;
        });
    }
}

double lambda() {
    double m1, m2, m3;
    dv polinom_minus_V(polinom.size());
    Transform(polinom.begin(), polinom.end(), V.begin(), polinom_minus_V.begin(), [](double p, double v) {
        return p - v;
    });
    dv polinom_plus_V(polinom.size());
    Transform(polinom.begin(), polinom.end(), V.begin(), polinom_plus_V.begin(), [](double p, double v) {
        return p + v;
    });
    m1 = G(polinom_minus_V);
    m2 = G(polinom);
    m3 = G(polinom_plus_V);
    return (m1 - m3) / (2 * (m1 - 2 * m2 + m3));
}

double get_sigma(dv& tmp) {
    double q, get_sigma_val = 1000;
    Transform(tmp.begin(), tmp.end(), polinom.begin(), tmp.begin(), [](double t, double p) {
        return t - p;
    });
    for (size_t i = 0; i < k + 1; ++i) {
        if (polinom[i] != 0.0) {
            q = std::abs(tmp[i] / polinom[i]);
            if (q < get_sigma_val) {
                get_sigma_val = q;
            }
        }
    }
    return get_sigma_val;
}




