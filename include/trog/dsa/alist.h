#ifndef ALIST_H
#define ALIST_H

#warning Needs testing!
#include <trog.h>
#include <trog/mem/alloc.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
        size_t size;
        size_t capacity;
        size_t stride;
        tr_alloc *alloc;
        void *data;
} tr_alist;

void tr_alistCreate(tr_alloc *alloc, tr_alist *list, const size_t capacity,
                    const size_t stride);

void tr_alistDestroy(tr_alist *list);

void tr_alistResizeElements(tr_alist *list, const size_t newCapacity);

void *tr_alistIdx(const tr_alist *list, const size_t i);

void *tr_alistPushback(tr_alist *list, const void *elem);

void *tr_alistNext(tr_alist *list);

void *tr_alistPushbackArray(tr_alist *list, const void *elem,
                            const size_t number);

void *tr_alistNextArray(tr_alist *list, const size_t number);

#ifdef __cplusplus
}
#endif

#endif // ALIST_H
