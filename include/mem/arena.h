#ifndef ARENA_H
#define ARENA_H

#include <assert.h>
#include <stdint.h>
#include <string.h>

#define DEFAULT_ARENA_RESERVATION_SIZE (256 * 1024 * 1024) // 256 MB

#define ArenaPushArray(arena, type, count)                                     \
  ((type *)ArenaPush((arena), sizeof(type) * (count)))

#define ArenaPushArrayZero(arena, type, count)                                 \
  ((type *)ArenaPushZero((arena), sizeof(type) * (count)))

#define PushStruct(arena, type) PushArray((arena), (type), 1)
#define PushStructZero(arena, type) PushArrayZero((arena), (type), 1)

typedef struct {
  size_t reserved;
  size_t capacity;

  size_t offset;
  void *buffer;
} Arena;

typedef struct {
  Arena *arena;
  size_t prevOffset;

  void *buffer;
} ScratchPad;

int ArenaCreate(Arena *arena);

void ArenaDestroy(Arena *arena);

void *ArenaPush(Arena *arena, size_t bytes);

void *ArenaPushZero(Arena *arena, size_t bytes);

void ArenaClear(Arena *arena);

// scratchPad
ScratchPad *ScratchPadBegin(Arena *arena, size_t bytes);

void ScratchPadEnd(ScratchPad *pad);
#endif // ARENA_H
