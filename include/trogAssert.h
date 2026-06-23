#ifndef ASSERT_H
#define ASSERT_H

#ifdef _DEBUG
#include <stdlib.h>
#include <stdio.h>

void printStackTrace();

#define tr_assert(condition)                                                   \
        do {                                                                   \
                if (!(condition)) {                                            \
                        LOG("\033[31;1;4mASSERTION FAILED\033[0m %s:  "        \
                            "%s in file "                                      \
                            "%s, line %d",                                     \
                            #condition, __func__, __FILE__, __LINE__);         \
                        printStackTrace();                                     \
                        abort();                                               \
                }                                                              \
        } while (0)

#else
#define tr_assert(condition)                                                   \
        do {                                                                   \
        } while (0)

#endif

#endif //  ASSERT_H
