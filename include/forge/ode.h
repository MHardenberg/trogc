#ifndef ODE_H
#define ODE_H

#include "forge/mem/arena.h"
#include "forge/linalg.h"

void f_rk4(double *dest, double (*f)(double, double), double x0, double y0,
           double h, size_t N);

void f_rk4v(f_arena *alloc, f_matd *dest,
            void (*f)(f_vecd *, f_vecd *, f_vecd *), f_vecd *x, f_vecd *y,
            double h);

#endif
