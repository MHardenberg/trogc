#include <forge/ode.h>
#include <forge/maths.h>
#include <forge/linalg.h>

static inline double rk4Step(double (*f)(double, double, void *), double x,
                             double y, double h, void *params) {
        const double k1 = f(x, y, params);
        const double k2 = f(x + h / 2, y + h / 2 * k1, params);
        const double k3 = f(x + h / 2, y + h / 2 * k2, params);
        const double k4 = f(x + h, y + h * k3, params);

        return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

void f_rk4(double *dest, double (*f)(double, double, void *), double x0,
           double y0, double h, size_t N, void *params) {
        assert(dest != NULL);
        for (size_t i = 0; i < N; ++i) {
                dest[i] = rk4Step(f, x0, f(x0, y0, params), h, params);
        }
}

static inline void rk4Stepv(f_vecd *ynext,
                            void (*dxdt)(f_vecd *, f_vecd *, double, void *),
                            double x, f_vecd *yn, f_vecd *ytemp, const double h,
                            void *params, f_vecd *k1, f_vecd *k2, f_vecd *k3,
                            f_vecd *k4) {
        // K1 = h*f(x, yn)
        dxdt(k1, yn, x, params);

        // K2 = f(x +h/2, yn + k1/2)
        f_vecdScale(ytemp, .5, k1);
        f_vecdAdd(ytemp, ytemp, yn);
        dxdt(k2, ytemp, x + h / 2, params);

        // K3 =  f(x+h/2, yn + k2/2)
        f_vecdScale(ytemp, .5, k2);
        f_vecdAdd(ytemp, ytemp, yn);
        dxdt(k3, ytemp, x + h / 2, params);

        // K4 =  f(x+h, yn + k3)
        f_vecdAdd(ytemp, yn, yn);
        dxdt(k3, ytemp, x + h, params);

        // ynext = yn + h(k1/6 + k2/3 + k3/3 + k4/6)
        f_vecdAdd(ynext, k2, k3);
        f_vecdScale(ynext, 2, ynext);

        f_vecdAdd(ynext, ynext, k1);
        f_vecdAdd(ynext, ynext, k4);
        f_vecdScale(ynext, h / 6., ynext);

        f_vecdAdd(ynext, ynext, yn);
}

// mat schould by rows = dims - cols = steps
// dxdt function should have signature void ode(f_vecd *dxdt, f_vecd *x, double
// time, void *params)
void f_rk4v(f_alloc *alloc, void (*dxdt)(f_vecd *, f_vecd *, double, void *),
            f_matd *Y, f_vecd *y0, f_vecd *x, double h, void *functionParams) {
        assert(alloc != NULL);
        assert(dxdt != NULL);
        assert(Y != NULL);
        assert(y0 != NULL);
        assert(x != NULL);
        assert(functionParams != NULL);

        assert(x->size == Y->cols);
        assert(y0->size == Y->rows);

        f_vecd *k1 = f_vecdAlloc(alloc, Y->rows);
        f_vecd *k2 = f_vecdAlloc(alloc, Y->rows);
        f_vecd *k3 = f_vecdAlloc(alloc, Y->rows);
        f_vecd *k4 = f_vecdAlloc(alloc, Y->rows);

        f_vecd ynow = {.size = Y->rows};
        f_matdCol(&ynow, Y, 0);
        f_vecdCopy(&ynow, y0);

        f_vecd *ynext = f_vecdAlloc(alloc, Y->rows);
        // for holding temp vectors during stepping
        f_vecd *ytemp = f_vecdAlloc(alloc, Y->rows);

        // for every step we compute the ynext value and put it into
        // y now, which is a cloumn in dest
        for (size_t i = 0; i < Y->cols - 1; ++i) {
                f_matdCol(&ynow, Y, i);
                f_matdCol(ynext, Y, i + 1);
                rk4Stepv(ynext, dxdt, *f_vecdIdx(x, i), &ynow, ytemp, h,
                         functionParams, k1, k2, k3, k4);
        }
}
