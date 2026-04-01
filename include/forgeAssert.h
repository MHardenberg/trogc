#ifndef ASSERT_H
#define ASSERT_H

void printStackTrace();

#warning should be global!
#define _DEBUG
#include <stdlib.h>
#include <stdio.h>

#ifdef _DEBUG
#define assert(condition)                                                      \
        do {                                                                   \
                if (!(condition)) {                                            \
                        printStackTrace();                                     \
                        fprintf(stderr,                                        \
                                "Assertion failed: %s, file %s, line %d\n",    \
                                #condition, __FILE__, __LINE__);               \
                        abort();                                               \
                }                                                              \
        } while (0)

#else
#define assert(condition)                                                      \
        do {                                                                   \
        } while (0)

#endif

#endif //  ASSERT_H
