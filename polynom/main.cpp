#include "polynom.h"
#include "polynom_funcs.h"
#include "polynom_plot.h"
#include <iostream>
#include <iomanip>
#include <fstream>

int main() {
    double LEFT_BORDER, RIGHT_BORDER, eps = 1.e-9;
    size_t n0, m = 2;
    std::cout << "_____________________________Please enter data________________________________\n\n";
    std::cout << "LEFT_BORDER: ";
    std::cin >> LEFT_BORDER;
    std::cout << "RIGHT_BORDER: ";
    std::cin >> RIGHT_BORDER;
    std::cout << "N: ";
    std::cin >> N;
    std::cout << "Initial degree of polynom: ";
    std::cin >> n0;
    std::cout << "Number of polynoms from degree " << n0 << ": ";
    std::cin >> m;
    std::cout << std::endl;

    double h = (RIGHT_BORDER - LEFT_BORDER) / N;
    X.resize(N + 1);
    for (size_t i = 0; i < N + 1; ++i) X[i] = LEFT_BORDER + i * h;
    Y.resize(N + 1);
    std::cout << "Select function:\n";
    std::cout << "1. y = 2.14*x^3 - 0.6*x^2 + 5.342*x + 4\n";
    std::cout << "2. y = -2.14*(x^2) + 0.44*x - 4\n";
    std::cout << "3. y = sin(x) * exp(-x)\n";
    std::cout << "Your decision is: ";
    int choice;
    std::cin >> choice;
    std::cout << std::endl;

    switch (choice) {
        case 1:
            Transform(X.begin(), X.end(), Y.begin(), fun1);
            break;
        case 2:
            Transform(X.begin(), X.end(), Y.begin(), fun2);
            break;
        case 3:
            Transform(X.begin(), X.end(), Y.begin(), fun3);
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            return 1;
    }
    
    polinom.resize(n0 + m, 0.0);
    gradient.resize(n0 + m, 0.0);
    V.resize(n0 + m, 0.0);

    bool first;
    std::ofstream ofs("points.txt");
    for (k = n0; k < n0 + m; ++k) {
        size_t i = 0;
        first = true;
        double sigma = 1000.0;

        std::cout << "n: " << k << std::endl;

        while (sigma >= eps) {
            dv tmp = polinom;
            ++i;
            get_V(first);
            double Lambda = lambda();
            
            Transform(polinom.begin(), polinom.end(), V.begin(), polinom.begin(), [Lambda](double p, double v) {
                return p + Lambda * v;
            });
            if (first) first = false;
            else sigma = get_sigma(tmp);

            std::cout << "iter number " << i << ": |grad(F)|=" << std::sqrt(std::inner_product(gradient.begin(), gradient.end(), gradient.begin(), 0.0)) << std::endl;
        }
        dv p(N+1);
        double max_error = 0.0;
        std::cout << std::endl;
        std::cout << std::setw(5) << "iter"
                << std::setw(15) << "X(i)"
                << std::setw(15) << "Y(i)"
                << std::setw(15) << "P(i)"
                << std::setw(15) << "d" << std::endl;

        for (size_t i = 0; i < N + 1; ++i) {
            p[i] = P(X[i], polinom);
            double error = std::abs(Y[i] - p[i]);
            max_error = std::max(max_error, error);
            std::cout << std::setw(5) << i
                    << std::setw(15) << X[i]
                    << std::setw(15) << Y[i]
                    << std::setw(15) << p[i]
                    << std::setw(15) << error
                    << std::endl;
        }

        std::cout << std::endl;
        std::cout << "a0..an" << std::endl;
        for (size_t i = 0; i <= k; ++i) {
            std::cout << "a" << i << " = " << polinom[i] << std::endl;
        }
        std::cout << "Max error of polynom: " << max_error << std::endl;
        for (size_t i = 0; i < N + 1; ++i) {
            ofs << X[i] << ' ' << p[i] << std::endl;
        }
        ofs << std::endl << std::endl;
    }
    for (size_t i = 0; i < N + 1; ++i) {
        ofs << X[i] << ' ' << Y[i] << std::endl;
    }
    ofs.close();
    plot();
    std::remove("points.txt");
    return 0;
}
