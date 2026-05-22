#ifndef LOGGING_H
#define LOGGING_H

#ifdef _DEBUG
#include <stdio.h>
#include <stdlib.h>

#define LOG(...)                                                               \
        do {                                                                   \
                fprintf(stderr, __VA_ARGS__);                                  \
        } while (0)

#define LOGERROR(...)                                                          \
        do {                                                                   \
                fprintf(stderr, "Error: <%s on line %d>\n\t", __FILE__,        \
                        __LINE__);                                             \
                LOG(__VA_ARGS__);                                              \
        } while (0)

#else

#define LOG(fmt, ...)

#define LOGERROR(fmt, ...)

#endif

#endif // LOGGING_H
