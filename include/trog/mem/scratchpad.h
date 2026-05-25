#ifndef SCRATCH_PAD_H
#define SCRATCH_PAD_H

#include <trog/mem/alloc.h>

typedef struct {
        tr_alloc *alloc;

        size_t offset;
        size_t capacity;

        void *buffer;
} tr_ScratchPad;

#define tr_ScratchPadPushArray(padPtr, typesize, count)                        \
        (tr_ScratchPadPush((arena), (typesize) * (count)))

#define tr_ScratchPadPushArrayZero(padPtr, typesize, count)                    \
        (tr_ScratchPadPushZero((arena), (typesize) * (count)))

tr_ScratchPad *tr_ScratchPadCreate(tr_alloc *alloc, size_t bytes);

void *tr_ScratchPadPush(tr_ScratchPad *pad, size_t bytes);

void *tr_ScratchPadPushZero(tr_ScratchPad *pad, size_t bytes);

void tr_ScratchPadClear(tr_ScratchPad *pad);

void tr_ScratchPadDestroy(tr_ScratchPad *pad);

#endif // SCRATCH_PAD_H
