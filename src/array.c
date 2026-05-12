#include <forge.h>
#include <forge/dsa/array.h>

void f_arrayCreate(f_alloc *alloc, f_array *array, const size_t size,
                   const size_t stride) {
        array->size = 0;
        array->stride = stride;
        array->data = f_allocPush(alloc, size * stride);
}

void f_arrayDestroy(f_alloc *alloc, f_array *array) {
        f_allocFree(alloc, array->data);
}

void f_arrayFree(f_alloc *alloc, f_array *array) {
        f_allocFree(alloc, array->data);
        f_allocFree(alloc, array);
}

void *f_arrayIdx(const f_array *array, const size_t i) {
        return (int8_t *)array->data + array->stride * i;
}
