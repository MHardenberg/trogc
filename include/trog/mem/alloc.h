#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "trogAssert.h"
#include <trog.h>
#include <trog/mem/arena.h>

enum allocType { ALLOC_UNINIT = 0, ALLOC_HEAP, ALLOC_ARENA };

typedef struct {
        enum allocType type;

        union {
                tr_arena allocArena;
        } alloc;
} tr_alloc;

typedef struct {
        const tr_alloc *alloc;
        const tr_alloc cpy;
} tr_allocCheckpoint;

void tr_allocCreate(tr_alloc *alloc, enum allocType type);

void *tr_allocPush(tr_alloc *alloc, size_t bytes);

void *tr_allocPushZero(tr_alloc *alloc, size_t bytes);

void tr_allocClear(tr_alloc *alloc);

void tr_allocFree(tr_alloc *alloc, void *ptr);

// Dangerous if allocator doesnt track allocations!
void tr_allocDestroy(tr_alloc *alloc);

// Checkpoints
tr_allocCheckpoint tr_allocCheckpointSpawn(const tr_alloc *alloc);

void tr_allocCheckpointReset(const tr_allocCheckpoint *check);

#endif // ALLOCATOR_H
