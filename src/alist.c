#include <trog/dsa/alist.h>

void tr_alistCreate(tr_alloc *alloc, tr_alist *list, const size_t capacity,
                    const size_t stride) {
        list->capacity = capacity;
        list->size = 0;
        list->stride = stride;
        list->alloc = alloc;
        list->data = tr_allocPush(alloc, capacity * stride);
}

void tr_alistDestroy(tr_alist *list) {
        tr_allocFree(list->alloc, list->data);
}

void tr_alistFree(tr_alist *list) {
        tr_allocFree(list->alloc, list->data);
        tr_allocFree(list->alloc, list);
}

void tr_alistResizeElements(tr_alist *list, const size_t newCapacity) {
        tr_assert(newCapacity > list->capacity);
        void *new = tr_allocPush(list->alloc, newCapacity * list->stride);
        memcpy(new, list->data, list->size * list->stride);

        tr_allocFree(list->alloc, list->data);
        list->data = new;
        list->capacity = newCapacity;
}

void *tr_alistIdx(const tr_alist *list, const size_t i) {
        tr_assert(i < list->size);
        return (int8_t *)list->data + list->stride * i;
}

void *tr_alistIdxBack(const tr_alist *list, const size_t i) {
        tr_assert(i <= list->size);
        return (int8_t *)list->data + list->stride * (list->size - i);
}

void *tr_alistNext(tr_alist *list) {
        if (list->capacity < list->size + 1) {
                tr_alistResizeElements(list, 2 * (list->size + 1));
        }

        void *dest = tr_alistIdx(list, list->size);
        ++list->size;
        return dest;
}

void *tr_alistPushback(tr_alist *list, const void *elem) {
        tr_assert(list != NULL);
        tr_assert(elem != NULL);
        void *dest = tr_alistNext(list);
        memcpy(dest, elem, list->stride);
        return dest;
}

void *tr_alistNextArray(tr_alist *list, const size_t number) {
        tr_assert(list != NULL);
        if (list->capacity <= list->size + number) {
                tr_alistResizeElements(list, 2 * (list->size + number));
        }

        void *dest = tr_alistIdx(list, list->size);
        list->size += number;
        return dest;
}

void *tr_alistPushbackArray(tr_alist *list, const void *elem,
                            const size_t number) {
        tr_assert(list != NULL);
        tr_assert(elem != NULL);
        void *dest = tr_alistNextArray(list, number);

        memcpy(dest, elem, list->stride * number);
        return dest;
}
