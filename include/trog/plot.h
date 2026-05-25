#ifndef PLOT_H
#define PLOT_H

#include <trog.h>
#include <trog/linalg.h>

void tr_plotv(const char *title, const tr_vecd *x, const tr_vecd *ys,
              const char *xlabel, const char *label);

void tr_plotvs(const char *title, const tr_vecd *x, const tr_vecd **ys,
               const size_t nvecs, const char *xlabel, const char **labels);

void tr_plota(const char *title, const double *x, const double *ya,
              const size_t rows, const char *xlabel, const char *label);

void tr_plotas(const char *title, const double *x, const double **yas,
               const size_t rows, const size_t nvecs, const char *xlabel,
               const char **labels);

#endif // PLOT_H
