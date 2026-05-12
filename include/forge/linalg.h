#ifndef LINALG_H
#define LINALG_H

#include <forge.h>
#include <openblas/cblas.h>
#include <forge/mem/alloc.h>

// Vectors
typedef struct {
        size_t size;
        double *x;
} f_vecd;

typedef union {
        PACKED_START
        struct {
                double x;
                double y;
        } PACKED_END;
        double array[2];
} f_vec2d;

typedef union {
        PACKED_START
        struct {
                double x;
                double y;
                double z;
        } PACKED_END;
        double array[3];
} f_vec3d;

typedef union {
        PACKED_START
        struct {
                double a;
                double b;
                double c;
                double d;
        } PACKED_END;
        double array[4];
} f_vec4d;

// data procs
f_vecd *f_vecdAlloc(f_alloc *alloc, size_t size);

f_vecd *f_vecdAllocZero(f_alloc *alloc, size_t size);

static inline f_vecd *f_vecdAllocLike(f_alloc *alloc, f_vecd *source) {
        assert(source != NULL);
        return f_vecdAlloc(alloc, source->size);
}

static inline f_vecd *f_vecdAllocZeroLike(f_alloc *alloc, f_vecd *source) {
        assert(source != NULL);
        return f_vecdAllocZero(alloc, source->size);
}

void f_vecdFree(f_alloc *alloc, f_vecd *vector);

double *f_vecdIdx(const f_vecd *v, size_t i);

void f_vecdPrint(const f_vecd *v);

void f_vecdCopy(f_vecd *dest, const f_vecd *source);

void f_vecdSlice(f_vecd *dest, const f_vecd *source, const size_t from,
                 const size_t to);

// linear alg procs
void f_vecdZero(f_vecd *vec);

void f_vecdArange(f_vecd *v, const double scale);

void f_vecdLinspace(f_vecd *v, const double start, const double stop);

