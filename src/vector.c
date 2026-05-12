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

void f_vec2dAdd(f_vec2d *dest, const f_vec2d *a, const f_vec2d *b) {
        assert(dest != NULL);
        assert(a != NULL);
        assert(b != NULL);

        dest->x = a->x + b->x;
        dest->y = a->y + b->y;
}

void f_vec3dAdd(f_vec3d *dest, const f_vec3d *a, const f_vec3d *b) {
        assert(dest != NULL);
        assert(a != NULL);
        assert(b != NULL);

        dest->x = a->x + b->x;
        dest->y = a->y + b->y;
        dest->z = a->z + b->z;
}

void f_vec4dAdd(f_vec4d *dest, const f_vec4d *a, const f_vec4d *b) {
        assert(dest != NULL);
        assert(a != NULL);
        assert(b != NULL);

        dest->a = a->a + b->a;
        dest->b = a->b + b->b;
        dest->c = a->c + b->c;
        dest->d = a->d + b->d;
}

void f_vecdDiff(f_vecd *dest, const f_vecd *a, const f_vecd *b) {
        assert((NULL != dest) && (NULL != a) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < a->size) && (i < b->size);
             ++i) {
                dest->x[i] = a->x[i] - b->x[i];
        }
}

void f_vec2dDiff(f_vec2d *dest, const f_vec2d *a, const f_vec2d *b) {
        assert(dest != NULL);
        assert(a != NULL);
        assert(b != NULL);

        dest->x = a->x - b->x;
        dest->y = a->y - b->y;
}

void f_vec3dDiff(f_vec3d *dest, const f_vec3d *a, const f_vec3d *b) {
        assert(dest != NULL);
        assert(a != NULL);
        assert(b != NULL);

        dest->x = a->x - b->x;
        dest->y = a->y - b->y;
        dest->z = a->z - b->z;
}

void f_vec4dDiff(f_vec4d *dest, const f_vec4d *a, const f_vec4d *b) {
        assert(dest != NULL);
        assert(a != NULL);
        assert(b != NULL);

        dest->a = a->a - b->a;
        dest->b = a->b - b->b;
        dest->c = a->c - b->c;
        dest->d = a->d - b->d;
}

void f_vecdIncr(f_vecd *dest, const double a, const f_vecd *b) {
        assert((NULL != dest) && (NULL != b));
        for (size_t i = 0; (i < dest->size) && (i < b->size); ++i) {
                dest->x[i] = a + b->x[i];
        }
}

void f_vec2dIncr(f_vec2d *dest, const double a, const f_vec2d *b) {
        assert(dest != NULL);
        assert(b != NULL);

        dest->x = a + b->x;
        dest->y = a + b->y;
}

void f_vec3dIncr(f_vec3d *dest, const double a, const f_vec3d *b) {
        assert(dest != NULL);
        assert(b != NULL);

        dest->x = a + b->x;
        dest->y = a + b->y;
        dest->z = a + b->z;
}

void f_vec4dIncr(f_vec4d *dest, const double a, const f_vec4d *b) {
        assert(dest != NULL);
        assert(b != NULL);

        dest->a = a + b->a;
        dest->b = a + b->b;
        dest->c = a + b->c;
        dest->d = a + b->d;
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

void f_vec2dScale(f_vec2d *dest, const double a, const f_vec2d *b) {
        assert(dest != NULL);
        assert(b != NULL);

        dest->x = a * b->x;
        dest->y = a * b->y;
}

void f_vec3dScale(f_vec3d *dest, const double a, const f_vec3d *b) {
        assert(dest != NULL);
        assert(b != NULL);

        dest->x = a * b->x;
        dest->y = a * b->y;
        dest->z = a * b->z;
}

void f_vec4dScale(f_vec4d *dest, const double a, const f_vec4d *b) {
        assert(dest != NULL);
        assert(b != NULL);

        dest->a = a * b->a;
        dest->b = a * b->b;
        dest->c = a * b->c;
        dest->d = a * b->d;
}

void f_vecdScAdd(f_vecd *dest, const double a, const f_vecd *v,
                 const f_vecd *w) {
        assert((NULL != dest) && (NULL != v) && (NULL != w));
        for (size_t i = 0; (i < dest->size) && (i < v->size) && (i < w->size);
             ++i) {
                dest->x[i] = v->x[i] + a * w->x[i];
        }
}

void f_vec2dScAdd(f_vec2d *dest, const double a, const f_vec2d *v,
                  const f_vec2d *w) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(w != NULL);

        dest->x = v->x + a * w->x;
        dest->y = v->y + a * w->y;
}

