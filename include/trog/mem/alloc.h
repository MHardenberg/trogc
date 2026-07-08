#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <trog.h>
#include <trog/mem/arena.h>

#ifdef __cplusplus
extern "C" {
#endif

enum allocType { ALLOC_UNINIT = 0, ALLOC_HEAP, ALLOC_ARENA };

typedef struct {
        enum allocType type;

        union {
                tr_arena allocArena;
        } alloc;
} tr_alloc;

void tr_allocCreate(tr_alloc *alloc, enum allocType type);

void *tr_allocPush(tr_alloc *alloc, size_t bytes);

void *tr_allocPushZero(tr_alloc *alloc, size_t bytes);

void tr_allocClear(tr_alloc *alloc);

void tr_allocFree(tr_alloc *alloc, void *ptr);

// Dangerous if allocator doesnt track allocations!
void tr_allocDestroy(tr_alloc *alloc);

#ifdef __cplusplus
}
#endif

#endif // ALLOCATOR_H
