#ifndef LINALG_H
#define LINALG_H

#include <forge.h>
#include <openblas/cblas.h>
#include <stdio.h>
#include <string.h>
// Vectors
typedef struct {
        size_t size;
        double *x;
} f_vecd;
#define f_vecdSize(n)                                                          \
        (sizeof(f_vecd) + n * sizeof(double)) // for assigning continuous

// Matrices
typedef struct {
        // column major
        size_t cols;
        size_t rows;
        double *x;
} f_matd;
#define f_matdSize(c, r)                                                       \
        (sizeof(f_matd) + c * r * sizeof(double)) // for assigning continuous

double *f_vecdIdx(const f_vecd *v, size_t i);

void f_vecdAssingContinuous(f_vecd *dest, size_t n);

void f_vecdOnes(f_vecd *vec);

void f_vecdZeros(f_vecd *vec);

void f_vecdAdd(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vecdIncr(f_vecd *dest, const double a, const f_vecd *b);

void f_vecdScale(f_vecd *dest, const double a, const f_vecd *b);

void f_vecdEmul(f_vecd *dest, const double a, const f_vecd *x, const f_vecd *y);

double f_vecdMul(const f_vecd *a, const f_vecd *b);

void f_vecdCross(f_vecd *dest, const f_vecd *a, const f_vecd *b);

void f_vecdPrint(const f_vecd *v);

// Matrices
double *f_matdIdx(const f_matd *m, const size_t r, const size_t c);

void f_matdCol(f_vecd *dest, const f_matd *m, const size_t c);

void f_matdOnes(f_matd *m);

void f_matdZeros(f_matd *m);

void f_matdIdent(f_matd *m);

void f_matdMVMul(f_vecd *dest, const f_matd *m, const f_vecd *v,
                 const double a);

void f_matdMMul(f_matd *dest, const double alpha, const f_matd *a,
                const f_matd *b);

void f_matdPrint(f_matd *m);

void f_matdAssingContinuous(f_matd *dest, size_t c, size_t r);
#endif
