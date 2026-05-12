#include <assert.h>
#include <forge/mem/scratchpad.h>
#include <forge/mem/alloc.h>
#include <forge/mem/mem.h>
#include <string.h>

f_ScratchPad *f_ScratchPadCreate(f_alloc *alloc, size_t bytes) {
        f_ScratchPad *pad = f_allocPush(alloc, sizeof(f_ScratchPad));
        pad->alloc = alloc;
        pad->capacity = bytes;
        pad->buffer = f_allocPush(alloc, bytes);
        f_assert(pad->buffer != NULL);
        return pad;
}

void *f_ScratchPadPush(f_ScratchPad *pad, size_t bytes) {
        size_t newOffset =
            f_alignForward((uintptr_t)pad->buffer + pad->offset + bytes) -
            (uintptr_t)pad->buffer;

        if (newOffset > pad->capacity) {
                return NULL;
        }

        void *dest = (void *)((uintptr_t)pad->buffer + pad->offset);
        pad->offset = newOffset;

        return dest;
}

void *f_ScratchPadPushZero(f_ScratchPad *pad, size_t bytes) {
        void *dest = f_ScratchPadPush(pad, bytes);
        f_assert(dest != NULL);
        memset(dest, 0, bytes);
        return dest;
}

void f_ScratchPadClear(f_ScratchPad *pad) {
        pad->offset = 0;
}

void f_ScratchPadDestroy(f_ScratchPad *pad) {
        f_allocFree(pad->alloc, pad->buffer);
        f_allocFree(pad->alloc, pad);
}
