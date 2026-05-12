#ifndef FORGE_H
#define FORGE_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <forgeLogging.h>
#include <forgeAssert.h>

#define f_max(a, b) ((a) > (b) ? (a) : (b));

#if defined(__GNUC__) || defined(__clang__)
#define PACKED_START
#define PACKED_END __attribute__((packed))

#elif defined(_MSC_VER)
#define PACKED_START __pragma(pack(push, 1))
#define PACKED_END __pragma(pack(pop))

#else
#error "Compiler not supported"
#endif

#endif // FORGE_H
