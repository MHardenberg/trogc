#include <string.h>
#include <forge/linalg.h>
#include <forge/plot.h>
#include "test.h"
#include "test_linalg.h"
#include "test_alloc.h"

int main() {
        test_f_alloc();
        test_modLinalg();

        // Plotting
        double x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        double y0[10];
        double y1[10];
        const double *ys[] = {y0, y1};
        for (int i = 0; i < 10; ++i) {
                y0[i] = x[i] * x[i];
                y1[i] = x[i] * x[i] * x[i];
        }
        f_vecd vx = {.size = 10, .x = x};
        f_vecd vy0 = {.size = 10, .x = y0};
        f_vecd vy1 = {.size = 10, .x = y1};

        const f_vecd *vs[2] = {&vy0, &vy1};
        const char *labels[2] = {"y0", "y1"};
        f_plotv("Test vector", &vx, &vy0, labels[0]);
        f_plotvs("Test vectors", &vx, vs, labels, 2);

        f_plota("Test array", vx.x, vy0.x, vx.size, labels[0]);
        f_plotas("Test arrays", x, ys, vx.size, 2, labels);
        return 0;
}
