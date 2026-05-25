#include <trog/mem/arena.h>
#include <trog/mem/mem.h>
#include <trog.h>
#ifdef __linux__
#include <sys/mman.h>

/*
#define MEM_RESERVE(bytes)                                                     \
        mmap(NULL, (bytes), PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)

#define MEM_COMMIT(dest, bytes)                                                \
        mprotect((dest), (bytes), PROT_READ | PROT_WRITE)

#define MEM_RELEASE(ptr, bytes) munmap((ptr), (bytes));

*/

#define MEM_RESERVE(bytes)                                                     \
        mmap(NULL, (bytes), PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)

#define MEM_COMMIT(dest, bytes)                                                \
        mmap((dest), (bytes), PROT_READ | PROT_WRITE,                          \
             MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0)

#define MEM_RELEASE(ptr, bytes) munmap((void *)(ptr), (bytes))

#elif defined(_WIN32)
#include <windows.h>

#define MEM_RESERVE(bytes)                                                     \
        VirtualAlloc(NULL, (bytes), MEM_RESERVE, PAGE_NOACCESS)
#define(MEM_COMMIT(dest, bytes) VirtualAlloc((dest), (bytes), MEM_COMMIT,      \
                                             PAGE_READWRITE) != NULL           \
            ? 0                                                                \
            : 1
#define MEM_RELEASE(dest, bytes) VirtualFree((dest), 0, MEM_RELEASE)
#endif

void *arenaResize(tr_arena *arena, size_t bytes) {
        // commit full pages
        bytes = tr_alignPages(bytes);
        if (arena->offset + bytes > arena->reserved) {
                // This really shouldnt happen
                LOGERROR("Out of reserved addresses.");
                return NULL;
        }

        void *commit =
            (void *)((uintptr_t)arena->buffer +
                     arena->capacity); // Has to be capacity which has to be
                                       // page aligned and to not double commit.
#warning "Check for windwos comp"
        if (MEM_COMMIT(commit, bytes) == MAP_FAILED) {
                return NULL;
        }
        arena->capacity += bytes;
        return commit;
}

int tr_arenaCreate(tr_arena *arena) {
        arena->reserved = tr_alignPages(DEFAULT_ARENA_RESERVATION_SIZE);
        arena->capacity = PAGE_SIZE;
        arena->offset = 0;

        // reserve virtual memory addresses
        void *reservation = (void *)MEM_RESERVE(arena->reserved);

#warning "Check for windows comp"
        if (reservation == MAP_FAILED) {
                LOGERROR("Memory reservation failed.");
                // this should never happen
                return 1;
        }

        arena->buffer = reservation;

        // initially we commit a single page of physical
        // memory to our reserved

        void *commit = (void *)((uintptr_t)arena->buffer + arena->offset);

#warning "Check for windows comp"
        if (MEM_COMMIT(commit, arena->capacity) == MAP_FAILED) {
                return 1;
        }
        arena->buffer = commit;
        return 0;
}

void tr_arenaDestroy(tr_arena *arena) {
        MEM_RELEASE(arena->buffer, arena->reserved);
}

void *tr_arenaPush(tr_arena *arena, size_t bytes) {
        if (arena->offset + bytes >= arena->capacity) {
                // resize if out of cap
                if (arenaResize(arena, bytes) == NULL) {
                        LOGERROR("Memory resize failed.");
                        // fail if out of reserved
                        // addresses
                        return NULL;
                }
        }

        // align offset and move by bytes
        arena->offset =
            tr_alignForward((uintptr_t)arena->buffer + arena->offset) -
            (uintptr_t)arena->buffer;
        void *loc = (void *)((uintptr_t)arena->buffer + arena->offset);
        arena->offset += bytes;
        return loc;
}

void *tr_arenaPushZero(tr_arena *arena, size_t bytes) {
        void *loc = tr_arenaPush(arena, bytes);
        if (loc == NULL) {
                return NULL;
        }
        memset(loc, 0, bytes);
        return loc;
}

void tr_arenaClear(tr_arena *arena) {
        arena->offset = 0;
}
