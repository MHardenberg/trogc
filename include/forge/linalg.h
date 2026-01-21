#ifndef LINALG_H
#define LINALG_H

#include <forge.h>
#include <stdio.h>
#include <string.h>
// Vectors
typedef struct {
        size_t size;
        double *x;
} f_vecd;
#define f_vecdSize(n) (sizeof(f_vecd) + n*sizeof(double) // for assigning continuous

void f_vecdAssingContinuous(f_vecd *dest, size_t n);

void f_vecdOnes(f_vecd *vec);

void f_vecdZeros(f_vecd *vec);

double *f_vecdIdx(f_vecd *v, size_t i);

void f_vecdAdd(f_vecd *dest, f_vecd *a, f_vecd *b);

void f_vecdIncr(f_vecd *dest, double a, f_vecd *b);

void f_vecdEmul(f_vecd *dest, const double a, f_vecd *x, f_vecd *y);

void f_vecdScale(f_vecd *dest, double a, f_vecd *b);

double f_vecdMul(f_vecd *a, f_vecd *b);

void f_vecdCross(f_vecd *dest, f_vecd *a, f_vecd *b);

void f_vecdPrint(f_vecd *v);

// Matrices
typedef struct {
        // column major
        size_t cols;
        size_t rows;
        double *x;
} f_matd;
#define f_matdSize(c, r) (sizeof(f_matd) + c*r*sizeof(double) // for assigning continuous

void f_matdAssingContinuous(f_matd *dest, size_t c, size_t r);

double *f_matdIdx(f_matd *m, size_t c, size_t r);

void f_matdOnes(f_matd *m);

void f_matdZeros(f_matd *m);

int f_matdIdent(f_matd *m);

void f_matdMVMul(f_vecd *dest, f_matd *m, f_vecd *v, double a, double b);

double f_vecdMul(f_vecd *a, f_vecd *b);

void f_matdPrint(f_matd *m);
#endif
