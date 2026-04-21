#ifndef ODE_H
#define ODE_H

#include "forge/mem/alloc.h"
#include "forge/linalg.h"

// function to be solved needs to have the signature of
// void dmdt(double x, f_vecd *ys, void *params)
void f_rk4(double *dest, double (*f)(double, double, void *), const double x0,
           double y0, const double h, const size_t N, void *params);

// mat schould by rows = dims - cols = steps
// dxdt function should have signature void ode(f_vecd *dxdt, f_vecd *x, double
// time, void *params)
void f_rk4v(f_alloc *alloc,
            void (*dvdt)(f_vecd *, f_vecd *, const double, const void *),
            f_matd *Y, const f_vecd *y0, const f_vecd *x, const double h,
            const void *functionParams);

#endif
