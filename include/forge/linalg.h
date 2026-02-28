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

f_vecd *f_vecdAlloc(f_alloc *alloc, size_t size);

f_vecd *f_vecdAllocZero(f_alloc *alloc, size_t size);

void f_vecdFree(f_alloc *alloc, f_vecd *vector);

void f_vecdCopy(f_vecd *dest, f_vecd *source);

void f_vecdSlice(f_vecd *dest, f_vecd *source, size_t from, size_t to);

double *f_vecdIdx(const f_vecd *v, size_t i);

size_t f_vecdIMin(const f_vecd *v);

double *f_vecdMin(const f_vecd *v);

size_t f_vecdIMax(const f_vecd *v);

double *f_vecdMax(const f_vecd *v);

void f_vecdOne(f_vecd *vec);

void f_vecdZero(f_vecd *vec);

void f_vecdArange(f_vecd *v, const double start, const double stop);

void f_vecdAdd(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vecdIncr(f_vecd *dest, const double a, const f_vecd *b);

void f_vecdScale(f_vecd *dest, const double a, const f_vecd *b);

void f_vecdEmul(f_vecd *dest, const double a, const f_vecd *x, const f_vecd *y);

double f_vecdMul(const f_vecd *a, const f_vecd *b);

void f_vecdCross(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vecdPrint(const f_vecd *v);

// Matrices
typedef struct {
        // column major
        size_t cols;
        size_t rows;
        double *x;
} f_matd;

f_matd *f_matdAlloc(f_alloc *alloc, size_t cols, size_t rows);

f_matd *f_matdAllocZero(f_alloc *alloc, size_t cols, size_t rows);

void f_matdFree(f_alloc *alloc, f_matd *m);

double *f_matdIdx(const f_matd *m, const size_t r, const size_t c);

void f_matdCopy(f_matd *dest, f_matd *source);

void f_matdCol(f_vecd *dest, const f_matd *m, const size_t c);

void f_matdOne(f_matd *m);

void f_matdZero(f_matd *m);

void f_matdIdent(f_matd *m);

void f_matdMVMul(f_vecd *dest, const f_matd *m, const f_vecd *v,
                 const double a);

void f_matdMMul(f_matd *dest, const double alpha, const f_matd *a,
                const f_matd *b);

void f_matdPrint(f_matd *m);

#endif