// vector ops
// v + w
void f_vecdAdd(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vec2dAdd(f_vec2d *dest, const f_vec2d *a, const f_vec2d *b);

void f_vec3dAdd(f_vec3d *dest, const f_vec3d *a, const f_vec3d *b);

void f_vec4dAdd(f_vec4d *dest, const f_vec4d *a, const f_vec4d *b);

// v - w
void f_vecdDiff(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vec2dDiff(f_vec2d *dest, const f_vec2d *a, const f_vec2d *b);

void f_vec3dDiff(f_vec3d *dest, const f_vec3d *a, const f_vec3d *b);

void f_vec4dDiff(f_vec4d *dest, const f_vec4d *a, const f_vec4d *b);

// v + a
void f_vecdIncr(f_vecd *dest, const double a, const f_vecd *b);

void f_vec2dIncr(f_vec2d *dest, const double a, const f_vec2d *b);

void f_vec3dIncr(f_vec3d *dest, const double a, const f_vec3d *b);

void f_vec4dIncr(f_vec4d *dest, const double a, const f_vec4d *b);

// a * v
void f_vecdScale(f_vecd *dest, const double a, const f_vecd *b);

void f_vec2dScale(f_vec2d *dest, const double a, const f_vec2d *b);

void f_vec3dScale(f_vec3d *dest, const double a, const f_vec3d *b);

void f_vec4dScale(f_vec4d *dest, const double a, const f_vec4d *b);

// a * (v + w)
void f_vecdAddSc(f_vecd *dest, const double a, const f_vecd *v,
                 const f_vecd *w);

void f_vec2dAddSc(f_vec2d *dest, const double a, const f_vec2d *v,
                  const f_vec2d *w);

void f_vec3dAddSc(f_vec3d *dest, const double a, const f_vec3d *v,
                  const f_vec3d *w);

void f_vec4dAddSc(f_vec4d *dest, const double a, const f_vec4d *v,
                  const f_vec4d *w);

// v + a * w
void f_vecdScAdd(f_vecd *dest, const f_vecd *v, const double a,
                 const f_vecd *w);

void f_vec2dScAdd(f_vec2d *dest, const f_vec2d *v, const double a,
                  const f_vec2d *w);

void f_vec3dScAdd(f_vec3d *dest, const f_vec3d *v, const double a,
                  const f_vec3d *w);

void f_vec4dScAdd(f_vec4d *dest, const f_vec4d *v, const double a,
                  const f_vec4d *w);

void f_vecdEmul(f_vecd *dest, const double a, const f_vecd *x, const f_vecd *y);

double f_vecdMul(const f_vecd *a, const f_vecd *b);

// Element procs
size_t f_vecdIMin(const f_vecd *v);

double *f_vecdMin(const f_vecd *v);

size_t f_vecdIMax(const f_vecd *v);

double *f_vecdMax(const f_vecd *v);

void f_vecdOne(f_vecd *vec);

void f_vecdENorm(f_vecd *dest, const f_vecd **vecs, const size_t nvecs);

void f_vecdEMean(f_vecd *dest, const f_vecd **vecs, const size_t nvecs);

double f_vecdMean(const f_vecd *v);

double f_vecdSum(const f_vecd *v);

void f_vecdCross(f_vecd *dest, const f_vecd *a, const f_vecd *b);

// w x w
double f_vec2dCross(const f_vec2d *a, const f_vec2d *b);

void f_vec3dCross(f_vec3d *dest, const f_vec3d *a, const f_vec3d *b);

// |v|
double f_vecdNorm(f_vecd *v);

double f_vec2dNorm(f_vec2d *v);

double f_vec3dNorm(f_vec3d *v);

double f_vec4dNorm(f_vec4d *v);

// R(phase) dot v
void f_vec2dRotate(f_vec2d *dest, const f_vec2d *v, const double phase);

void f_vec3dRotatex(f_vec3d *dest, const f_vec3d *v, const double phase);

void f_vec3dRotatey(f_vec3d *dest, const f_vec3d *v, const double phase);

void f_vec3dRotatez(f_vec3d *dest, const f_vec3d *v, const double phase);

// Matrices
typedef struct {
        // column major
        size_t cols;
        size_t rows;
        double *x;
} f_matd;

f_matd *f_matdAlloc(f_alloc *alloc, size_t rows, size_t cols);

f_matd *f_matdAllocZero(f_alloc *alloc, size_t rows, size_t cols);

static inline f_matd *f_matdAllocLike(f_alloc *alloc, f_matd *source) {
        assert(source != NULL);
        return f_matdAlloc(alloc, source->rows, source->cols);
}

static inline f_matd *f_matdAllocLikeZero(f_alloc *alloc, f_matd *source) {
        assert(source != NULL);
        return f_matdAllocZero(alloc, source->rows, source->cols);
}

void f_matdFree(f_alloc *alloc, f_matd *m);

double *f_matdIdx(const f_matd *m, const size_t r, const size_t c);

bool f_matdIsTranspose(f_matd *m0, f_matd *m1);

void f_matdTranspose(f_matd *dest, const f_matd *m);

void f_matdCopy(f_matd *dest, f_matd *source);

void f_vec2dCopy(f_vec2d *dest, const f_vec2d *source);

void f_vec3dCopy(f_vec3d *dest, const f_vec3d *source);

void f_vec4dCopy(f_vec4d *dest, const f_vec4d *source);

void f_matdColCpy(f_vecd *dest, const f_matd *m, const size_t c, size_t stride);

void f_matdRowCpy(f_vecd *dest, const f_matd *m, const size_t r, size_t stride);

void f_matdCol(f_vecd *dest, const f_matd *m, const size_t c);

f_vec2d *f_matdColv2(const f_matd *m, const size_t c);

f_vec3d *f_matdColv3(const f_matd *m, const size_t c);

f_vec4d *f_matdColv4(const f_matd *m, const size_t c);

void f_matdColslice(f_matd *dest, const f_matd *m, const size_t fromCol,
                    const size_t toCol);

void f_matdOne(f_matd *m);

void f_matdZero(f_matd *m);

void f_matdIdent(f_matd *m);

void f_matdScale(f_matd *dest, f_matd *m, double a);

void f_matdIncr(f_matd *dest, f_matd *m, double a);

void f_matdAdd(f_matd *dest, f_matd *m, f_matd *n);

void f_matdScAdd(f_matd *dest, f_matd *m, double a, f_matd *n);

void f_matdMVMul(f_vecd *dest, const f_matd *m, const f_vecd *v,
                 const double a);

void f_matdMMul(f_matd *dest, const double alpha, const f_matd *a,
                const f_matd *b);

void f_matdPrint(f_matd *m);

#endif
