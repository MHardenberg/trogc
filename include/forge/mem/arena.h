#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <string.h>

#define DEFAULT_ARENA_RESERVATION_SIZE                                         \
        (256LL * 1000LL * 1000LL * 1000LL) // 256 Gb

#define f_arenaPushArray(arenaPtr, typesize, count)                            \
        (ArenaPush((arena), typesize * (count)))

#define f_arenaPushArrayZero(arenaPtr, typesize, count)                        \
        (ArenaPushZero((arena), typesize * (count)))

// #define f_PushStruct(arena, type) PushArray((arena), (type), 1)
// #define f_PushStructZero(arena, type) PushArrayZero((arena), (type), 1)

typedef struct {
        size_t reserved;
        size_t capacity;

        size_t offset;
        void *buffer;
} f_arena;

int f_arenaCreate(f_arena *arena);

void f_arenaDestroy(f_arena *arena);

void *f_arenaPush(f_arena *arena, size_t bytes);

void *f_arenaPushZero(f_arena *arena, size_t bytes);

void f_arenaClear(f_arena *arena);

#endif // ARENA_H
