#include <trog/linalg.h>
#include <trog/plot.h>

#include "test_linalg.h"
#include "test_alloc.h"

int main() {
        test_tr_alloc();
        test_modLinalg();

        /*
                // Plotting
                double x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                double y0[10];
                double y1[10];
                const double *ys[] = {y0, y1};
                for (int i = 0; i < 10; ++i) {
                        y0[i] = x[i] * x[i];
                        y1[i] = x[i] * x[i] * x[i];
                }
                tr_vecd vx = {.size = 10, .x = x};
                tr_vecd vy0 = {.size = 10, .x = y0};
                tr_vecd vy1 = {.size = 10, .x = y1};

                const tr_vecd *vs[2] = {&vy0, &vy1};
                const char *labels[2] = {"y0", "y1"};
                tr_plotv("Test vector", &vx, &vy0, "x", labels[0]);
                tr_plotvs("Test vectors", &vx, vs, 2, "x", labels);

                tr_plota("Test array", vx.x, vy0.x, vx.size, "x", labels[0]);
                tr_plotas("Test arrays", x, ys, vx.size, 2, "x", labels);
                return 0;
        */
}
