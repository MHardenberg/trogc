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
                        fprintf(stderr,                                        \
                                "\033[31;1;4mASSERTION FAILED\033[0m %s:  "    \
                                "%s in file "                                  \
                                "%s, line %d\n",                               \
                                #condition, __func__, __FILE__, __LINE__);     \
                        printStackTrace();                                     \
                        abort();                                               \
                }                                                              \
        } while (0)

#else
#define assert(condition)                                                      \
        do {                                                                   \
        } while (0)

#endif

#endif //  ASSERT_H
