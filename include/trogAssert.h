#ifndef ASSERT_H
#define ASSERT_H

void printStackTrace();

#define tr_panic(msg)                                                          \
        do {                                                                   \
                LOG("\n\n\033[31;1;4mProgram PANIC\033[0m %s: "                \
                    "%s in file "                                              \
                    "%s, line %d",                                             \
                    msg != NULL ? msg : "", __func__, __FILE__, __LINE__);     \
                printStackTrace();                                             \
                abort();                                                       \
        } while (0)

#ifdef _DEBUG

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

#else

#define tr_assert(condition)                                                   \
        do {                                                                   \
        } while (0)

#endif

#endif //  ASSERT_H
