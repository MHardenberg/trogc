#ifndef ARRAY_H
#define ARRAY_H

#include <forge.h>
#include <forge/mem/alloc.h>

typedef struct {
        size_t size;
        size_t stride;
        void *data;
} f_array;

void f_arrayCreate(f_alloc *alloc, f_array *array, const size_t size,
                   const size_t stride);

void f_arrayDestroy(f_alloc *alloc, f_array *array);

void f_arrayFree(f_alloc *alloc, f_array *array);

void *f_arrayIdx(const f_array *array, const size_t i);

#endif // ARRAY_H
