#ifndef ARRAY_H
#define ARRAY_H

#include <trog.h>
#include <trog/mem/alloc.h>

typedef struct {
        size_t size;
        size_t stride;
        void *data;
} tr_array;

void tr_arrayCreate(tr_alloc *alloc, tr_array *array, const size_t size,
                    const size_t stride);

void tr_arrayDestroy(tr_alloc *alloc, tr_array *array);

void tr_arrayFree(tr_alloc *alloc, tr_array *array);

void *tr_arrayIdx(const tr_array *array, const size_t i);

#endif // ARRAY_H
