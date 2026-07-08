#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_ARENA_RESERVATION_SIZE                                         \
        (256LL * 1000LL * 1000LL * 1000LL) // 256 Gb

#define tr_arenaPushArray(arenaPtr, typesize, count)                           \
        (ArenaPush((arena), typesize * (count)))

#define tr_arenaPushArrayZero(arenaPtr, typesize, count)                       \
        (ArenaPushZero((arena), typesize * (count)))

// #define tr_PushStruct(arena, type) PushArray((arena), (type), 1)
// #define tr_PushStructZero(arena, type) PushArrayZero((arena), (type), 1)

typedef struct {
        size_t reserved;
        size_t capacity;

        size_t offset;
        void *buffer;
} tr_arena;

int tr_arenaCreate(tr_arena *arena);

void tr_arenaDestroy(tr_arena *arena);

void *tr_arenaPush(tr_arena *arena, size_t bytes);

void *tr_arenaPushZero(tr_arena *arena, size_t bytes);

void tr_arenaClear(tr_arena *arena);

#ifdef __cplusplus
}
#endif

#endif // ARENA_H
