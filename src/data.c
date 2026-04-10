#include "forge/mem/scratchpad.h"
#include <sys/stat.h>
#include <time.h>
#include <float.h>

#include <forge/data.h>
#define _BUFFER_LEN 1024
#define _MAX_PLOT_POINTS 10000LL
const char pathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

void f_getTimeStr(char *dest, size_t capacity) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(dest, capacity, "%d_%m_%Y_%H_%M_%S", t);
}

// Given a file path, create all constituent directories if missing
void f_createPathDirs(const char *dest) {
        const char *next_sep = strchr(dest, pathSeparator);
        char dirPath[1024];
        while (next_sep != NULL) {
                int dirPathLen = next_sep - dest;
                memcpy(dirPath, dest, dirPathLen);
                dirPath[dirPathLen] = '\0';
                mkdir(dirPath, S_IRWXU | S_IRWXG | S_IROTH);
                next_sep = strchr(next_sep + 1, pathSeparator);
        }
}

void f_getFilePath(char *dest, const char *title) {
        if (title != NULL) {
                strcat(dest, PROJECT_ROOT "/temp/");
                char c = '\0';
                size_t i = 0;
                for (;;) {
                        c = title[i++];
                        if (c == '\0') {
                                break;
                        }
                        if (c == ' ' || c == '\n' || c == '\r') {
                                continue;
                        }
                        strncat(dest, &c, 1);
                }

        } else {
                size_t result = snprintf(dest, sizeof(char) * _BUFFER_LEN,
                                         "%s/temp/%s", PROJECT_ROOT, "temp");
                assert(result > 0);
                assert(result <= sizeof(char) * _BUFFER_LEN);
        }
}

void f_makeDataPath(f_alloc *alloc, char *dest, char *fileName) {
        assert(dest != NULL);
        f_ScratchPad *pad = f_ScratchPadCreate(alloc, 3072);

        char *time = f_ScratchPadPush(pad, 1024);
        char *stampedFile = f_ScratchPadPush(pad, 1024);
        f_getTimeStr(time, 1024);
        assert(time != NULL);
        assert(dest != NULL);
        sprintf(stampedFile, "%s%s%s", time, "_", fileName);
        f_getFilePath(dest, stampedFile);
        f_ScratchPadDestroy(pad);
}

void f_toFile(f_alloc *alloc, char *fileName, char *path, f_vecd *x,
              f_vecd **ys, size_t nvecs, char *xLabel, char **labels) {
        assert(alloc != NULL);
        assert((fileName != NULL) ^ (path != NULL));
        assert(xLabel != NULL);
        assert(labels != NULL);
        assert(x != NULL);
        for (size_t i = 0; i < nvecs; ++i) {
                assert(ys[i] != NULL);
                assert(ys[i]->size == x->size);
        }

        f_ScratchPad *pad = f_ScratchPadCreate(alloc, 4096);
        if (path == NULL) {
                path = f_ScratchPadPush(pad, 2048);
                f_makeDataPath(alloc, path, fileName);
        }

        f_createPathDirs(path);
        LOG("path");
        FILE *fptr;
        fptr = fopen(path, "w");
        assert(fptr != NULL);

        size_t incr = 1;
        if (x->size > _MAX_PLOT_POINTS) {
                incr = x->size / _MAX_PLOT_POINTS;
        }

        LOG("Saving to %s", path);
        // Labels to file
        fprintf(fptr, "%s, ", xLabel);
        for (size_t i = 0; i < nvecs; ++i) {
                fprintf(fptr, "%s%s", labels[i], (i < nvecs - 1) ? ", " : "\n");
        }

        // Data to file
        for (size_t r = 0; r < x->size; r += incr) {
                fprintf(fptr, "%e, ", x->x[r]);
                for (size_t i = 0; i < nvecs; ++i) {
                        fprintf(fptr, "%e%s", ys[i]->x[r],
                                (i < nvecs - 1) ? ", " : "\n");
                }
        }
        // Close the file
        fclose(fptr);
        f_ScratchPadDestroy(pad);
}
