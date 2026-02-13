#include <forge/plot.h>

void f_plot(const char *name, const f_vecd *x, const f_vecd *y, size_t nvecs) {
        // open persistent gnuplot window
        FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
        // basic settings
        fprintf(gnuplot_pipe, "set title '%s'\n", name);
        // fill it with data
        fprintf(gnuplot_pipe, "plot '-' with linespoints linewidth 2 pointsize "
                              "1 pointtype 7\n");
        for (size_t i = 0; i < nvecs; ++i) {
                for (size_t j = 0; j < x->size; ++j) {
                        fprintf(gnuplot_pipe, "%f, %f\n", x[i].x[j], y[i].x[j]);
                }
        }
        fprintf(gnuplot_pipe, "e\n");
        fprintf(gnuplot_pipe, "refresh\n");
}