void f_vec3dScAdd(f_vec3d *dest, const double a, const f_vec3d *v,
                  const f_vec3d *w) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(w != NULL);

        dest->x = v->x + a * w->x;
        dest->y = v->y + a * w->y;
        dest->z = v->z + a * w->z;
}

void f_vec4dScAdd(f_vec4d *dest, const double a, const f_vec4d *v,
                  const f_vec4d *w) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(w != NULL);

        dest->a = v->a + a * w->a;
        dest->b = v->b + a * w->b;
        dest->c = v->c + a * w->c;
        dest->c = v->d + a * w->d;
}

void f_vecdAddSc(f_vecd *dest, const double a, const f_vecd *v,
                 const f_vecd *w) {
        assert((NULL != dest) && (NULL != v) && (NULL != w));
        for (size_t i = 0; (i < dest->size) && (i < v->size) && (i < w->size);
             ++i) {
                dest->x[i] = a * (v->x[i] + w->x[i]);
        }
}

void f_vec2dAddSc(f_vec2d *dest, const double a, const f_vec2d *v,
                  const f_vec2d *w) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(w != NULL);

        dest->x = a * (v->x + a * w->x);
        dest->y = a * (v->y + a * w->y);
}

void f_vec3dAddSc(f_vec3d *dest, const double a, const f_vec3d *v,
                  const f_vec3d *w) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(w != NULL);

        dest->x = a * (v->x + w->x);
        dest->y = a * (v->y + w->y);
        dest->z = a * (v->z + w->z);
}

void f_vec4dAddSc(f_vec4d *dest, const double a, const f_vec4d *v,
                  const f_vec4d *w) {
        assert(dest != NULL);
        assert(v != NULL);
        assert(w != NULL);

        dest->a = a * (v->a + w->a);
        dest->b = a * (v->b + w->b);
        dest->c = a * (v->c + w->c);
        dest->c = a * (v->d + w->d);
}

double f_vecdNorm(f_vecd *v) {
        assert(v != NULL);

        double norm = 0;
        for (size_t i = 0; i < v->size; ++i) {
                norm += (v->x[i] * v->x[i]);
        }

        return norm;
}

double f_vec2dNorm(f_vec2d *v) {
        return v->x * v->x + v->y * v->y;
}

double f_vec3dNorm(f_vec3d *v) {
        return v->x * v->x + v->y * v->y + v->z * v->z;
}

double f_vec4dNorm(f_vec4d *v) {
        return v->a * v->a + v->b * v->b + v->c * v->c + v->d * v->d;
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

double f_vec2dCross(const f_vec2d *a, const f_vec2d *b) {
        assert(a != NULL);
        assert(b != NULL);

        return a->x * b->y - a->y * b->x;
}

void f_vec3dCross(f_vec3d *dest, const f_vec3d *a, const f_vec3d *b) {
        assert(dest != NULL);
        assert(a != NULL);
        assert(b != NULL);

        dest->x = a->y * b->z - a->z * b->y;
        dest->y = a->z * b->x - a->x * b->z;
        dest->z = a->x * b->y - a->y * b->x;
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

void f_vec2dRotate(f_vec2d *dest, const f_vec2d *v, const double phase) {
        assert(dest != NULL);
        assert(v != NULL);

        const double vx = v->x;
        const double vy = v->y;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->x = vx * cos_phase - vy * sin_phase;
        dest->y = vx * sin_phase + vy * cos_phase;
}

void f_vec3dRotatex(f_vec3d *dest, const f_vec3d *v, const double phase) {
        assert(dest != NULL);
        assert(v != NULL);

        const double vy = v->y;
        const double vz = v->z;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->y = vy * cos_phase - vz * sin_phase;
        dest->z = vy * sin_phase + vz * sin_phase;
}

void f_vec3dRotatey(f_vec3d *dest, const f_vec3d *v, const double phase) {
        assert(dest != NULL);
        assert(v != NULL);

        const double vx = v->x;
        const double vz = v->z;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->x = vx * cos_phase + vz * sin_phase;
        dest->z = -vx * sin_phase + vz * cos_phase;
}

void f_vec3dRotatez(f_vec3d *dest, const f_vec3d *v, const double phase) {
        assert(dest != NULL);
        assert(v != NULL);

        const double vx = v->x;
        const double vy = v->z;
        const double cos_phase = cos(phase);
        const double sin_phase = sin(phase);

        dest->x = vx * cos_phase - vy * sin_phase;
        dest->y = vx * sin_phase + vy * cos_phase;
}
