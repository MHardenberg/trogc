#include <trog/mem/alloc.h>
#include <trog/ode.h>
#include <trog/maths.h>
#include <trog/linalg.h>

double rk4Step(dydt_fn f, const double x, const double y, const double h,
               void *params) {
        const double k1 = f(x, y, 0., params);
        const double k2 = f(x + h / 2, y + h / 2 * k1, h / 2, params);
        const double k3 = f(x + h / 2, y + h / 2 * k2, h / 2, params);
        const double k4 = f(x + h, y + h * k3, h, params);

        return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

void tr_rk4(double *dest, dydt_fn f, const double x0, double y0, const double h,
            const size_t N, void *params) {
        tr_assert(dest != NULL);
        for (size_t i = 0; i < N; ++i) {
                dest[i] = rk4Step(f, x0, f(x0, y0, h, params), h, params);
        }
}

void rk4Stepv(tr_vecd *ynext, dvdt_fn dvdt, const double x,
              tr_vecd *restrict yn, const double h, const void *params,
              tr_rk4Containers *rk4containers) {
        tr_vecd *restrict k1 = rk4containers->k1;
        tr_vecd *restrict k2 = rk4containers->k2;
        tr_vecd *restrict k3 = rk4containers->k3;
        tr_vecd *restrict k4 = rk4containers->k4;
        tr_vecd *restrict ytemp = rk4containers->ytemp;

        // K1 = f(x, yn)
        dvdt(k1, yn, x, 0., params);

        // K2 = f(x + h/2, yn + h * k1/2)
        tr_vecdScAdd(ytemp, yn, h / 2., k1);
        dvdt(k2, ytemp, x + h / 2., h / 2., params);

        // K3 = f(x + h/2, yn + h * k2/2)
        tr_vecdScAdd(ytemp, yn, h / 2., k2);
        dvdt(k3, ytemp, x + h / 2., h / 2., params);

        // K4 = f(x + h, yn + h * k3)
        tr_vecdScAdd(ytemp, yn, h, k3);
        dvdt(k4, ytemp, x + h, h, params);

        // ynext = yn + h*(k1/6 + k2/3 + k3/3 + k4/6)
        tr_vecdScAdd(ytemp, yn, h / 6., k1);
        tr_vecdScAdd(ytemp, ytemp, h / 3., k2);
        tr_vecdScAdd(ytemp, ytemp, h / 3., k3);
        tr_vecdScAdd(ynext, ytemp, h / 6., k4);
}

// mat schould by rows = dims - cols = steps
// dvdt function should have signature void ode(tr_vecd *dvdt, tr_vecd *x,
// double time, double step, void *params)
void tr_rk4v(tr_alloc *alloc, dvdt_fn dvdt, tr_matd *restrict Y,
             const tr_vecd *restrict y0, const tr_vecd *restrict x,
             const double h, const void *functionParams) {
        tr_assert(alloc != NULL);
        tr_assert(dvdt != NULL);
        tr_assert(Y != NULL);
        tr_assert(y0 != NULL);
        tr_assert(x != NULL);
        tr_assert(functionParams != NULL);

        tr_assert(x->size == Y->cols);
        tr_assert(y0->size == Y->rows);

        tr_rk4Containers rk4containers = {
            .k1 = tr_vecdAllocZero(alloc, Y->rows),
            .k2 = tr_vecdAllocZero(alloc, Y->rows),
            .k3 = tr_vecdAllocZero(alloc, Y->rows),
            .k4 = tr_vecdAllocZero(alloc, Y->rows),
            .ytemp = tr_vecdAlloc(alloc, Y->rows)};
        tr_vecd ynow;
        tr_vecd ynext;
        tr_matdCol(&ynow, Y, 0);
        tr_vecdCopy(&ynow, y0);

        // for every step we compute the ynext value and put it into
        // y now, which is a cloumn in dest
        for (size_t i = 0; i < Y->cols - 1; ++i) {
                tr_matdCol(&ynow, Y, i);
                tr_matdCol(&ynext, Y, i + 1);
                rk4Stepv(&ynext, dvdt, *tr_vecdIdx(x, i), &ynow, h,
                         functionParams, &rk4containers);
        }

        tr_allocFree(alloc, rk4containers.k1);
        tr_allocFree(alloc, rk4containers.k2);
        tr_allocFree(alloc, rk4containers.k3);
        tr_allocFree(alloc, rk4containers.k4);
}
