#ifndef LINALG_H
#define LINALG_H

#include <trog.h>
#include <openblas/cblas.h>
#include <trog/mem/alloc.h>

// Vectors
typedef struct {
        size_t size;
        double *x;
} tr_vecd;

typedef union {
        PACKED_START
        struct {
                double x;
                double y;
        } PACKED_END;
        double array[2];
} tr_vec2d;

typedef union {
        PACKED_START
        struct {
                double x;
                double y;
                double z;
        } PACKED_END;
        double array[3];
} tr_vec3d;

typedef union {
        PACKED_START
        struct {
                double a;
                double b;
                double c;
                double d;
        } PACKED_END;
        double array[4];
} tr_vec4d;
void tr_vecdPrint(const tr_vecd *v);
void tr_vec2dPrint(const tr_vec2d *v);
void tr_vec3dPrint(const tr_vec3d *v);
void tr_vec4dPrint(const tr_vec4d *v);

// data procs
tr_vecd *tr_vecdAlloc(tr_alloc *alloc, size_t size);
tr_vecd *tr_vecdAllocZero(tr_alloc *alloc, size_t size);
tr_vecd *tr_vecdAllocArray(tr_alloc *alloc, size_t size, const double *array);
tr_vecd *tr_vecdAllocCpy(tr_alloc *alloc, const tr_vecd *source);
tr_vecd *tr_vecdAllocLike(tr_alloc *alloc, tr_vecd *source);
tr_vecd *tr_vecdAllocZeroLike(tr_alloc *alloc, tr_vecd *source);
void tr_vecdFree(tr_alloc *alloc, tr_vecd *vector);

double *tr_vecdIdx(const tr_vecd *v, size_t i);

void tr_vecdCopy(tr_vecd *dest, const tr_vecd *source);
void tr_vec2dCopy(tr_vec2d *dest, const tr_vec2d *source);
void tr_vec3dCopy(tr_vec3d *dest, const tr_vec3d *source);
void tr_vec4dCopy(tr_vec4d *dest, const tr_vec4d *source);

void tr_vecdSlice(tr_vecd *dest, const tr_vecd *source, const size_t from,
                  const size_t to);

// linear alg procs
void tr_vecdZero(tr_vecd *vec);
void tr_vecdOne(tr_vecd *vec);
void tr_vecdArange(tr_vecd *v, const double scale);
void tr_vecdLinspace(tr_vecd *v, const double start, const double stop);
void tr_vecdLogspace(tr_vecd *v, const double startExp, const double stopExp,
                     const double base);

// vector ops
// v + w
void tr_vecdAdd(tr_vecd *dest, const tr_vecd *a, const tr_vecd *b);
void tr_vec2dAdd(tr_vec2d *dest, const tr_vec2d *a, const tr_vec2d *b);
void tr_vec3dAdd(tr_vec3d *dest, const tr_vec3d *a, const tr_vec3d *b);
void tr_vec4dAdd(tr_vec4d *dest, const tr_vec4d *a, const tr_vec4d *b);

// v - w
void tr_vecdDiff(tr_vecd *dest, const tr_vecd *a, const tr_vecd *b);
void tr_vec2dDiff(tr_vec2d *dest, const tr_vec2d *a, const tr_vec2d *b);
void tr_vec3dDiff(tr_vec3d *dest, const tr_vec3d *a, const tr_vec3d *b);
void tr_vec4dDiff(tr_vec4d *dest, const tr_vec4d *a, const tr_vec4d *b);

// v + a
void tr_vecdIncr(tr_vecd *dest, const double a, const tr_vecd *b);
void tr_vec2dIncr(tr_vec2d *dest, const double a, const tr_vec2d *b);
void tr_vec3dIncr(tr_vec3d *dest, const double a, const tr_vec3d *b);
void tr_vec4dIncr(tr_vec4d *dest, const double a, const tr_vec4d *b);

// a * v
void tr_vecdScale(tr_vecd *dest, const double a, const tr_vecd *b);
void tr_vec2dScale(tr_vec2d *dest, const double a, const tr_vec2d *b);
void tr_vec3dScale(tr_vec3d *dest, const double a, const tr_vec3d *b);
void tr_vec4dScale(tr_vec4d *dest, const double a, const tr_vec4d *b);

// a * (v + w)
void tr_vecdAddSc(tr_vecd *dest, const double a, const tr_vecd *v,
                  const tr_vecd *w);
void tr_vec2dAddSc(tr_vec2d *dest, const double a, const tr_vec2d *v,
                   const tr_vec2d *w);
void tr_vec3dAddSc(tr_vec3d *dest, const double a, const tr_vec3d *v,
                   const tr_vec3d *w);
void tr_vec4dAddSc(tr_vec4d *dest, const double a, const tr_vec4d *v,
                   const tr_vec4d *w);

// v + a * w
void tr_vecdScAdd(tr_vecd *dest, const tr_vecd *v, const double a,
                  const tr_vecd *w);
void tr_vec2dScAdd(tr_vec2d *dest, const tr_vec2d *v, const double a,
                   const tr_vec2d *w);
void tr_vec3dScAdd(tr_vec3d *dest, const tr_vec3d *v, const double a,
                   const tr_vec3d *w);
