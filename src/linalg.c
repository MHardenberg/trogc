#include "forge/mem/alloc.h"
#include <float.h>
#include <forge.h>
#include <forge/linalg.h>
#include <openblas/cblas.h>
#include <stddef.h>

f_vecd *f_vecdAlloc(f_alloc *alloc, size_t size) {
        assert(alloc != NULL);
        f_vecd *dest = f_allocPush(alloc, sizeof(f_vecd));
        dest->size = size;
        dest->x = f_allocPush(alloc, sizeof(double) * size);
        return dest;
}

f_vecd *f_vecdAllocZero(f_alloc *alloc, size_t size) {
        assert(alloc != NULL);
        f_vecd *dest = f_allocPush(alloc, sizeof(f_vecd));
        dest->size = size;
        dest->x = f_allocPush(alloc, sizeof(double) * size);

        f_vecdZero(dest);
        return dest;
}

void f_vecdCopy(f_vecd *dest, f_vecd *source) {
        dest->size = source->size;
        memcpy(dest->x, source->x, sizeof(double) * dest->size);
        f_vecdPrint(source);
        f_vecdPrint(dest);
}

void f_vecdSlice(f_vecd *dest, f_vecd *source, size_t from, size_t to) {
        assert(to <= source->size);
        assert(from < to);
        dest->size = to - from;
        dest->x = f_vecdIdx(source, from);
}

size_t f_vecdIMin(const f_vecd *v) {
        double m = DBL_MAX;
        size_t midx;
        for (size_t i = 0; i < v->size; ++i) {
                if (v->x[i] < m) {
                        m = v->x[i];
                        midx = i;
                }
        }
        return midx;
}

double *f_vecdMin(const f_vecd *v) {
        return f_vecdIdx(v, f_vecdIMin(v));
}

size_t f_vecdIMax(const f_vecd *v) {
        double M = DBL_MIN;
        size_t Midx;
        for (size_t i = 0; i < v->size; ++i) {
                if (v->x[i] > M) {
                        M = v->x[i];
                        Midx = i;
                }
        }
        return Midx;
}

double *f_vecdMax(const f_vecd *v) {
        return f_vecdIdx(v, f_vecdIMax(v));
}

void f_vecdFree(f_alloc *alloc, f_vecd *v) {
        assert(alloc != NULL);
        assert(v != NULL);
        f_allocFree(alloc, v->x);
        f_allocFree(alloc, v);
}

double *f_vecdIdx(const f_vecd *v, size_t i) {
        assert(i < v->size);
        return v->x + i;
}

void f_vecdOne(f_vecd *vec) {
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 1.0;
        }
}

void f_vecdZero(f_vecd *vec) {
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 0.0;
        }
}

void f_vecdArange(f_vecd *v, const double start, const double stop) {
        double step = (stop - start) / v->size;
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = start + step * i;
        }
}

void f_vecdAdd(f_vecd *dest, const f_vecd *a, const f_vecd *b) {
        assert((NULL != dest) && (NULL != a) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < a->size) && (i < b->size);
             ++i) {
                dest->x[i] = a->x[i] + b->x[i];
        }
}

void f_vecdIncr(f_vecd *dest, const double a, const f_vecd *b) {
        assert((NULL != dest) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < b->size); ++i) {
                dest->x[i] = a + b->x[i];
        }
}

void f_vecdScale(f_vecd *dest, const double a, const f_vecd *b) {
        assert((NULL != dest) && (NULL != b));
#ifdef _BLAS
        cblas_dscal(b->size, a, b->x, 1);
#else
        for (size_t i = 0; (i < dest->size) && (i < b->size); ++i) {
                dest->x[i] = a * b->x[i];
        }

#endif
}

void f_vecdEmul(f_vecd *dest, const double a, const f_vecd *x,
                const f_vecd *y) {
        assert((dest != NULL) && (x != NULL));
        for (size_t i = 0; (i < dest->size) && (i < x->size); ++i) {
                dest->x[i] = a * x->x[i] * y->x[i];
        }
}

double f_vecdMul(const f_vecd *a, const f_vecd *b) {
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

void f_vecdCross(f_vecd *dest, const f_vecd *a, const f_vecd *b) {
        assert((3 == a->size) && (3 == b->size) && (3 == dest->size));
        dest->x[0] = a->x[1] * b->x[2] - a->x[2] * b->x[1];
        dest->x[1] = a->x[2] * b->x[0] - a->x[0] * b->x[2];
        dest->x[2] = a->x[0] * b->x[1] - a->x[1] * b->x[0];
}

void f_vecdPrint(const f_vecd *v) {
        printf("[ ");
        for (size_t i = 0; i < v->size; ++i) {
                if (0 == i) {
                        printf("%.6e", *f_vecdIdx(v, i));
                } else {
                        printf(", %.6e", *f_vecdIdx(v, i));
                }
        }
        printf(" ]\n\n");
}

// Matrices

f_matd *f_matdAlloc(f_alloc *alloc, size_t cols, size_t rows) {
        assert(alloc != NULL);
        f_matd *dest = f_allocPush(alloc, sizeof(f_matd));
        dest->x = f_allocPush(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

f_matd *f_matdAllocZero(f_alloc *alloc, size_t cols, size_t rows) {
        assert(alloc != NULL);
        f_matd *dest = f_allocPush(alloc, sizeof(f_matd));
        dest->x = f_allocPushZero(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

void f_matdFree(f_alloc *alloc, f_matd *m) {
        assert(alloc != NULL);
        assert(m != NULL);
        f_allocFree(alloc, m->x);
        f_allocFree(alloc, m);
}

void f_matdCopy(f_matd *dest, f_matd *source) {
        dest->cols = source->cols;
        dest->rows = source->rows;
        memcpy(dest->x, source->x, sizeof(double) * dest->cols * dest->rows);
}

double *f_matdIdx(const f_matd *m, const size_t r, const size_t c) {
        assert((r < m->rows) && (c < m->cols));
        return m->x + (c * m->rows + r);
}

void f_matdCol(f_vecd *dest, const f_matd *m, const size_t c) {
        assert(dest->size == m->rows);
        dest->x = f_matdIdx(m, 0, c);
}

void f_matdOne(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *f_matdIdx(m, r, c) = 1.0;
                }
        }
}

void f_matdZero(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *f_matdIdx(m, r, c) = 0.0;
                }
        }
}

void f_matdIdent(f_matd *m) {
        assert(m->rows == m->cols);
        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *f_matdIdx(m, r, c) = (c == r) ? 1.0 : 0.0;
                }
        }
}

void f_matdMVMul(f_vecd *dest, const f_matd *m, const f_vecd *v,
                 const double a) {
#ifdef _BLAS
        cblas_dgemv(CblasColMajor, CblasNoTrans, m->rows, m->cols, a, m->x,
                    m->rows, v->x, 1, 0.0, dest->x, 1);
#else
#error "Not implemented!"
#endif
}

void f_matdMMul(f_matd *dest, const double alpha, const f_matd *a,
                const f_matd *b) {
#ifdef _BLAS
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, a->rows, b->cols,
                    a->cols, alpha, a->x, a->rows, b->x, b->rows, 1.0, dest->x,
                    dest->rows);
#else
#error "Not implemented!"
#endif
}

void f_matdPrint(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                printf("| ");
                for (size_t c = 0; c < m->cols; ++c) {
                        if (0 == c) {
                                printf("%.6e", *f_matdIdx(m, r, c));
                        } else {
                                printf(", %.6e", *f_matdIdx(m, r, c));
                        }
                }
                printf(" |\n");
        }
        printf("\n");
}
