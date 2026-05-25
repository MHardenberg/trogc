#include <assert.h>
#include <math.h>
#include <openblas/cblas.h>
#include <float.h>

#include <trog.h>
#include <trog/mem/alloc.h>
#include <trog/linalg.h>

tr_vecd *tr_vecdAlloc(tr_alloc *alloc, size_t size) {
        tr_assert(alloc != NULL);
        tr_vecd *dest =
            tr_allocPush(alloc, sizeof(tr_vecd) + sizeof(double) * size);
        tr_assert(dest != NULL);

        dest->size = size;
        dest->x = (double *)(dest + 1);
        return dest;
}

tr_vecd *tr_vecdAllocZero(tr_alloc *alloc, size_t size) {
        tr_vecd *dest = tr_vecdAlloc(alloc, size);
        tr_vecdZero(dest);
        return dest;
}

void tr_vecdFree(tr_alloc *alloc, tr_vecd *v) {
        tr_assert(alloc != NULL);
        tr_assert(v != NULL);
        tr_allocFree(alloc, v->x);
        tr_allocFree(alloc, v);
}

double *tr_vecdIdx(const tr_vecd *v, size_t i) {
        tr_assert(v != NULL);
        tr_assert(i < v->size);
        return v->x + i;
}

void tr_vecdPrint(const tr_vecd *v) {
        printf("[ ");
        for (size_t i = 0; i < v->size; ++i) {
                if (i > 10) {
                        printf(", ...");
                        printf(", %.4e", *tr_vecdIdx(v, v->size - 1));
                        break;
                }
                if (0 == i) {
                        printf("%.4e", *tr_vecdIdx(v, i));
                } else {
                        printf(", %.4e", *tr_vecdIdx(v, i));
                }
        }
        printf(" ]\n\n");
}

void tr_vecdCopy(tr_vecd *dest, const tr_vecd *source) {
        dest->size = source->size;
        memcpy(dest->x, source->x, sizeof(double) * dest->size);
}

void tr_vec2dCopy(tr_vec2d *dest, const tr_vec2d *source) {
        dest->x = source->x;
        dest->y = source->y;
}

void tr_vec3dCopy(tr_vec3d *dest, const tr_vec3d *source) {
        dest->x = source->x;
        dest->y = source->y;
        dest->z = source->z;
}

void tr_vec4dCopy(tr_vec4d *dest, const tr_vec4d *source) {
        dest->a = source->a;
        dest->b = source->b;
        dest->c = source->c;
        dest->d = source->d;
}

void tr_vecdSlice(tr_vecd *dest, const tr_vecd *source, const size_t from,
                  const size_t to) {
        tr_assert(to <= source->size);
        tr_assert(from < to);
        dest->size = to - from;
        dest->x = tr_vecdIdx(source, from);
}

size_t tr_vecdIMin(const tr_vecd *v) {
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

double tr_vecdMin(const tr_vecd *v) {
        return *tr_vecdIdx(v, tr_vecdIMin(v));
}

size_t tr_vecdIMax(const tr_vecd *v) {
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

double tr_vecdMax(const tr_vecd *v) {
        return *tr_vecdIdx(v, tr_vecdIMax(v));
}

void tr_vecdOne(tr_vecd *vec) {
        tr_assert(vec != NULL);
        tr_assert(vec->x != NULL);
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 1.0;
        }
}

void tr_vecdZero(tr_vecd *vec) {
        tr_assert(vec != NULL);
        tr_assert(vec->x != NULL);
        for (size_t i = 0; i < vec->size; ++i) {
                vec->x[i] = 0.0;
        }
}

void tr_vecdLinspace(tr_vecd *v, const double start, const double stop) {
        tr_assert(v != NULL);
        tr_assert(v->x != NULL);
        double step = (stop - start) / (v->size - 1);
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = start + step * i;
        }
}

void tr_vecdLogspace(tr_vecd *v, const double startExp, const double stopExp,
                     const double base) {
        tr_assert(v != NULL);
        tr_assert(v->x != NULL);

        if (v->size == 0) return;

        double step =
            (v->size > 1) ? (stopExp - startExp) / (v->size - 1) : 0.0;

        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = pow(base, startExp + step * i);
        }
}

