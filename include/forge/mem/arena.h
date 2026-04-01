#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <string.h>

#define DEFAULT_ARENA_RESERVATION_SIZE                                         \
        (256LL * 1000LL * 1000LL * 1000LL) // 256 Gb

#define f_arenaPushArray(arena, type, count)                                   \
        ((type *)ArenaPush((arena), sizeof(type) * (count)))

#define f_arenaPushArrayZero(arena, type, count)                               \
        ((type *)ArenaPushZero((arena), sizeof(type) * (count)))

#define f_PushStruct(arena, type) PushArray((arena), (type), 1)
#define f_PushStructZero(arena, type) PushArrayZero((arena), (type), 1)

typedef struct {
        size_t reserved;
        size_t capacity;

        size_t offset;
        void *buffer;
} f_arena;

typedef struct {
        f_arena *arena;
        size_t prevOffset;

        void *buffer;
} ScratchPad;

int f_arenaCreate(f_arena *arena);

void f_arenaDestroy(f_arena *arena);

void *f_arenaPush(f_arena *arena, size_t bytes);

void *f_arenaPushZero(f_arena *arena, size_t bytes);

void f_arenaClear(f_arena *arena);

// scratchPad
ScratchPad *f_ScratchPadBegin(f_arena *arena, size_t bytes);

void f_ScratchPadEnd(ScratchPad *pad);
#endif // ARENA_H
