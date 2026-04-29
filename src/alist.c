#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <forge/dsa/alist.h>

void f_alistCreate(f_alloc *alloc, f_alist *list, size_t capacity,
                   size_t element_size) {
        list->capacity = capacity;
        list->size = 0;
        list->element_size = element_size;
        list->alloc = alloc;
        list->data = f_allocPush(alloc, capacity * element_size);
}

void f_alistDestroy(f_alist *list) {
        f_allocFree(list->alloc, list->data);
}

void f_alistResizeElements(f_alist *list, size_t newCapacity) {
        assert(newCapacity > list->capacity);
        void *new = f_allocPush(list->alloc, newCapacity * list->element_size);
        memcpy(new, list->data, list->size * list->element_size);

        f_allocFree(list->alloc, list->data);
        list->data = new;
        list->capacity = newCapacity;
}

void *f_alistIdx(f_alist *list, size_t i) {
        return (int8_t *)list->data + list->element_size * i;
}

void *f_alistPushback(f_alist *list, void *elem) {
        if (list->capacity <= list->size + 1) {
                if (list->capacity <= list->size + 1) {
                        f_alistResizeElements(list, 2 * (list->size + 1));
                }
        }

        void *dest = f_alistIdx(list, list->size);
        memcpy(dest, elem, list->element_size);
        list->size++;

        return dest;
}

void *f_alistPushbackArray(f_alist *list, void *elem, size_t number) {
        assert(list != NULL);
        assert(elem != NULL);
        if (list->capacity <= list->size + number) {
                f_alistResizeElements(list, 2 * (list->size + number));
        }

        void *dest = f_alistIdx(list, list->size);
        memcpy(dest, elem, list->element_size * number);
        list->size += number;

        return dest;
}
