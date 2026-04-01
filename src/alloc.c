#include "forge/mem/arena.h"
#include <forge/mem/alloc.h>
#include <stdlib.h>

void f_allocCreate(f_alloc *alloc, enum allocType type) {
        assert(alloc != NULL);
        switch (type) {
        case ALLOC_ARENA: {
                alloc->type = ALLOC_ARENA;
                f_arenaCreate(&alloc->alloc.allocArena);
                break;
        }
        case ALLOC_HEAP: {
                alloc->type = ALLOC_HEAP;
                break;
        }
        default: // Should never happen.
                assert(0 && "Not initialised!");
        }
}

void *f_allocPush(f_alloc *alloc, size_t bytes) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                return f_arenaPush(&alloc->alloc.allocArena, bytes);
        }
        case ALLOC_HEAP: {
                return malloc(bytes);
        }
        default: // Should never happen.
                assert(0 && "Not initialised!");
                return NULL;
        }
}

void *f_allocPushZero(f_alloc *alloc, size_t bytes) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                return f_arenaPushZero(&alloc->alloc.allocArena, bytes);
        }
        case ALLOC_HEAP: {
                return calloc(bytes, sizeof(char));
        }
        default: // Should never happen.
                assert(0 && "Not initialised!");
                return NULL;
        }
}

void f_allocFree(f_alloc *alloc, void *ptr) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                (void)ptr;
                // no op in arena}
                break;
        }
        case ALLOC_HEAP: {
                free(ptr);
                break;
        }
        default: // Should never happen.
                assert(0 && "Not initialised!");
        }
}

void f_allocClear(f_alloc *alloc) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                f_arenaClear(&alloc->alloc.allocArena);
        }
        case ALLOC_HEAP: {
                // noop
                break;
        }
        default: // Should never happen.
                assert(0 && "Not initialised!");
        }
}

// Dangerous if allocator doesnt track allocations!
void f_allocDestroy(f_alloc *alloc) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                f_arenaDestroy(&alloc->alloc.allocArena);
                break;
        }
        case ALLOC_HEAP: {
                break; // nothing todo
        }
        default: // Should never happen.
                assert(0 && "Not initialised!");
        }
}
