#include <assert.h>
#include <trog/mem/scratchpad.h>
#include <trog/mem/alloc.h>
#include <trog/mem/mem.h>
#include <string.h>

tr_ScratchPad *tr_ScratchPadCreate(tr_alloc *alloc, size_t bytes) {
        tr_ScratchPad *pad = tr_allocPush(alloc, sizeof(tr_ScratchPad));
        pad->alloc = alloc;
        pad->offset = 0;
        pad->capacity = bytes;
        pad->buffer = tr_allocPush(alloc, bytes);
        tr_assert(pad->buffer != NULL);
        return pad;
}

void *tr_ScratchPadPush(tr_ScratchPad *pad, size_t bytes) {
        size_t newOffset =
            tr_alignForward((uintptr_t)pad->buffer + pad->offset + bytes) -
            (uintptr_t)pad->buffer;

        if (newOffset > pad->capacity) {
                return NULL;
        }

        void *dest = (void *)((uintptr_t)pad->buffer + pad->offset);
        pad->offset = newOffset;

        return dest;
}

void *tr_ScratchPadPushZero(tr_ScratchPad *pad, size_t bytes) {
        void *dest = tr_ScratchPadPush(pad, bytes);
        tr_assert(dest != NULL);
        memset(dest, 0, bytes);
        return dest;
}

void tr_ScratchPadClear(tr_ScratchPad *pad) {
        pad->offset = 0;
}

void tr_ScratchPadDestroy(tr_ScratchPad *pad) {
        tr_allocFree(pad->alloc, pad->buffer);
        tr_allocFree(pad->alloc, pad);
}
