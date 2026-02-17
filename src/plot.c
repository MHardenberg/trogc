#include "forge/linalg.h"
#include <forge/plot.h>
#include <stdlib.h>
#include <string.h>

#define _BUFFER_LEN 1024

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

                strcat(dest, ".dat");

        } else {
                size_t result =
                    snprintf(dest, sizeof(char) * _BUFFER_LEN,
                             "%s/temp/figures/%s.dat", PROJECT_ROOT, "temp");
                assert(result > 0);
                assert(result <= sizeof(char) * _BUFFER_LEN);
        }
}

void _toDatFile(const char *dest, const f_vecd *x, const f_vecd **ys,
                const size_t nvecs) {
        assert(x != NULL);
        for (size_t i = 0; i < nvecs; ++i) {
                assert(ys[i] != NULL);
                assert(ys[i]->size == x->size);
        }

        FILE *fptr;
        fptr = fopen(dest, "w");
        assert(fptr != NULL);

        for (size_t r = 0; r < x->size; ++r) {
                fprintf(fptr, "%f, ", x->x[r]);
                for (size_t i = 0; i < nvecs; ++i) {
                        fprintf(fptr, "%f%s", ys[i]->x[r],
                                (i < nvecs - 1) ? "\t" : "\n");
                }
        }
        // Close the file
        fclose(fptr);
}

void f_plotv(const char *title, const f_vecd *x, const f_vecd *ys,
             const char *label) {
        f_plotvs(title, x, &ys, &label, 1);
}

void f_plotvs(const char *title, const f_vecd *x, const f_vecd **ys,
              const char **labels, size_t nvecs) {
        // write to temp file
        char dest[_BUFFER_LEN];
        _getFilePath(dest, title);
        _toDatFile(dest, x, ys, nvecs);

        FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
        if (title != NULL) {
                fprintf(gnuplot_pipe, "set title '%s'\n", title);
        }

        fprintf(gnuplot_pipe, "plot ");

        for (size_t i = 0; i < nvecs; ++i) {
                fprintf(gnuplot_pipe,
                        "'%s' using 1:%lu title \"%s\" with linespoints "
                        "linewidth 2 "
                        "pointsize 1 pointtype 7%s",
                        dest, i + 2, (labels != NULL) ? labels[i] : "",
                        (i < nvecs - 1) ? ", " : "\n");
        }

        fprintf(gnuplot_pipe, "refresh\n");
}

void f_plota(const char *title, const double *xa, const double *ya,
             const size_t rows, const char *label) {
        f_vecd yv, xv;
        xv.size = rows;
        yv.size = rows;
        xv.x = (double *)xa; // I hate this too - just seems nicer
        yv.x = (double *)ya;

        f_plotv(title, &xv, &yv, label);
}

void f_plotas(const char *title, const double *xa, const double **yas,
              const size_t rows, const size_t nvecs, const char **labels) {
        f_vecd xv = {.size = rows, .x = (double *)xa};

        f_vecd **ys_ptrs = malloc(sizeof(f_vecd *) * nvecs);
        f_vecd *ys_vals = malloc(sizeof(f_vecd) * nvecs);

        for (size_t i = 0; i < nvecs; ++i) {
                ys_vals[i].size = rows;
                ys_vals[i].x = (double *)yas[i];
                ys_ptrs[i] = &ys_vals[i];
        }

        f_plotvs(title, &xv, (const f_vecd **)ys_ptrs, labels, nvecs);
        free(ys_vals);
        free(ys_ptrs);
}
