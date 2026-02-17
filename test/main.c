#include "test.h"

#include <forge/linalg.h>
#include <forge/plot.h>

// ---------- Linalg ----------------------------------------------------------
void test_linalg_f_vecdOnes() {
        int res = 0;
        size_t n = 10;
        double x[n];
        f_vecd v = {.size = n, .x = x};

        f_vecdOnes(&v);

        for (size_t i = 0; i < n; ++i) {
                if (*f_vecdIdx(&v, i) != 1.0) {
                        ++res;
                }
        }

        TEST(res);
}

void test_linalg_f_vecdZeros() {
        int res = 0;
        size_t n = 10;
        double x[n];
        f_vecd v = {.size = n, .x = x};

        f_vecdZeros(&v);
        for (size_t i = 0; i < n; ++i) {
                if (*f_vecdIdx(&v, i) != 0.0) {
                        ++res;
                }
        }

        TEST(res);
}

void test_linalg_f_vecdIdx() {
        double x[] = {1.0f, 2.0f, 3.0f};
        f_vecd v = {.size = 3U, .x = x};
        int res = 0;
        for (uint8_t i = 0; i < v.size; ++i) {
                if (x[i] != *f_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST(res);
}

void test_linalg_f_vecdAdd() {
        double x[] = {1.0f, 2.0f, 3.0f};
        double y[] = {4.0f, 5.0f, 6.0f};

        f_vecd v = {.size = 3U, .x = x};
        f_vecd w = {.size = 3U, .x = y};
        int res = 0;

        f_vecdAdd(&v, &v, &w);
        for (uint8_t i = 0; i < v.size; ++i) {
                if (x[i] != *f_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST(res);
}

void test_linalg_f_vecdIncr() {
        double a = 123.456;
        double x[] = {1.0f, 2.0f, 3.0f};
        double y[] = {a + 1.0f, a + 2.0f, a + 3.0f};

        f_vecd v = {.size = 3U, .x = x};
        f_vecdIncr(&v, a, &v);

        int res = 0;
        for (uint8_t i = 0; i < v.size; ++i) {
                if (y[i] != *f_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST(res);
}

void test_linalg_f_vecdEmul() {
        double a = 1.0, b = 2.0, c = 3.0;
        double d = 4.0, e = 2.0, f = 3.0;
        double x[] = {a, b, c};
        double y[] = {d, e, f};

        double alpha = 123.456;
        f_vecd v = {.size = 3U, .x = x};
        f_vecd w = {.size = 3U, .x = y};
        double z[] = {alpha * a * d, alpha * b * e, alpha * c * f};
        int res = 0;

        f_vecdEmul(&v, alpha, &v, &w);
        for (uint8_t i = 0; i < v.size; ++i) {
                if (z[i] != *f_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST(res);
}

void test_linalg_f_vecdMul() {
        double a = 1.0, b = 2.0, c = 3.0;
        double d = 4.0, e = 2.0, f = 3.0;
        double x[] = {a, b, c};
        double y[] = {d, e, f};

        f_vecd v = {.size = 3U, .x = x};
        f_vecd w = {.size = 3U, .x = y};
        int res = 0;

        double s = f_vecdMul(&v, &w);
        double r = a * d + b * e + c * f;

        if (s != r) {
                ++res;
        }
        TEST(res);
}

void test_linalg_f_vecdScale() {
        double a = 1.0, b = 2.0, c = 3.0;
        double alpha = 123.456;
        double x[] = {a, b, c};
        double y[] = {alpha * a, alpha * b, alpha * c};
        f_vecd v = {.size = 3U, .x = x};
        f_vecdScale(&v, alpha, &v);

        int res = 0;
        for (uint8_t i = 0; i < v.size; ++i) {
                if (y[i] != *f_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST(res);
}

void test_linalg_f_matdIdx() {
        double x[3][2] = {{1, 4}, {2, 5}, {3, 6}}; // column major
        f_matd m = {.rows = 2, .cols = 3, .x = (double *)x};
        int res = 0;
        size_t idx = 0;
        for (size_t i = 0; i < m.rows; ++i) {
                for (size_t j = 0; j < m.cols; ++j) {
                        idx = m.rows * j + i;
                        // printf("%f %f %d %d %d\n", m.x[idx],
                        //        *f_matdIdx(&m, i, j), i, j, idx);
                        if (m.x[idx] != *f_matdIdx(&m, i, j)) {
                                ++res;
                        }
                }
        }

        // f_matdPrint(&m);
        TEST(res);
}

void test_linalg_f_matdMVMul() {
        int res = 0;

        double mx[3][2] = {{1, 4}, {2, 5}, {3, 6}}; // column major
        double vx[3] = {7, 8, 9};
        double yx[2] = {0, 0};
        double expectedY[2] = {550, 1342};

        f_matd m = {.rows = 2, .cols = 3, .x = (double *)mx};
        f_vecd v = {.size = 3, .x = vx};
        f_vecd y = {.size = 2, .x = yx};
        double alpha = 11;
        f_matdMVMul(&y, &m, &v, alpha);

        /*
            f_matdPrint(&m);
            f_vecdPrint(&v);
            f_vecdPrint(&y);
        */

        for (size_t i = 0; i < 2; ++i) {
                if (expectedY[i] != *f_vecdIdx(&y, i)) {
                        ++res;
                }
        }
        TEST(res);
}

void test_linalg_f_matdMMul() {
        int res = 0;

        double mx[3][2] = {{1, 4}, {2, 5}, {3, 6}}; // column major
        double nx[2][3] = {{1, 3, 5}, {2, 4, 6}};
        double yx[2][2] = {{0, 0}, {0, 0}};

        double expectedY[2][2] = {{242, 539}, {308, 704}};

        f_matd m = {.rows = 2, .cols = 3, .x = (double *)mx};
        f_matd n = {.rows = 3, .cols = 2, .x = (double *)nx};
        f_matd y = {.rows = 2, .cols = 2, .x = (double *)yx};
        f_matd expected = {.rows = 2, .cols = 2, .x = (double *)expectedY};
        double alpha = 11;

        f_matdMMul(&y, alpha, &m, &n);

        /*
            f_matdPrint(&m);
            f_matdPrint(&n);
            f_matdPrint(&y);
            f_matdPrint(&expected);
        */

        for (size_t i = 0; i < y.rows; ++i) {
                for (size_t j = 0; j < y.cols; ++j) {
                        if (*f_matdIdx(&expected, i, j) !=
                            *f_matdIdx(&y, i, j)) {
                                ++res;
                        }
                }
        }
        TEST(res)
}

int main() {
        // vectors
        test_linalg_f_vecdZeros();
        test_linalg_f_vecdOnes();
        test_linalg_f_vecdIdx();
        test_linalg_f_vecdAdd();
        test_linalg_f_vecdIncr();
        test_linalg_f_vecdEmul();
        test_linalg_f_vecdMul();
        test_linalg_f_vecdScale();

        // matrices
        test_linalg_f_matdIdx();
        test_linalg_f_matdMVMul();
        test_linalg_f_matdMMul();

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
        LOG(PROJECT_ROOT);
        f_plotv("Test vector", &vx, &vy0, labels[0]);
        f_plotvs("Test vectors", &vx, vs, labels, 2);

        f_plota("Test array", vx.x, vy0.x, vx.size, labels[0]);
        f_plotas("Test arrays", x, ys, vx.size, 2, labels);
        return 0;
}
