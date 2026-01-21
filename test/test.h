#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <forge.h>
#define TEST(t)                                                                \
        {                                                                      \
                if (t != 0) {                                                  \
                        fprintf(stderr,                                        \
                                "\n\033[31;1;4mTEST FAILED:\033[0m %s: %s "    \
                                "l:%d\n\n",                                    \
                                __FILE__, __func__, __LINE__);                 \
                } else {                                                       \
                        fprintf(stderr, "\033[32mTEST PASSED: %s\033[0m\n",    \
                                __func__);                                     \
                }                                                              \
        }

#endif
