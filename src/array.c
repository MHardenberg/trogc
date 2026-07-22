#include "trog/mem/alloc.h"
#include <trog.h>
#include <trog/dsa/array.h>

tr_array *tr_arrayAlloc(tr_alloc *alloc, const size_t size,
                        const size_t stride) {
        tr_array *array = tr_allocPush(alloc, sizeof(tr_array));
        array->size = 0;
        array->stride = stride;
        array->data = tr_allocPush(alloc, size * stride);

        return array;
}

tr_array *tr_arrayAllocZero(tr_alloc *alloc, const size_t size,
                            const size_t stride) {
        tr_array *array = tr_allocPush(alloc, sizeof(tr_array));
        array->size = 0;
        array->stride = stride;
        array->data = tr_allocPushZero(alloc, size * stride);

        return array;
}

void tr_arrayCreate(tr_alloc *alloc, tr_array *array, const size_t size,
                    const size_t stride) {
        array->size = 0;
        array->stride = stride;
        array->data = tr_allocPush(alloc, size * stride);
}

void tr_arrayDestroy(tr_alloc *alloc, tr_array *array) {
        tr_allocFree(alloc, array->data);
}

void tr_arrayFree(tr_alloc *alloc, tr_array *array) {
        tr_allocFree(alloc, array->data);
        tr_allocFree(alloc, array);
}

void *tr_arrayIdx(const tr_array *array, const size_t i) {
        return (int8_t *)array->data + array->stride * i;
}
