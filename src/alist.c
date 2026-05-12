#include <forge/dsa/alist.h>

void f_alistCreate(f_alloc *alloc, f_alist *list, const size_t capacity,
                   const size_t stride) {
        list->capacity = capacity;
        list->size = 0;
        list->stride = stride;
        list->alloc = alloc;
        list->data = f_allocPush(alloc, capacity * stride);
}

void f_alistDestroy(f_alist *list) {
        f_allocFree(list->alloc, list->data);
}

void f_alistFree(f_alist *list) {
        f_allocFree(list->alloc, list->data);
        f_allocFree(list->alloc, list);
}

void f_alistResizeElements(f_alist *list, const size_t newCapacity) {
        f_assert(newCapacity > list->capacity);
        void *new = f_allocPush(list->alloc, newCapacity * list->stride);
        memcpy(new, list->data, list->size * list->stride);

        f_allocFree(list->alloc, list->data);
        list->data = new;
        list->capacity = newCapacity;
}

void *f_alistIdx(const f_alist *list, const size_t i) {
        return (int8_t *)list->data + list->stride * i;
}

void *f_alistNext(f_alist *list) {
        if (list->capacity < list->size + 1) {
                f_alistResizeElements(list, 2 * (list->size + 1));
        }

        void *dest = f_alistIdx(list, list->size);
        ++list->size;
        return dest;
}

void *f_alistPushback(f_alist *list, const void *elem) {
        f_assert(list != NULL);
        f_assert(elem != NULL);
        void *dest = f_alistNext(list);
        memcpy(dest, elem, list->stride);
        return dest;
}

void *f_alistNextArray(f_alist *list, const size_t number) {
        f_assert(list != NULL);
        if (list->capacity <= list->size + number) {
                f_alistResizeElements(list, 2 * (list->size + number));
        }

        void *dest = f_alistIdx(list, list->size);
        list->size += number;
        return dest;
}

void *f_alistPushbackArray(f_alist *list, const void *elem,
                           const size_t number) {
        f_assert(list != NULL);
        f_assert(elem != NULL);
        void *dest = f_alistNextArray(list, number);

        memcpy(dest, elem, list->stride * number);
        return dest;
}
