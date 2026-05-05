#ifndef ODE_H
#define ODE_H

#include "forge/mem/alloc.h"
#include "forge/linalg.h"

// dydt = fn(y ,x, h, params)
typedef double (*dydt_fn)(double, double, void *);

double rk4Step(dydt_fn f, const double x, const double y, const double h,
               void *params);

void f_rk4(double *dest, double (*f)(double, double, void *), const double x0,
           double y0, const double h, const size_t N, void *params);

// mat schould by rows = dims - cols = steps
// dxdt function should have signature void ode(f_vecd *dxdt, f_vecd *x, double
// time, void *params)

// dvdt = fn(dvdt, yvec, x, h, params)
typedef void (*dvdt_fn)(f_vecd *, f_vecd *, const double, const double,
                        const void *);

void rk4Stepv(f_vecd *ynext, dvdt_fn dvdt, const double x, f_vecd *restrict yn,
              f_vecd *restrict ytemp, const double h, const void *params,
              f_vecd *restrict k1, f_vecd *restrict k2, f_vecd *restrict k3,
              f_vecd *restrict k4);

void f_rk4v(f_alloc *alloc, dvdt_fn dvdt, f_matd *restrict Y,
            const f_vecd *restrict y0, const f_vecd *restrict x, const double h,
            const void *functionParams);
#endif