void tr_vec4dScAdd(tr_vec4d *dest, const tr_vec4d *v, const double a,
                   const tr_vec4d *w);

void tr_vecdEmul(tr_vecd *dest, const double a, const tr_vecd *x,
                 const tr_vecd *y);
void tr_vecdENorm(tr_vecd *dest, const tr_vecd **vecs, const size_t nvecs);
void tr_vecdEMean(tr_vecd *dest, const tr_vecd **vecs, const size_t nvecs);

double tr_vecdMean(const tr_vecd *v);
double tr_vecdSum(const tr_vecd *v);
double tr_vecdDot(const tr_vecd *a, const tr_vecd *b);
double tr_vec4dDot(const tr_vec4d *a, const tr_vec4d *b);
double tr_vec3dDot(const tr_vec3d *a, const tr_vec3d *b);
double tr_vec2dDot(const tr_vec2d *a, const tr_vec2d *b);

// Element procs
size_t tr_vecdIMin(const tr_vecd *v);
double tr_vecdMin(const tr_vecd *v);
size_t tr_vecdIMax(const tr_vecd *v);
double tr_vecdMax(const tr_vecd *v);

// w x w
void tr_vecdCross(tr_vecd *dest, const tr_vecd *a, const tr_vecd *b);
double tr_vec2dCross(const tr_vec2d *a, const tr_vec2d *b);
void tr_vec3dCross(tr_vec3d *dest, const tr_vec3d *a, const tr_vec3d *b);

// |v|
double tr_vecdNorm(tr_vecd *v);
double tr_vec2dNorm(tr_vec2d *v);
double tr_vec3dNorm(tr_vec3d *v);
double tr_vec4dNorm(tr_vec4d *v);

// R(phase) dot v
void tr_vec2dRotate(tr_vec2d *dest, const tr_vec2d *v, const double phase);
void tr_vec3dRotatex(tr_vec3d *dest, const tr_vec3d *v, const double phase);
void tr_vec3dRotatey(tr_vec3d *dest, const tr_vec3d *v, const double phase);
void tr_vec3dRotatez(tr_vec3d *dest, const tr_vec3d *v, const double phase);

// Matrices
typedef struct {
        // column major
        size_t cols;
        size_t rows;
        double *x;
} tr_matd;
void tr_matdPrint(tr_matd *m);

tr_matd *tr_matdAlloc(tr_alloc *alloc, size_t rows, size_t cols);
tr_matd *tr_matdAllocZero(tr_alloc *alloc, size_t rows, size_t cols);
tr_matd *tr_matdAllocCpy(tr_alloc *alloc, tr_matd *source);
tr_matd *tr_matdAllocLike(tr_alloc *alloc, tr_matd *source);
tr_matd *tr_matdAllocLikeZero(tr_alloc *alloc, tr_matd *source);
void tr_matdFree(tr_alloc *alloc, tr_matd *m);

double *tr_matdIdx(const tr_matd *m, const size_t r, const size_t c);

bool tr_matdIsTranspose(tr_matd *m0, tr_matd *m1);
void tr_matdTranspose(tr_matd *dest, const tr_matd *m);

void tr_matdCopy(tr_matd *dest, tr_matd *source);
void tr_matdColCpy(tr_vecd *dest, const tr_matd *m, const size_t c,
                   size_t stride);
void tr_matdRowCpy(tr_vecd *dest, const tr_matd *m, const size_t r,
                   size_t stride);
void tr_matdCol(tr_vecd *dest, const tr_matd *m, const size_t c);

tr_vec2d *tr_matdColv2(const tr_matd *m, const size_t c);
tr_vec3d *tr_matdColv3(const tr_matd *m, const size_t c);
tr_vec4d *tr_matdColv4(const tr_matd *m, const size_t c);

void tr_mat2NdRotCols(tr_matd *m, const tr_vecd *stepwise_phase,
                      const double const_phase);
void tr_mat3NdRotColsx(tr_matd *m, const tr_vecd *stepwise_phase,
                       const double const_phase);
void tr_mat3NdRotColsy(tr_matd *m, const tr_vecd *stepwise_phase,
                       const double const_phase);

void tr_mat2NCrossCols(tr_vecd *dest, const tr_matd *m, const tr_matd *n);
void tr_mat3NCrossCols(tr_matd *dest, const tr_matd *m, const tr_matd *n);

void tr_mat3NdRotColsz(tr_matd *m, const tr_vecd *stepwise_phase,
                       const double const_phase);

void tr_matdColslice(tr_matd *dest, const tr_matd *m, const size_t fromCol,
                     const size_t toCol);

void tr_matdOne(tr_matd *m);
void tr_matdZero(tr_matd *m);
void tr_matdIdent(tr_matd *m);

void tr_matdScale(tr_matd *dest, tr_matd *m, double a);
void tr_matdIncr(tr_matd *dest, tr_matd *m, double a);
void tr_matdAdd(tr_matd *dest, tr_matd *m, tr_matd *n);
void tr_matdScAdd(tr_matd *dest, tr_matd *m, double a, tr_matd *n);

void tr_matdMVMul(tr_vecd *dest, const tr_matd *m, const tr_vecd *v,
                  const double a);
void tr_matdMMul(tr_matd *dest, const double alpha, const tr_matd *a,
                 const tr_matd *b);

#endif
