#ifndef TROG_H
#define TROG_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <trogLogging.h>
#include <trogAssert.h>

#define tr_max(a, b) ((a) > (b) ? (a) : (b));

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
