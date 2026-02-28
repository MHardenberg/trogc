#ifndef ODE_H
#define ODE_H

#include "forge/mem/alloc.h"
#include "forge/linalg.h"

// function to be solved needs to have the signature of
// void dmdt(double x, f_vecd *ys, void *params)
void f_rk4(double *dest, double (*f)(double, double, void *), double x0,
           double y0, double h, size_t N, void *params);

// mat schould by rows = dims - cols = steps
// dxdt function should have signature void ode(f_vecd *dxdt, f_vecd *x, double
// time, void *params)
void f_rk4v(f_alloc *alloc, void (*dxdt)(f_vecd *, f_vecd *, double, void *),
            f_matd *Y, f_vecd *y0, f_vecd *x, double h, void *functionParams);

#endif