void tr_vecdArange(tr_vecd *v, const double scale) {
        tr_assert(v != NULL);
        tr_assert(v->x != NULL);

        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = scale * i;
        }
}

void tr_vecdAdd(tr_vecd *dest, const tr_vecd *a, const tr_vecd *b) {
        tr_assert((NULL != dest) && (NULL != a) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < a->size) && (i < b->size);
             ++i) {
                dest->x[i] = a->x[i] + b->x[i];
        }
}

void tr_vec2dAdd(tr_vec2d *dest, const tr_vec2d *a, const tr_vec2d *b) {
        tr_assert(dest != NULL);
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        dest->x = a->x + b->x;
        dest->y = a->y + b->y;
}

void tr_vec3dAdd(tr_vec3d *dest, const tr_vec3d *a, const tr_vec3d *b) {
        tr_assert(dest != NULL);
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        dest->x = a->x + b->x;
        dest->y = a->y + b->y;
        dest->z = a->z + b->z;
}

void tr_vec4dAdd(tr_vec4d *dest, const tr_vec4d *a, const tr_vec4d *b) {
        tr_assert(dest != NULL);
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        dest->a = a->a + b->a;
        dest->b = a->b + b->b;
        dest->c = a->c + b->c;
        dest->d = a->d + b->d;
}

void tr_vecdDiff(tr_vecd *dest, const tr_vecd *a, const tr_vecd *b) {
        tr_assert((NULL != dest) && (NULL != a) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < a->size) && (i < b->size);
             ++i) {
                dest->x[i] = a->x[i] - b->x[i];
        }
}

void tr_vec2dDiff(tr_vec2d *dest, const tr_vec2d *a, const tr_vec2d *b) {
        tr_assert(dest != NULL);
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        dest->x = a->x - b->x;
        dest->y = a->y - b->y;
}

void tr_vec3dDiff(tr_vec3d *dest, const tr_vec3d *a, const tr_vec3d *b) {
        tr_assert(dest != NULL);
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        dest->x = a->x - b->x;
        dest->y = a->y - b->y;
        dest->z = a->z - b->z;
}

void tr_vec4dDiff(tr_vec4d *dest, const tr_vec4d *a, const tr_vec4d *b) {
        tr_assert(dest != NULL);
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        dest->a = a->a - b->a;
        dest->b = a->b - b->b;
        dest->c = a->c - b->c;
        dest->d = a->d - b->d;
}

void tr_vecdIncr(tr_vecd *dest, const double a, const tr_vecd *b) {
        tr_assert((NULL != dest) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < b->size); ++i) {
                dest->x[i] = a + b->x[i];
        }
}

void tr_vec2dIncr(tr_vec2d *dest, const double a, const tr_vec2d *b) {
        tr_assert(dest != NULL);
        tr_assert(b != NULL);

        dest->x = a + b->x;
        dest->y = a + b->y;
}

void tr_vec3dIncr(tr_vec3d *dest, const double a, const tr_vec3d *b) {
        tr_assert(dest != NULL);
        tr_assert(b != NULL);

        dest->x = a + b->x;
        dest->y = a + b->y;
        dest->z = a + b->z;
}

void tr_vec4dIncr(tr_vec4d *dest, const double a, const tr_vec4d *b) {
        tr_assert(dest != NULL);
        tr_assert(b != NULL);

        dest->a = a + b->a;
        dest->b = a + b->b;
        dest->c = a + b->c;
        dest->d = a + b->d;
}

