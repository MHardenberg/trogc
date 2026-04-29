#ifndef ALIST_H
#define ALIST_H

#warning Needs testing!
#include <forge.h>
#include <forge/mem/alloc.h>

typedef struct {
        size_t size;
        size_t capacity;
        size_t element_size;
        f_alloc *alloc;
        void *data;
} f_alist;

void f_alistCreate(f_alloc *alloc, f_alist *list, const size_t capacity,
                   const size_t element_size);

void f_alistDestroy(f_alist *list);

void f_alistResizeElements(f_alist *list, const size_t newCapacity);

void *f_alistIdx(const f_alist *list, const size_t i);

void *f_alistPushback(f_alist *list, const void *elem);

void *f_alistNext(f_alist *list);

void *f_alistPushbackArray(f_alist *list, const void *elem,
                           const size_t number);

void *f_alistNextArray(f_alist *list, const size_t number);

#endif // ALIST_H
