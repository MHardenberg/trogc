#ifndef ODE_H
#define ODE_H

#include <trog/mem/alloc.h>
#include <trog/linalg.h>

// dydt = fn(y ,x, h, params)
typedef double (*dydt_fn)(double, double, double, void *);

typedef struct {
        tr_vecd *k1;
        tr_vecd *k2;
        tr_vecd *k3;
        tr_vecd *k4;
        tr_vecd *ytemp;
} tr_rk4Containers;

typedef struct {
        tr_vecd k1;
        tr_vecd k2;
        tr_vecd k3;
        tr_vecd k4;
} solver_arrays;

// dvdt = fn(dvdt, yvec, x, h, params)
typedef void (*dvdt_fn)(tr_vecd *, tr_vecd *, const double, const double,
                        const void *);

double rk4Step(dydt_fn f, const double x, const double y, const double h,
               void *params);
void tr_rk4(tr_vecd *restrict dest, dydt_fn f, const double x0, double y0,
            const double h, const size_t N, void *params);
// params should be struct &{p1[batchSize], p2[batchSize],...}
void tr_rk4Batch(tr_vecd **dest, dydt_fn f, const double x0, double y0,
                 const double h, const size_t N, const size_t batchSize,
                 void *params);

// mat schould by rows = dims - cols = steps
// dxdt function should have signature void ode(tr_vecd *dxdt, tr_vecd *x,
// double time, void *params)
void rk4Stepv(tr_vecd *ynext, dvdt_fn dvdt, const double x,
              tr_vecd *restrict yn, const double h, const void *params,
              tr_rk4Containers *rk4containers);
void tr_rk4v(tr_alloc *alloc, dvdt_fn dvdt, tr_matd *restrict Y,
             const tr_vecd *restrict y0, const tr_vecd *restrict x,
             const double h, const void *functionParams);
// params should be struct &{p1[batchSize], p2[batchSize],...}
void tr_rk4vBatch(tr_alloc *alloc, dvdt_fn dvdt, tr_matd *restrict *restrict Y,
                  const tr_vecd *restrict y0, const tr_vecd *restrict x,
                  const double h, const size_t batchSize,
                  const void *functionParams);

#endif
