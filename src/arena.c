#include <forge/mem/arena.h>
#include <forge.h>
#ifdef __linux__
#include <sys/mman.h>
#include <unistd.h>

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

#define PAGE_SIZE 4096
#define DEFAULT_ALIGNMENT (2 * sizeof(void *))

static inline uintptr_t alignForward(uintptr_t ptr) {
        assert(!(DEFAULT_ALIGNMENT % 2));
        uintptr_t modulo = ptr & (uintptr_t)(DEFAULT_ALIGNMENT - 1);
        if (modulo != 0) {
                ptr += DEFAULT_ALIGNMENT - modulo;
        }
        return ptr;
}

static inline size_t alignPages(size_t bytes) {
        return (bytes % PAGE_SIZE) ? PAGE_SIZE * (bytes / PAGE_SIZE + 1)
                                   : bytes;
}

void *arenaResize(f_arena *arena, size_t bytes) {
        // commit full pages
        bytes = alignPages(bytes);
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

int f_arenaCreate(f_arena *arena) {
        arena->reserved = alignPages(DEFAULT_ARENA_RESERVATION_SIZE);
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

void f_arenaDestroy(f_arena *arena) {
        MEM_RELEASE(arena->buffer, arena->reserved);
}

void *f_arenaPush(f_arena *arena, size_t bytes) {
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
        arena->offset = alignForward((uintptr_t)arena->buffer + arena->offset) -
                        (uintptr_t)arena->buffer;
        void *loc = (void *)((uintptr_t)arena->buffer + arena->offset);
        arena->offset += bytes;
        return loc;
}

void *f_arenaPushZero(f_arena *arena, size_t bytes) {
        void *loc = f_arenaPush(arena, bytes);
        if (loc == NULL) {
                return NULL;
        }
        memset(loc, 0, bytes);
        return loc;
}

void f_arenaClear(f_arena *arena) {
        arena->offset = 0;
}

// scratchPad
ScratchPad *f_ScratchPadBegin(f_arena *arena, size_t bytes) {
        size_t prevOffset = arena->offset;
        ScratchPad *pad = f_arenaPush(arena, bytes + sizeof(ScratchPad));
        if (pad == NULL) {
                return NULL;
        }

        pad->arena = arena;
        pad->prevOffset = prevOffset;
        pad->buffer = (void *)((uintptr_t)arena->buffer + prevOffset +
                               sizeof(ScratchPad));
        return pad;
}

void f_ScratchPadEnd(ScratchPad *pad) {
        pad->arena->offset = pad->prevOffset;
}
