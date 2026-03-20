#ifndef PLOT_H
#define PLOT_H

#include <forge.h>
#include <forge/linalg.h>

void f_plotv(const char *title, const f_vecd *x, const f_vecd *ys,
             const char *xlabel, const char *label);

void f_plotvs(const char *title, const f_vecd *x, const f_vecd **ys,
              const size_t nvecs, const char *xlabel, const char **labels);

void f_plota(const char *title, const double *x, const double *ya,
             const size_t rows, const char *xlabel, const char *label);

void f_plotas(const char *title, const double *x, const double **yas,
              const size_t rows, const size_t nvecs, const char *xlabel,
              const char **labels);

#endif // PLOT_H
