#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <forge/dsa/alist.h>

f_Alist f_alistCreate(f_alloc *alloc, size_t capacity, size_t dataBytes) {
        f_Alist list = {.capacity = capacity,
                        .size = 0,
                        .dataBytes = dataBytes,
                        .alloc = alloc};
        list.data = f_allocPush(alloc, capacity);

        return list;
}

void f_alistDestroy(f_Alist *list) {
        f_allocFree(list->alloc, list->data);
}

void f_alistResize(f_Alist *list, size_t newCapacity) {
        assert(newCapacity > list->capacity);
        void *new = f_allocPush(list->alloc, newCapacity);
        memcpy(new, list->data, list->size * list->dataBytes);
        f_allocFree(list->alloc, list->data);
        list->data = new;
        list->capacity = newCapacity;
}

void *f_alistIdx(f_Alist *list, size_t i) {
        return (int8_t *)list->data + list->dataBytes * i;
}

void f_alistPushback(f_Alist *list, void *elem, size_t elemBytes,
                     size_t number) {
        if (list->capacity <= list->size + number) {
                f_alistResize(list, list->capacity * 2);
        }

        for (size_t i = 0; i < number; ++i) {
                memcpy(list->data, elem, elemBytes * number);
        }
        list->size += number;
}
