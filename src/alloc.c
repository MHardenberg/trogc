#include "trog/mem/arena.h"
#include <trog/mem/alloc.h>
#include <stdlib.h>

void tr_allocCreate(tr_alloc *alloc, enum allocType type) {
        tr_assert(alloc != NULL);
        switch (type) {
        case ALLOC_ARENA: {
                alloc->type = ALLOC_ARENA;
                tr_arenaCreate(&alloc->alloc.allocArena);
                break;
        }
        case ALLOC_HEAP: {
                alloc->type = ALLOC_HEAP;
                break;
        }
        default: // Should never happen.
                tr_assert(0 && "Not initialised!");
        }
}

void *tr_allocPush(tr_alloc *alloc, size_t bytes) {
        tr_assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                return tr_arenaPush(&alloc->alloc.allocArena, bytes);
        }
        case ALLOC_HEAP: {
                return malloc(bytes);
        }
        default: // Should never happen.
                tr_assert(0 && "Not initialised!");
                return NULL;
        }
}

void *tr_allocPushZero(tr_alloc *alloc, size_t bytes) {
        tr_assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                return tr_arenaPushZero(&alloc->alloc.allocArena, bytes);
        }
        case ALLOC_HEAP: {
                return calloc(bytes, sizeof(char));
        }
        default: // Should never happen.
                tr_assert(0 && "Not initialised!");
                return NULL;
        }
}

void tr_allocFree(tr_alloc *alloc, void *ptr) {
        tr_assert(alloc != NULL);
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
                tr_assert(0 && "Not initialised!");
        }
}

void tr_allocClear(tr_alloc *alloc) {
        tr_assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                tr_arenaClear(&alloc->alloc.allocArena);
        }
        case ALLOC_HEAP: {
                // noop
                break;
        }
        default: // Should never happen.
                tr_assert(0 && "Not initialised!");
        }
}

// Dangerous if allocator doesnt track allocations!
void tr_allocDestroy(tr_alloc *alloc) {
        tr_assert(alloc != NULL);
        switch (alloc->type) {
        case ALLOC_ARENA: {
                tr_arenaDestroy(&alloc->alloc.allocArena);
                break;
        }
        case ALLOC_HEAP: {
                break; // nothing todo
        }
        default: // Should never happen.
                tr_assert(0 && "Not initialised!");
        }
}

// Checkpoints
tr_allocCheckpoint tr_allocCheckpointSpawn(const tr_alloc *alloc) {
        tr_assert(alloc != NULL);
        tr_allocCheckpoint check = {.alloc = alloc, .cpy = *alloc};
        return check;
}

void tr_allocCheckpointReset(const tr_allocCheckpoint *check) {
        tr_assert(check != NULL);
        tr_assert(check->alloc != NULL);

        switch (check->alloc->type) {
        case ALLOC_HEAP: { // no-op
                break;
        }

        case ALLOC_ARENA: {
                *(tr_alloc *)check->alloc = check->cpy;
                break;
        }

        default: {
                tr_panic("Invalid allocator");
        }
        }
}
