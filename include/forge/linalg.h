#ifndef LINALG_H
#define LINALG_H

#include <forge.h>
#include <openblas/cblas.h>
#include <stdio.h>
#include <string.h>
#include <forge/mem/alloc.h>

// Vectors
typedef struct {
        size_t size;
        double *x;
} f_vecd;

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

void f_vecdAdd(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vecdDiff(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vecdIncr(f_vecd *dest, const double a, const f_vecd *b);

void f_vecdScale(f_vecd *dest, const double a, const f_vecd *b);

void f_vecdEmul(f_vecd *dest, const double a, const f_vecd *x, const f_vecd *y);

double f_vecdMul(const f_vecd *a, const f_vecd *b);

void f_vecdCross(f_vecd *dest, const f_vecd *a, const f_vecd *b);

// Element procs
size_t f_vecdIMin(const f_vecd *v);

double *f_vecdMin(const f_vecd *v);

size_t f_vecdIMax(const f_vecd *v);

double *f_vecdMax(const f_vecd *v);

void f_vecdOne(f_vecd *vec);

double f_vecdNorm(const f_vecd *v);

void f_vecdENorm(f_vecd *dest, const f_vecd **vecs, const size_t nvecs);

void f_vecdEMean(f_vecd *dest, const f_vecd **vecs, const size_t nvecs);

double f_vecdMean(const f_vecd *v);

double f_vecdSum(const f_vecd *v);

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

void f_matdColCpy(f_vecd *dest, const f_matd *m, const size_t c, size_t stride);

void f_matdRowCpy(f_vecd *dest, const f_matd *m, const size_t r, size_t stride);

void f_matdCol(f_vecd *dest, const f_matd *m, const size_t c);

#warning needs testing
void f_matdColslice(f_matd *dest, const f_matd *m, const size_t fromCol,
                    const size_t toCol);

void f_matdOne(f_matd *m);

void f_matdZero(f_matd *m);

void f_matdIdent(f_matd *m);

#warning needs testing
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
