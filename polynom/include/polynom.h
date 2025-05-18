#include <stdexcept>
#include <numeric>
#include "Vector.h"

extern size_t N, k;
extern dv X, Y, polinom, gradient, V;

template<typename InputIt, typename OutputIt, typename UnaryOperation>
OutputIt Transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation unary_op) {
    while (first != last) {
        *d_first++ = unary_op(*first++);
    }
    return d_first;
}

template<typename InputIt1, typename InputIt2, typename OutputIt, typename BinaryOperation>
OutputIt Transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, OutputIt d_first, BinaryOperation binary_op) {
    while (first1 != last1) {
        *d_first++ = binary_op(*first1++, *first2++);
    }
    return d_first;
}

double P(double, const dv&);
void get_gradient();
double G(const dv&);
void get_V(bool);
double lambda();
double get_sigma(dv&);


