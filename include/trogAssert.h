#ifndef ASSERT_H
#define ASSERT_H

#ifdef _DEBUG
#include <stdlib.h>
#include <stdio.h>
void printStackTrace();

#define tr_assert(condition)                                                   \
        do {                                                                   \
                if (!(condition)) {                                            \
                        LOG("\n\n\033[31;1;4mASSERTION FAILED\033[0m %s: "     \
                            "%s in file "                                      \
                            "%s, line %d",                                     \
                            #condition, __func__, __FILE__, __LINE__);         \
                        printStackTrace();                                     \
                        abort();                                               \
                }                                                              \
        } while (0)

#define tr_panic(msg)                                                          \
        do {                                                                   \
                LOG("\n\n\033[31;1;4mProgram PANIC\033[0m %s: "                \
                    "%s in file "                                              \
                    "%s, line %d",                                             \
                    msg != NULL ? msg : "", __func__, __FILE__, __LINE__);     \
                printStackTrace();                                             \
                abort();                                                       \
        } while (0)

#else
#define tr_assert(condition)                                                   \
        do {                                                                   \
        } while (0)

#endif

#define tr_panic(msg)                                                          \
        do {                                                                   \
                LOGRELEASE("\n\n\033[31;1;4mProgram PANIC\033[0m %s: "         \
                           "%s in file "                                       \
                           "%s, line %d",                                      \
                           msg != NULL ? msg : "", __func__, __FILE__,         \
                           __LINE__);                                          \
                abort();                                                       \
        } while (0)

#endif //  ASSERT_H
