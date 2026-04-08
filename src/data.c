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

void f_getTimeStr(char *dest) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(dest, strlen(dest), "%d_%m_%Y_%H_%M_%S", t);
}

// Given a file path, create all constituent directories if missing
void f_createPathDirs(const char *dest) {
        char timeBuffer[_BUFFER_LEN];
        f_getTimeStr(timeBuffer);
        char *file_path = (char *)malloc(strlen(dest) + strlen(timeBuffer) + 1);
        strcpy(file_path, dest);
        strcat(file_path, timeBuffer);

        char *dir_path =
            (char *)malloc(strlen(file_path) + strlen(timeBuffer) + 1);
        char *next_sep = strchr(file_path, pathSeparator);
        while (next_sep != NULL) {
                int dir_path_len = next_sep - file_path;
                memcpy(dir_path, file_path, dir_path_len);
                dir_path[dir_path_len] = '\0';
                mkdir(dir_path, S_IRWXU | S_IRWXG | S_IROTH);
                next_sep = strchr(next_sep + 1, pathSeparator);
        }

        free(file_path);
        free(dir_path);
}

void f_getFilePath(char *dest, const char *title) {
        if (title != NULL) {
                strcat(dest, PROJECT_ROOT "/temp/figures/");
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

                strcat(dest, ".dat");

        } else {
                size_t result =
                    snprintf(dest, sizeof(char) * _BUFFER_LEN,
                             "%s/temp/figures/%s", PROJECT_ROOT, "temp");
                assert(result > 0);
                assert(result <= sizeof(char) * _BUFFER_LEN);
        }
}

void f_toCSVfile(const char *dest, const f_vecd *x, const f_vecd **ys,
                 const size_t nvecs, const char *xLabel, const char **labels) {
        assert(x != NULL);
        for (size_t i = 0; i < nvecs; ++i) {
                assert(ys[i] != NULL);
                assert(ys[i]->size == x->size);
        }

        f_createPathDirs(dest);
        FILE *fptr;
        fptr = fopen(dest, "w");
        assert(fptr != NULL);

        size_t incr = 1;
        if (x->size > _MAX_PLOT_POINTS) {
                incr = x->size / _MAX_PLOT_POINTS;
        }

        fprintf(fptr, "%s, ", xLabel);
        for (size_t i = 0; i < nvecs; ++i) {
                fprintf(fptr, "%s%s", labels[i], (i < nvecs - 1) ? ", " : "\n");
        }

        for (size_t r = 0; r < x->size; r += incr) {
                fprintf(fptr, "%e, ", x->x[r]);
                for (size_t i = 0; i < nvecs; ++i) {
                        fprintf(fptr, "%e%s", ys[i]->x[r],
                                (i < nvecs - 1) ? ", " : "\n");
                }
        }
        // Close the file
        fclose(fptr);
}