void tr_vecdScale(tr_vecd *dest, const double a, const tr_vecd *b) {
        tr_assert((NULL != dest) && (NULL != b));

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

void tr_vec2dScale(tr_vec2d *dest, const double a, const tr_vec2d *b) {
        tr_assert(dest != NULL);
        tr_assert(b != NULL);

        dest->x = a * b->x;
        dest->y = a * b->y;
}

void tr_vec3dScale(tr_vec3d *dest, const double a, const tr_vec3d *b) {
        tr_assert(dest != NULL);
        tr_assert(b != NULL);

        dest->x = a * b->x;
        dest->y = a * b->y;
        dest->z = a * b->z;
}

void tr_vec4dScale(tr_vec4d *dest, const double a, const tr_vec4d *b) {
        tr_assert(dest != NULL);
        tr_assert(b != NULL);

        dest->a = a * b->a;
        dest->b = a * b->b;
        dest->c = a * b->c;
        dest->d = a * b->d;
}

void tr_vecdScAdd(tr_vecd *dest, const tr_vecd *v, const double a,
                  const tr_vecd *w) {
        tr_assert((NULL != dest) && (NULL != v) && (NULL != w));
        for (size_t i = 0; (i < dest->size) && (i < v->size) && (i < w->size);
             ++i) {
                dest->x[i] = v->x[i] + a * w->x[i];
        }
}

void tr_vec2dScAdd(tr_vec2d *dest, const tr_vec2d *v, const double a,
                   const tr_vec2d *w) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);
        tr_assert(w != NULL);

        dest->x = v->x + a * w->x;
        dest->y = v->y + a * w->y;
}

void tr_vec3dScAdd(tr_vec3d *dest, const tr_vec3d *v, const double a,
                   const tr_vec3d *w) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);
        tr_assert(w != NULL);

        dest->x = v->x + a * w->x;
        dest->y = v->y + a * w->y;
        dest->z = v->z + a * w->z;
}

void tr_vec4dScAdd(tr_vec4d *dest, const tr_vec4d *v, const double a,
                   const tr_vec4d *w) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);
        tr_assert(w != NULL);

        dest->a = v->a + a * w->a;
        dest->b = v->b + a * w->b;
        dest->c = v->c + a * w->c;
        dest->c = v->d + a * w->d;
}

void tr_vecdAddSc(tr_vecd *dest, const double a, const tr_vecd *v,
                  const tr_vecd *w) {
        tr_assert((NULL != dest) && (NULL != v) && (NULL != w));
        for (size_t i = 0; (i < dest->size) && (i < v->size) && (i < w->size);
             ++i) {
                dest->x[i] = a * (v->x[i] + w->x[i]);
        }
}

void tr_vec2dAddSc(tr_vec2d *dest, const double a, const tr_vec2d *v,
                   const tr_vec2d *w) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);
        tr_assert(w != NULL);

        dest->x = a * (v->x + a * w->x);
        dest->y = a * (v->y + a * w->y);
}

void tr_vec3dAddSc(tr_vec3d *dest, const double a, const tr_vec3d *v,
                   const tr_vec3d *w) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);
        tr_assert(w != NULL);

        dest->x = a * (v->x + w->x);
        dest->y = a * (v->y + w->y);
        dest->z = a * (v->z + w->z);
}

void tr_vec4dAddSc(tr_vec4d *dest, const double a, const tr_vec4d *v,
                   const tr_vec4d *w) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);
        tr_assert(w != NULL);

        dest->a = a * (v->a + w->a);
        dest->b = a * (v->b + w->b);
        dest->c = a * (v->c + w->c);
        dest->c = a * (v->d + w->d);
}

double tr_vecdNorm(tr_vecd *v) {
        tr_assert(v != NULL);

        double norm = 0;
        for (size_t i = 0; i < v->size; ++i) {
                norm += (v->x[i] * v->x[i]);
        }

        return sqrt(norm);
}

double tr_vec2dNorm(tr_vec2d *v) {
        return sqrt(v->x * v->x + v->y * v->y);
}

