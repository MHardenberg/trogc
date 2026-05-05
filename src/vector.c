#include <assert.h>
#include <math.h>
#include <openblas/cblas.h>
#include <float.h>

#include <forge.h>
#include <forge/mem/alloc.h>
#include <forge/linalg.h>

f_vecd *f_vecdAlloc(f_alloc *alloc, size_t size) {
        assert(alloc != NULL);
        f_vecd *dest =
            f_allocPush(alloc, sizeof(f_vecd) + sizeof(double) * size);
        assert(dest != NULL);

        dest->size = size;
        dest->x = (double *)(dest + 1);
        return dest;
}

f_vecd *f_vecdAllocZero(f_alloc *alloc, size_t size) {
        f_vecd *dest = f_vecdAlloc(alloc, size);
        f_vecdZero(dest);
        return dest;
}

void f_vecdFree(f_alloc *alloc, f_vecd *v) {
        assert(alloc != NULL);
        assert(v != NULL);
        f_allocFree(alloc, v->x);
        f_allocFree(alloc, v);
}

double *f_vecdIdx(const f_vecd *v, size_t i) {
        assert(v != NULL);
        assert(i < v->size);
        return v->x + i;
}

void f_vecdPrint(const f_vecd *v) {
        printf("[ ");
        for (size_t i = 0; i < v->size; ++i) {
                if (i > 10) {
                        printf(", ...");
                        printf(", %.4e", *f_vecdIdx(v, v->size - 1));
                        break;
                }
                if (0 == i) {
                        printf("%.4e", *f_vecdIdx(v, i));
                } else {
                        printf(", %.4e", *f_vecdIdx(v, i));
                }
        }
        printf(" ]\n\n");
}

void f_vecdCopy(f_vecd *dest, const f_vecd *source) {
        dest->size = source->size;
        memcpy(dest->x, source->x, sizeof(double) * dest->size);
}

void f_vecdSlice(f_vecd *dest, const f_vecd *source, const size_t from,
                 const size_t to) {
        assert(to <= source->size);
        assert(from < to);
        dest->size = to - from;
        dest->x = f_vecdIdx(source, from);
}

size_t f_vecdIMin(const f_vecd *v) {
        double m = DBL_MAX;
        size_t midx = 0;
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
        double M = -DBL_MAX;
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

void f_vecdOne(f_vecd *vec) {
        assert(vec != NULL);
        assert(vec->x != NULL);
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 1.0;
        }
}

void f_vecdZero(f_vecd *vec) {
        assert(vec != NULL);
        assert(vec->x != NULL);
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 0.0;
        }
}

void f_vecdLinspace(f_vecd *v, const double start, const double stop) {
        assert(v != NULL);
        assert(v->x != NULL);
        double step = (stop - start) / (v->size - 1);
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = start + step * i;
        }
}

void f_vecdArange(f_vecd *v, const double scale) {
        assert(v != NULL);
        assert(v->x != NULL);

        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = scale * i;
        }
}

void f_vecdAdd(f_vecd *dest, const f_vecd *a, const f_vecd *b) {
        assert((NULL != dest) && (NULL != a) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < a->size) && (i < b->size);
             ++i) {
                dest->x[i] = a->x[i] + b->x[i];
        }
}

void f_vecdDiff(f_vecd *dest, const f_vecd *a, const f_vecd *b) {
        assert((NULL != dest) && (NULL != a) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < a->size) && (i < b->size);
             ++i) {
                dest->x[i] = a->x[i] - b->x[i];
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

        // buggy blas impl
        // #ifdef _BLAS
        //     cblas_dscal(b->size, a, b->x, 1);  <--- this is inplace and needs
        //     to be replace for the logic to work
        // #else
        for (size_t i = 0; (i < dest->size) && (i < b->size); ++i) {
                dest->x[i] = a * b->x[i];
        }

        // #endif
}

double f_vecdNorm(const f_vecd *v) {
        assert(v != NULL);
        return sqrt(f_vecdMul(v, v));
}

void f_vecdENorm(f_vecd *dest, const f_vecd **vecs, const size_t nvecs) {
        assert(dest != NULL);
        assert(vecs != NULL);

        for (size_t i = 0; i < nvecs; ++i) {
                assert(vecs[i] != 0);
                assert(vecs[i]->size == dest->size);
        }

        for (size_t i = 0; i < dest->size; ++i) {
                dest->x[i] = 0;
                for (size_t j = 0; j < nvecs; ++j) {
                        dest->x[i] += pow(vecs[j]->x[i], 2);
                }

                dest->x[i] = sqrt(dest->x[i]);
        }
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

double f_vecdSum(const f_vecd *v) {
        double sum = 0;
        assert(v != NULL);
        for (size_t i = 0; i < v->size; ++i) {
                sum += v->x[i];
        }

        return sum;
}

double f_vecdMean(const f_vecd *v) {
        return f_vecdSum(v) / v->size;
}

void f_vecdEMean(f_vecd *dest, const f_vecd **vecs, const size_t nvecs) {
        assert(dest != NULL);
        assert(vecs != NULL);

        for (size_t i = 0; i < nvecs; ++i) {
                assert(vecs[i] != 0);
                assert(vecs[i]->size == dest->size);
        }

        for (size_t i = 0; i < dest->size; ++i) {
                dest->x[i] = 0;
                for (size_t j = 0; j < nvecs; ++j) {
                        dest->x[i] += vecs[j]->x[i];
                }
                dest->x[i] /= nvecs;
        }
}

void f_vecdRotatex(f_vecd *dest, const f_vecd *v, const double phase) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(v->size == 3);

        const double vy = *f_vecdIdx(v, 1);
        const double vz = *f_vecdIdx(v, 2);

        *f_vecdIdx(dest, 1) = vy * cos(phase) - vz * sin(phase);
        *f_vecdIdx(dest, 2) = vy * sin(phase) + vz * sin(phase);
}

void f_vecdRotatey(f_vecd *dest, const f_vecd *v, const double phase) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(v->size == 3);

        const double vx = *f_vecdIdx(v, 0);
        const double vz = *f_vecdIdx(v, 2);

        *f_vecdIdx(dest, 0) = vx * cos(phase) + vz * sin(phase);
        *f_vecdIdx(dest, 2) = -vx * sin(phase) + vz * cos(phase);
}

void f_vecdRotatez(f_vecd *dest, const f_vecd *v, const double phase) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(v->size == 3);

        const double vx = *f_vecdIdx(v, 0);
        const double vy = *f_vecdIdx(v, 1);

        *f_vecdIdx(dest, 0) = vx * cos(phase) - vy * sin(phase);
        *f_vecdIdx(dest, 1) = vx * sin(phase) + vy * cos(phase);
}
