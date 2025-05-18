#ifndef ITER_METHODS
#define ITER_METHODS

#include "globals1.h"

template <typename F>
void genericMethod(const F&);
void Jacobi();
void Seidel();
void modified_Seidel(); 
void Sor(double);

#endif