#include <forge/ode.h>
#include <forge/maths.h>
#include <forge/linalg.h>

static inline double rk4Step(double (*f)(double, double), double x, double y,
                             double h) {
        const double k1 = f(x, y);
        const double k2 = f(x + h / 2, y + h / 2 * k1);
        const double k3 = f(x + h / 2, y + h / 2 * k2);
        const double k4 = f(x + h, y + h * k3);

        return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}

static inline void rk4Stepv(f_vecd *dest,
                            void (*f)(f_vecd *, f_vecd *, f_vecd *), f_vecd *x,
                            f_vecd *xh, f_vecd *y, f_vecd *yh, const double h,
                            f_vecd *k1, f_vecd *k2, f_vecd *k3, f_vecd *k4) {
        // y + h*(k1 + 2*k2 + 2*k3 + k4)/6;
        f(k1, x, y);

        f_vecdIncr(xh, h / 2, x);
        f_vecdIncr(yh, h / 2, x);
        f_vecdEmul(dest, 1.0f, yh, k1);
        f(k2, xh, dest);

        f_vecdEmul(dest, 1.0f, yh, k2);
        f(k3, xh, dest);

        f_vecdIncr(xh, h / 2.0f, x);
        f_vecdIncr(yh, h / 2.0f, x);
        f_vecdEmul(dest, 1.0f, yh, k3);
        f(k4, xh, dest);

        f_vecdAdd(dest, k2, k3);
        f_vecdScale(dest, 2.0f, dest);
        f_vecdAdd(dest, dest, k1);
        f_vecdAdd(dest, dest, k4);
        f_vecdScale(dest, h / 6.0f, dest);
        f_vecdAdd(dest, dest, y);
        return;
}

void f_rk4(double *dest, double (*f)(double, double), double x0, double y0,
           double h, size_t N) {
        if (dest == NULL) {
                return;
        }

        for (size_t i = 0; i < N; ++i) {
                dest[i] = rk4Step(f, x0, f(x0, y0), h);
        }
}

void f_rk4v(f_alloc *alloc, f_matd *dest,
            void (*f)(f_vecd *, f_vecd *, f_vecd *), f_vecd *x, f_vecd *y,
            double h) {
        if ((dest == NULL) || (dest == NULL) || (f == NULL) || (x == NULL) ||
            (y == NULL)) {
                return;
        }

        f_vecd desti = {.size = dest->rows, .x = f_matdIdx(dest, 0U, 0U)};
        f_vecd *k1 = f_allocPushZero(alloc, sizeof(f_vecd) * desti.size);
        f_vecd *k2 = f_allocPushZero(alloc, sizeof(f_vecd) * desti.size);
        f_vecd *k3 = f_allocPushZero(alloc, sizeof(f_vecd) * desti.size);
        f_vecd *k4 = f_allocPushZero(alloc, sizeof(f_vecd) * desti.size);
        f_vecd *xh = f_allocPushZero(alloc, sizeof(f_vecd) * desti.size);
        f_vecd *yh = f_allocPushZero(alloc, sizeof(f_vecd) * desti.size);

        for (size_t i = 0; i < dest->cols; ++i) {
                rk4Stepv(&desti, f, x, xh, y, yh, h, k1, k2, k3, k4);
                desti.x = f_matdIdx(dest, 0U, i);
        }
}
