#ifndef LOGGING_H
#define LOGGING_H

#ifdef _DEBUG
#include <time.h>
#include <stdio.h>

#define LOG(...)                                                               \
        do {                                                                   \
                FILE *fptr = fopen(LOG_FILE, "a");                             \
                if (fptr != NULL) {                                            \
                        time_t t = time(NULL);                                 \
                        struct tm timeLocal = *localtime(&t);                  \
                        fprintf(fptr, "[%d-%02d-%02d %02d:%02d:%02d] [LOG] ",  \
                                timeLocal.tm_year + 1900,                      \
                                timeLocal.tm_mon + 1, timeLocal.tm_mday,       \
                                timeLocal.tm_hour, timeLocal.tm_min,           \
                                timeLocal.tm_sec);                             \
                        fprintf(fptr, __VA_ARGS__);                            \
                        fprintf(fptr, "\n");                                   \
                        fclose(fptr);                                          \
                } else {                                                       \
                        fprintf(stderr, "Failed to open log file..\n");        \
                }                                                              \
                fprintf(stderr, "[LOG] " __VA_ARGS__);                         \
                fprintf(stderr, "\n");                                         \
        } while (0)

#define LOGERROR(...)                                                          \
        do {                                                                   \
                FILE *fptr = fopen(LOG_FILE, "a");                             \
                if (fptr != NULL) {                                            \
                        time_t t = time(NULL);                                 \
                        struct tm timeLocal = *localtime(&t);                  \
                        fprintf(                                               \
                            fptr,                                              \
                            "[%d-%02d-%02d %02d:%02d:%02d] [ERROR] [%s:%d] ",  \
                            timeLocal.tm_year + 1900, timeLocal.tm_mon + 1,    \
                            timeLocal.tm_mday, timeLocal.tm_hour,              \
                            timeLocal.tm_min, timeLocal.tm_sec, __FILE__,      \
                            __LINE__);                                         \
                        fprintf(fptr, __VA_ARGS__);                            \
                        fprintf(fptr, "\n");                                   \
                        fclose(fptr);                                          \
                } else {                                                       \
                        fprintf(stderr, "Failed to open log file..\n");        \
                }                                                              \
                fprintf(stderr, "[ERROR] [%s:%d] " __VA_ARGS__, __FILE__,      \
                        __LINE__);                                             \
                fprintf(stderr, "\n");                                         \
        } while (0)

#define LOGBARE(...)                                                           \
        do {                                                                   \
                FILE *fptr = fopen(LOG_FILE, "a");                             \
                if (fptr != NULL) {                                            \
                        fprintf(fptr, __VA_ARGS__);                            \
                        fclose(fptr);                                          \
                } else {                                                       \
                        fprintf(stderr, "Failed to open log file..\n");        \
                }                                                              \
                fprintf(stderr, __VA_ARGS__);                                  \
        } while (0)

#else
#define LOG(...)
#define LOGERROR(...)
#define LOGBARE(...)
#endif

#endif // LOGGING_H
