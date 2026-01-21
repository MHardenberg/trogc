#include "test.h"

#include <forge/linalg.h>
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
int test_linalg_f_matdIdx();

int main() {
        test_linalg_f_vecdZeros();
        test_linalg_f_vecdOnes();
        test_linalg_f_vecdIdx();
        test_linalg_f_vecdAdd();
        test_linalg_f_vecdIncr();
        test_linalg_f_vecdEmul();
        test_linalg_f_vecdMul();
        test_linalg_f_vecdScale();
        return 0;
}
