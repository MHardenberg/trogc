#include <assert.h>
#include <forge/mem/alloc.h>

void f_allocInit(f_alloc *alloc, enum allocType type) {
        assert(alloc != NULL);
        switch (type) {
        case ALLOC_ARENA: {
                alloc->type = ALLOC_ARENA;
                f_arenaCreate(&alloc->alloc.allocArena);
                break;
        }
        default: // Should never happen.
        }
}

void *f_allocPush(f_alloc *alloc, size_t bytes) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                return f_arenaPush(&alloc->alloc.allocArena, bytes);
        }
        default: // Should never happen.
                return NULL;
        }
}

void *f_allocPushZero(f_alloc *alloc, size_t bytes) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                return f_arenaPushZero(&alloc->alloc.allocArena, bytes);
        }
        default: // Should never happen.
                return NULL;
        }
}

void f_allocFree(f_alloc *alloc, void *ptr) {
        assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                (void)ptr;
                return; // no op in arena}
        }
        default: // Should never happen.
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
        default: // Should never happen.
        }
}
