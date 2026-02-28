#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <forge.h>
inline static void test_print_fail(const char *file, const char *func,
                                   const int line) {
        fprintf(stderr,
                "\033[31;1;4mTEST FAILED:\033[0m %s: %s "
                "l:%d\n",
                file, func, line);
}

inline static void test_print_pass(const char *func) {
        fprintf(stderr, "\033[32mTEST PASSED: %s\033[0m\n", func);
}

#define TEST_ZERO(t)                                                           \
        {                                                                      \
                if (t != 0) {                                                  \
                        test_print_fail(__FILE__, __func__, __LINE__);         \
                } else {                                                       \
                        test_print_pass(__func__);                             \
                }                                                              \
        }

#define TEST_TRUE(t)                                                           \
        {                                                                      \
                if ((bool)t == false) {                                        \
                        test_print_fail(__FILE__, __func__, __LINE__);         \
                } else {                                                       \
                        test_print_pass(__func__);                             \
                }                                                              \
        }

#endif
