#include "forge/mem/alloc.h"
#include <math.h>
#include <float.h>

#include <forge/linalg.h>
#include <forge/plot.h>
#include <forge/data.h>

#define _BUFFER_LEN 1024
#define _MAX_PLOT_POINTS 10000LL

void f_plotv(const char *title, const f_vecd *x, const f_vecd *ys,
             const char *xLabel, const char *label) {
        f_plotvs(title, x, &ys, 1, xLabel, &label);
}

void f_plotvs(const char *title, const f_vecd *x, const f_vecd **ys,
              const size_t nvecs, const char *xLabel, const char **labels) {
        // write to temp file
        f_alloc alloc;
        f_allocCreate(&alloc, ALLOC_ARENA);
        char *path = f_allocPush(&alloc, 2048);
        f_getFilePath(path, title);

        FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
        if (title != NULL) {
                fprintf(gnuplot_pipe, "set title '%s'\n", title);
        }

        fprintf(gnuplot_pipe,
                "set terminal pdfcairo font 'Arial,12' size 5,3\n");
        fprintf(gnuplot_pipe, "set output '%s.pdf'\n", path);

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
                        path, i + 2, (labels != NULL) ? labels[i] : "",
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
