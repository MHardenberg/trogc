#include "forge/linalg.h"
#include <forge/plot.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <float.h>

#define _BUFFER_LEN 1024
#define _MAX_PLOT_POINTS 10000LL

const char pathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

void _getTimeStr(char *dest) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(dest, strlen(dest), "%d_%m_%Y_%H_%M_%S", t);
}

// Given a file path, create all constituent directories if missing
void _createPathDirs(const char *dest) {
        char timeBuffer[_BUFFER_LEN];
        _getTimeStr(timeBuffer);
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

void _getFilePath(char *dest, const char *title) {
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

                // strcat(dest, ".dat");

        } else {
                size_t result =
                    snprintf(dest, sizeof(char) * _BUFFER_LEN,
                             "%s/temp/figures/%s", PROJECT_ROOT, "temp");
                assert(result > 0);
                assert(result <= sizeof(char) * _BUFFER_LEN);
        }
}

void _toCSVfile(const char *dest, const f_vecd *x, const f_vecd **ys,
                const size_t nvecs, const char *xLabel, const char **labels) {
        assert(x != NULL);
        for (size_t i = 0; i < nvecs; ++i) {
                assert(ys[i] != NULL);
                assert(ys[i]->size == x->size);
        }

        _createPathDirs(dest);
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

void f_plotv(const char *title, const f_vecd *x, const f_vecd *ys,
             const char *xLabel, const char *label) {
        f_plotvs(title, x, &ys, 1, xLabel, &label);
}

void f_plotvs(const char *title, const f_vecd *x, const f_vecd **ys,
              const size_t nvecs, const char *xLabel, const char **labels) {
        // write to temp file
        char dest[_BUFFER_LEN];
        char timeBuffer[_BUFFER_LEN];
        _getTimeStr(timeBuffer);
        _getFilePath(dest, title);
        _toCSVfile(dest, x, ys, nvecs, xLabel, labels);

        FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
        if (title != NULL) {
                fprintf(gnuplot_pipe, "set title '%s'\n", title);
        }

        fprintf(gnuplot_pipe,
                "set terminal pdfcairo font 'Arial,12' size 5,3\n");
        fprintf(gnuplot_pipe, "set output '%s_%s.pdf'\n", dest, timeBuffer);

        double upLim = DBL_MIN;
        double downLim = DBL_MAX;

        // figure out lims
        for (size_t i = 0; i < nvecs; ++i) {
                double M = *f_vecdMax(ys[i]);
                double m = *f_vecdMin(ys[i]);
                if (upLim < M) {
                        upLim = M;
                }
                if (downLim > m) {
                        downLim = m;
                }
        }
        upLim > 0 ? (upLim *= 1.25) : (upLim *= 0.75);
        downLim > 0 ? (downLim *= .75) : (downLim *= 1.25);
        upLim == 0 ? (upLim = fabs(downLim)) : (upLim *= 1); // noop
        downLim == 0 ? (downLim = fabs(upLim)) : (downLim *= 1);
        LOG("%e %e\n", upLim, downLim);
        assert(upLim > downLim);

        fprintf(gnuplot_pipe, "set yrange [%e:%e]\n", downLim, upLim);
        fprintf(gnuplot_pipe, "set palette viridis\n");
        fprintf(gnuplot_pipe, "plot ");
        for (size_t i = 0; i < nvecs; ++i) {
                fprintf(gnuplot_pipe,
                        "'%s' using 1:%lu title \"%s\" with "
                        "linespoints "
                        "linewidth 2 "
                        "pointsize .5 pointtype 0%s",
                        dest, i + 2, (labels != NULL) ? labels[i] : "",
                        (i < nvecs - 1) ? ", " : "\n");
        }

        fprintf(gnuplot_pipe, "refresh\n");
        pclose(gnuplot_pipe);
}

void f_plota(const char *title, const double *xa, const double *ya,
             const size_t rows, const char *xLabel, const char *label) {
        f_vecd yv, xv;
        xv.size = rows;
        yv.size = rows;
        xv.x = (double *)xa; // I hate this too - just seems nicer
        yv.x = (double *)ya;

        f_plotv(title, &xv, &yv, xLabel, label);
}

void f_plotas(const char *title, const double *xa, const double **yas,
              const size_t rows, const size_t nvecs, const char *xLabel,
              const char **labels) {
        f_vecd xv = {.size = rows, .x = (double *)xa};

        f_vecd **ys_ptrs = malloc(sizeof(f_vecd *) * nvecs);
        f_vecd *ys_vals = malloc(sizeof(f_vecd) * nvecs);

        for (size_t i = 0; i < nvecs; ++i) {
                ys_vals[i].size = rows;
                ys_vals[i].x = (double *)yas[i];
                ys_ptrs[i] = &ys_vals[i];
        }

        f_plotvs(title, &xv, (const f_vecd **)ys_ptrs, nvecs, xLabel, labels);
        free(ys_vals);
        free(ys_ptrs);
}
