#include <trog.h>
#include <trog/dsa/array.h>

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
