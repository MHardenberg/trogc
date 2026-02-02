#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <forge.h>
#include <forge/mem/arena.h>

enum allocType { ALLOC_ARENA };

typedef struct {
        enum allocType type;

        union {
                f_arena allocArena;
        } alloc;
} f_alloc;

void f_allocCreate(f_alloc *alloc, enum allocType type);

void *f_allocPush(f_alloc *alloc, size_t bytes);

void *f_allocPushZero(f_alloc *alloc, size_t bytes);

void f_allocFree(f_alloc *alloc, void *ptr);

// Dangerous if allocator doesnt track allocations!
void f_allocDestroy(f_alloc *alloc);
#endif // ALLOCATOR_H
