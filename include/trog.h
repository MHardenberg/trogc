#ifndef TROG_H
#define TROG_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include <trogAssert.h>
#include <trogLogging.h>

#define tr_max(a, b) ((a) > (b) ? (a) : (b))
#define tr_min(a, b) ((a) < (b) ? (a) : (b))

#ifndef tr_NPROC
#define tr_NPROC 4
#endif

#define tr_MAX_THREADS tr_max(1, tr_NPROC - 1)

#if defined(__GNUC__) || defined(__clang__)
#define PACKED_START
#define PACKED_END __attribute__((packed))

#elif defined(_MSC_VER)
#define PACKED_START __pragma(pack(push, 1))
#define PACKED_END __pragma(pack(pop))

#else
#error "Compiler not supported"
#endif

#endif // TROG_H
