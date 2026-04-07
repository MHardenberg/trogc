#ifndef ALIST_H
#define ALIST_H

#warning Needs testing!
#include <forge.h>
#include <forge/mem/alloc.h>

typedef struct {
        size_t size;
        size_t capacity;
        size_t dataBytes;
        f_alloc *alloc;
        void *data;
} f_Alist;

f_Alist f_alistCreate(f_alloc *alloc, size_t capacity, size_t dataBytes);

void f_alistDestroy(f_Alist *list);

void f_alistResize(f_Alist *list, size_t newCapacity);

void *f_alistIdx(f_Alist *list, size_t i);

void f_alistPushback(f_Alist *list, void *elem, size_t elemBytes,
                     size_t number);

#endif // ALIST_H
