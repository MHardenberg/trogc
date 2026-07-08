#ifndef _TENSOR_H
#define _TENSOR_H

#include <trog/mem/alloc.h>
#include <trog.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
        // m x n x p
        // final dim -> first dim major
        size_t rows, cols, layers;
        double *x;
} tr_tens3d;

tr_tens3d *tr_tens3dAlloc(tr_alloc *alloc, const size_t rows, const size_t cols,
                          const size_t layers);

tr_tens3d *tr_tens3dAllocZero(tr_alloc *alloc, const size_t rows,
                              const size_t cols, const size_t layers);

tr_tens3d *tr_tens3dAllocLike(tr_alloc *alloc, const tr_tens3d *source);

tr_tens3d *tr_tens3dAllocLikeZero(tr_alloc *alloc, const tr_tens3d *source);

void tr_tens3dCopy(tr_tens3d *dest, tr_tens3d *source);

tr_tens3d *tr_tens3dAllocCpy(tr_alloc *alloc, tr_tens3d *source);

void tr_tens3dFree(tr_alloc *alloc, tr_tens3d *t);

double *tr_tens3dIdx(const tr_tens3d *t, const size_t row, const size_t col,
                     const size_t layer);

#ifdef __cplusplus
}
#endif

#endif // _TENSOR_H
