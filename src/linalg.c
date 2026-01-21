#include <forge.h>
#include <forge/linalg.h>
#include <openblas/cblas.h>

double *f_vecdIdx(f_vecd *v, size_t i) {
        if (i >= v->size) {
                return NULL;
        }

        else {
                return v->x + i;
        }
}

void f_vecdAssingContinuous(f_vecd *dest, size_t n) {
        dest->size = n;
        dest->x = (double *)(dest + 1);
}

void f_vecdOnes(f_vecd *vec) {
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 1.0;
        }
}

void f_vecdZeros(f_vecd *vec) {
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 0.0;
        }
}

void f_vecdAdd(f_vecd *dest, f_vecd *a, f_vecd *b) {
        if ((dest == NULL) || (a == NULL) || (b == NULL)) {
                return;
        }
        for (size_t i = 0; (i < dest->size) && (i < a->size) && (i < b->size);
             ++i) {
                dest->x[i] = a->x[i] + b->x[i];
        }
}

void f_vecdIncr(f_vecd *dest, double a, f_vecd *b) {
        if ((dest == NULL) || (b == NULL)) {
                return;
        }
        for (size_t i = 0; (i < dest->size) && (i < b->size); ++i) {
                dest->x[i] = a + b->x[i];
        }
}

void f_vecdScale(f_vecd *dest, double a, f_vecd *b) {
        if ((dest == NULL) || (b == NULL)) {
                return;
        }
#ifdef _BLAS
        cblas_dscal(b->size, a, b->x, 1);
#else
        for (size_t i = 0; (i < dest->size) && (i < b->size); ++i) {
                dest->x[i] = a * b->x[i];
        }

#endif
}

void f_vecdEmul(f_vecd *dest, const double a, f_vecd *x, f_vecd *y) {
        if ((dest == NULL) || (x == NULL)) {
                return;
        }
        for (size_t i = 0; (i < dest->size) && (i < x->size); ++i) {
                dest->x[i] = a * x->x[i] * y->x[i];
        }
}

double f_vecdMul(f_vecd *a, f_vecd *b) {
        double x = 0;
        if ((a == NULL) || (b == NULL)) {
                return x;
        }
#ifdef _BLAS
        x = cblas_ddot(a->size, a->x, 1, b->x, 1);
#else
        for (size_t i = 0; (i < a->size) && (i < b->size); ++i) {
                x += a->x[i] * b->x[i];
        }
#endif
        return x;
}

void f_vecdCross(f_vecd *dest, f_vecd *a, f_vecd *b) {
        if ((a->size != 3) || (b->size) || (dest->size)) {
                return;
        }
        dest->x[0] = a->x[1] * b->x[2] - a->x[2] * b->x[1];
        dest->x[1] = a->x[2] * b->x[0] - a->x[0] * b->x[2];
        dest->x[2] = a->x[0] * b->x[1] - a->x[1] * b->x[0];
}
void f_vecdPrint(f_vecd *v) {
        printf("[ ");
        for (size_t i = 0; i < v->size; ++i) {
                printf("%f, ", *f_vecdIdx(v, i));
        }
        printf(" ]\n");
}

// Matrices
double *f_matdIdx(f_matd *m, size_t r, size_t c) {
        if ((r >= m->rows) || (c >= m->cols)) {
                return NULL;
        }

        return m->x + (c * m->rows + r);
}

void f_matdOnes(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *f_matdIdx(m, r, c) = 1.0;
                }
        }
}

void f_matdZeros(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *f_matdIdx(m, r, c) = 0.0;
                }
        }
}

int f_matdIdent(f_matd *m) {
        if (m->rows != m->cols) {
                return 1;
        }
        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *f_matdIdx(m, r, c) = (c == r) ? 1.0 : 0.0;
                }
        }
        return 0;
}

void f_matdMVMul(f_vecd *dest, f_matd *m, f_vecd *v, double a, double b) {
#ifdef _BLAS
        cblas_dgemv(CblasColMajor, CblasNoTrans, m->rows, m->cols, a, m->x,
                    m->rows, v->x, 1, b, dest->x, 1);
#else
#error "Not implemented!"
#endif
}

void f_matdPrint(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                printf("| ");
                for (size_t c = 0; c < m->cols; ++c) {
                        printf("%f, ", *f_matdIdx(m, r, c));
                }
                printf(" |\n");
        }
}
