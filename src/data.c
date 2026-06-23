#include "trog/linalg.h"
#include "trog/mem/scratchpad.h"
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <float.h>

#include <trog/data.h>
#define _BUFFER_LEN 1024
#define _MAX_PLOT_POINTS 100000LL
const char pathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

void tr_getTimeStr(char *dest, size_t capacity) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(dest, capacity, "%d_%m_%Y_%H_%M_%S", t);
}

// Given a file path, create all constituent directories if missing
void tr_createPathDirs(tr_alloc *alloc, const char *dest) {
        const char *next_sep = strchr(dest, pathSeparator);
        char *dirPath = tr_allocPush(alloc, 1024);
        while (next_sep != NULL) {
                int dirPathLen = next_sep - dest;
                memcpy(dirPath, dest, dirPathLen);
                dirPath[dirPathLen] = '\0';
                mkdir(dirPath, S_IRWXU | S_IRWXG | S_IROTH);
                next_sep = strchr(next_sep + 1, pathSeparator);
        }

        tr_allocFree(alloc, dirPath);
}

void tr_getFilePath(char *dest, const char *title) {
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
                tr_assert(result > 0);
                tr_assert(result <= sizeof(char) * _BUFFER_LEN);
        }
}

void tr_makeDataPath(tr_alloc *alloc, char *dest, char *fileName) {
        tr_assert(dest != NULL);
        tr_ScratchPad *pad = tr_ScratchPadCreate(alloc, 3072);

        char *timenow = tr_ScratchPadPush(pad, 1024);
        char *stampedFile = tr_ScratchPadPush(pad, 1024);
        tr_getTimeStr(timenow, 1024);
        tr_assert(timenow != NULL);
        tr_assert(dest != NULL);
        sprintf(stampedFile, "%s%s%s", timenow, "_", fileName);
        tr_getFilePath(dest, stampedFile);
        tr_ScratchPadDestroy(pad);
}

void tr_toFile(tr_alloc *alloc, char *fileName, char *path, const tr_vecd *x,
               tr_vecd **ys, const size_t nvecs, char *xLabel, char **labels) {
        tr_assert(alloc != NULL);
        tr_assert((fileName != NULL) ^ (path != NULL));
        tr_assert(xLabel != NULL);
        tr_assert(labels != NULL);
        tr_assert(x != NULL);
        for (size_t i = 0; i < nvecs; ++i) {
                tr_assert(ys[i] != NULL);
                tr_assert(ys[i]->size <= x->size);
        }

        tr_ScratchPad *pad = tr_ScratchPadCreate(alloc, 4096);
        if (path == NULL) {
                path = tr_ScratchPadPush(pad, 2048);
                tr_makeDataPath(alloc, path, fileName);
        }

        tr_createPathDirs(alloc, path);
        FILE *fptr;
        fptr = fopen(path, "w+");
        tr_assert(fptr != NULL);

        size_t incr = 1;
        if (x->size > _MAX_PLOT_POINTS) {
                incr = x->size / _MAX_PLOT_POINTS;
        }

        LOG("Saving to %s\n", path);
        // Labels to file
        fprintf(fptr, "%s,", xLabel);
        for (size_t i = 0; i < nvecs; ++i) {
                fprintf(fptr, "%s%s", labels[i], (i < nvecs - 1) ? "," : "\n");
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
        tr_ScratchPadDestroy(pad);
}
