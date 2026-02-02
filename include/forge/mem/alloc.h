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

#endif // ALLOCATOR_H