double tr_vec3dNorm(tr_vec3d *v) {
        return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

double tr_vec4dNorm(tr_vec4d *v) {
        return sqrt(v->a * v->a + v->b * v->b + v->c * v->c + v->d * v->d);
}

void tr_vecdENorm(tr_vecd *dest, const tr_vecd **vecs, const size_t nvecs) {
        tr_assert(dest != NULL);
        tr_assert(vecs != NULL);

        for (size_t i = 0; i < nvecs; ++i) {
                tr_assert(vecs[i] != 0);
                tr_assert(vecs[i]->size == dest->size);
        }

        for (size_t i = 0; i < dest->size; ++i) {
                dest->x[i] = 0;
                for (size_t j = 0; j < nvecs; ++j) {
                        dest->x[i] += pow(vecs[j]->x[i], 2);
                }

                dest->x[i] = sqrt(dest->x[i]);
        }
}

void tr_vecdEmul(tr_vecd *dest, const double a, const tr_vecd *x,
                 const tr_vecd *y) {
        tr_assert((dest != NULL) && (x != NULL));
        for (size_t i = 0; (i < dest->size) && (i < x->size); ++i) {
                dest->x[i] = a * x->x[i] * y->x[i];
        }
}

double tr_vecdMul(const tr_vecd *a, const tr_vecd *b) {
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

void tr_vecdCross(tr_vecd *dest, const tr_vecd *a, const tr_vecd *b) {
        tr_assert((3 == a->size) && (3 == b->size) && (3 == dest->size));
        dest->x[0] = a->x[1] * b->x[2] - a->x[2] * b->x[1];
        dest->x[1] = a->x[2] * b->x[0] - a->x[0] * b->x[2];
        dest->x[2] = a->x[0] * b->x[1] - a->x[1] * b->x[0];
}

double tr_vec2dCross(const tr_vec2d *a, const tr_vec2d *b) {
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        return a->x * b->y - a->y * b->x;
}

void tr_vec3dCross(tr_vec3d *dest, const tr_vec3d *a, const tr_vec3d *b) {
        tr_assert(dest != NULL);
        tr_assert(a != NULL);
        tr_assert(b != NULL);

        dest->x = a->y * b->z - a->z * b->y;
        dest->y = a->z * b->x - a->x * b->z;
        dest->z = a->x * b->y - a->y * b->x;
}

double tr_vecdSum(const tr_vecd *v) {
        double sum = 0;
        tr_assert(v != NULL);
        for (size_t i = 0; i < v->size; ++i) {
                sum += v->x[i];
        }

        return sum;
}

double tr_vecdMean(const tr_vecd *v) {
        return tr_vecdSum(v) / v->size;
}

void tr_vecdEMean(tr_vecd *dest, const tr_vecd **vecs, const size_t nvecs) {
        tr_assert(dest != NULL);
        tr_assert(vecs != NULL);

        for (size_t i = 0; i < nvecs; ++i) {
                tr_assert(vecs[i] != 0);
                tr_assert(vecs[i]->size == dest->size);
        }

        for (size_t i = 0; i < dest->size; ++i) {
                dest->x[i] = 0;
                for (size_t j = 0; j < nvecs; ++j) {
                        dest->x[i] += vecs[j]->x[i];
                }
                dest->x[i] /= nvecs;
        }
}

void tr_vec2dRotate(tr_vec2d *dest, const tr_vec2d *v, const double phase) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);

        const double vx = v->x;
        const double vy = v->y;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->x = vx * cos_phase - vy * sin_phase;
        dest->y = vx * sin_phase + vy * cos_phase;
}

void tr_vec3dRotatex(tr_vec3d *dest, const tr_vec3d *v, const double phase) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);

        const double vy = v->y;
        const double vz = v->z;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->y = vy * cos_phase - vz * sin_phase;
        dest->z = vy * sin_phase + vz * sin_phase;
}

void tr_vec3dRotatey(tr_vec3d *dest, const tr_vec3d *v, const double phase) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);

        const double vx = v->x;
        const double vz = v->z;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->x = vx * cos_phase + vz * sin_phase;
        dest->z = -vx * sin_phase + vz * cos_phase;
}

void tr_vec3dRotatez(tr_vec3d *dest, const tr_vec3d *v, const double phase) {
        tr_assert(dest != NULL);
        tr_assert(v != NULL);

        const double vx = v->x;
        const double vy = v->z;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->x = vx * cos_phase - vy * sin_phase;
        dest->y = vx * sin_phase + vy * cos_phase;
}
