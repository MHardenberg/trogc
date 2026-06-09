#include <trog/tensor.h>

tr_tens3d *tr_tens3dAlloc(tr_alloc *alloc, const size_t rows, const size_t cols,
                          const size_t layers) {
        tr_assert(alloc != NULL);
        tr_tens3d *dest = tr_allocPush(alloc, sizeof(tr_tens3d));
        dest->x = tr_allocPush(alloc, sizeof(double) * cols * rows * layers);
        dest->rows = rows;
        dest->cols = cols;
        dest->layers = layers;
        return dest;
}

tr_tens3d *tr_tens3dAllocZero(tr_alloc *alloc, const size_t rows,
                              const size_t cols, const size_t layers) {
        tr_assert(alloc != NULL);
        tr_tens3d *dest = tr_allocPush(alloc, sizeof(tr_tens3d));
        dest->x =
            tr_allocPushZero(alloc, sizeof(double) * cols * rows * layers);
        dest->rows = rows;
        dest->cols = cols;
        dest->layers = layers;
        return dest;
}

tr_tens3d *tr_tens3dAllocLike(tr_alloc *alloc, const tr_tens3d *source) {
        tr_assert(alloc != NULL);
        tr_assert(source != NULL);
        return tr_tens3dAlloc(alloc, source->rows, source->cols,
                              source->layers);
}

tr_tens3d *tr_tens3dAllocLikeZero(tr_alloc *alloc, const tr_tens3d *source) {
        tr_assert(alloc != NULL);
        tr_assert(source != NULL);
        return tr_tens3dAllocZero(alloc, source->rows, source->cols,
                                  source->layers);
}

void tr_tens3dCopy(tr_tens3d *dest, tr_tens3d *source) {
        tr_assert(dest != NULL);
        tr_assert(source != NULL);
        tr_assert((dest->rows * dest->cols * dest->layers) ==
                  (source->rows * source->cols * source->layers));
        dest->cols = source->cols;
        dest->rows = source->rows;
        dest->layers = source->layers;
        memcpy(dest->x, source->x,
               sizeof(double) * dest->cols * dest->rows * dest->layers);
}

tr_tens3d *tr_tens3dAllocCpy(tr_alloc *alloc, tr_tens3d *source) {
        tr_assert(alloc != NULL);
        tr_assert(source != NULL);
        tr_tens3d *dest = tr_tens3dAllocLike(alloc, source);
        tr_tens3dCopy(dest, source);
        return dest;
}

void tr_tens3dFree(tr_alloc *alloc, tr_tens3d *t) {
        tr_assert(alloc != NULL);
        tr_assert(t != NULL);
        tr_allocFree(alloc, t->x);
        tr_allocFree(alloc, t);
}

double *tr_tens3dIdx(const tr_tens3d *t, const size_t row, const size_t col,
                     const size_t layer) {
        tr_assert(t != NULL);
        tr_assert(row < t->rows);
        tr_assert(col < t->cols);
        tr_assert(layer < t->layers);
        const size_t layerOffset = layer * t->cols * t->rows;
        const size_t columnOffset = col * t->rows;
        return t->x + layerOffset + columnOffset + row;
}
