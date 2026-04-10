#ifndef SCRATCH_PAD_H
#define SCRATCH_PAD_H

#include <forge/mem/alloc.h>

typedef struct {
        f_alloc *alloc;

        size_t offset;
        size_t capacity;

        void *buffer;
} f_ScratchPad;

#define f_ScratchPadPushArray(padPtr, typesize, count)                         \
        (f_ScratchPadPush((arena), (typesize) * (count)))

#define f_ScratchPadPushArrayZero(padPtr, typesize, count)                     \
        (f_ScratchPadPushZero((arena), (typesize) * (count)))

f_ScratchPad *f_ScratchPadCreate(f_alloc *alloc, size_t bytes);

void *f_ScratchPadPush(f_ScratchPad *pad, size_t bytes);

void *f_ScratchPadPushZero(f_ScratchPad *pad, size_t bytes);

void f_ScratchPadClear(f_ScratchPad *pad);

void f_ScratchPadDestroy(f_ScratchPad *pad);

#endif // SCRATCH_PAD_H
