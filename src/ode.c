#include <forge/mem/alloc.h>
#include <forge/ode.h>
#include <forge/maths.h>
#include <forge/linalg.h>

double rk4Step(double (*f)(double, double, void *), const double x,
               const double y, const double h, void *params) {
        const double k1 = f(x, y, params);
        const double k2 = f(x + h / 2, y + h / 2 * k1, params);
        const double k3 = f(x + h / 2, y + h / 2 * k2, params);
        const double k4 = f(x + h, y + h * k3, params);

        return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

void f_rk4(double *dest, double (*f)(double, double, void *), const double x0,
           double y0, const double h, const size_t N, void *params) {
        f_assert(dest != NULL);
        for (size_t i = 0; i < N; ++i) {
                dest[i] = rk4Step(f, x0, f(x0, y0, params), h, params);
        }
}

void rk4Stepv(f_vecd *ynext, dvdt_fn dvdt, const double x, f_vecd *restrict yn,
              f_vecd *restrict ytemp, const double h, const void *params,
              f_vecd *restrict k1, f_vecd *restrict k2, f_vecd *restrict k3,
              f_vecd *restrict k4) {
        // K1 = f(x, yn)
        dvdt(k1, yn, x, 0., params);

        // K2 = f(x + h/2, yn + h * k1/2)
        f_vecdScale(ytemp, h / 2, k1);
        f_vecdAdd(ytemp, ytemp, yn);
        dvdt(k2, ytemp, x, h / 2, params);

        // K3 =  f(x+h/2, yn + h * k2/2)
        f_vecdScale(ytemp, h / 2, k2);
        f_vecdAdd(ytemp, ytemp, yn);
        dvdt(k3, ytemp, x, h / 2, params);

        // K4 =  f(x+h, yn + k3)
        f_vecdScale(ytemp, h, k3);
        f_vecdAdd(ytemp, yn, ytemp);
        dvdt(k4, ytemp, x, h, params);

        f_assert(ynext != k1);
        f_assert(ynext != k2);
        f_assert(ynext != k3);
        f_assert(ynext != k4);
        f_assert(ynext != ytemp);

        // ynext = yn + h(k1/6 + k2/3 + k3/3 + k4/6)
        f_vecdAdd(ynext, k2, k3);
        f_vecdScale(ynext, 2, ynext);

        f_vecdAdd(ynext, ynext, k1);
        f_vecdAdd(ynext, ynext, k4);
        f_vecdScale(ynext, h / 6., ynext);

        f_vecdAdd(ynext, ynext, yn);
}

// mat schould by rows = dims - cols = steps
// dvdt function should have signature void ode(f_vecd *dvdt, f_vecd *x, double
// time, void *params)
void f_rk4v(f_alloc *alloc, dvdt_fn dvdt, f_matd *restrict Y,
            const f_vecd *restrict y0, const f_vecd *restrict x, const double h,
            const void *functionParams) {
        f_assert(alloc != NULL);
        f_assert(dvdt != NULL);
        f_assert(Y != NULL);
        f_assert(y0 != NULL);
        f_assert(x != NULL);
        f_assert(functionParams != NULL);

        f_assert(x->size == Y->cols);
        f_assert(y0->size == Y->rows);

        f_vecd *k1 = f_vecdAllocZero(alloc, Y->rows);
        f_vecd *k2 = f_vecdAllocZero(alloc, Y->rows);
        f_vecd *k3 = f_vecdAllocZero(alloc, Y->rows);
        f_vecd *k4 = f_vecdAllocZero(alloc, Y->rows);

        // for holding temp vectors during stepping
        f_vecd *ytemp = f_vecdAlloc(alloc, Y->rows);
        f_vecd ynow;
        f_vecd ynext;
        f_matdCol(&ynow, Y, 0);
        f_vecdCopy(&ynow, y0);

        // for every step we compute the ynext value and put it into
        // y now, which is a cloumn in dest
        for (size_t i = 0; i < Y->cols - 1; ++i) {
                f_matdCol(&ynow, Y, i);
                f_matdCol(&ynext, Y, i + 1);
                rk4Stepv(&ynext, dvdt, *f_vecdIdx(x, i), &ynow, ytemp, h,
                         functionParams, k1, k2, k3, k4);
        }

        f_allocFree(alloc, k1);
        f_allocFree(alloc, k2);
        f_allocFree(alloc, k3);
        f_allocFree(alloc, k4);
}
