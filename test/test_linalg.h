#ifndef TEST_ZERO_LINALG
#define TEST_ZERO_LINALG
#include "trog/mem/alloc.h"
#include <trog.h>
#include <trog/linalg.h>
#include <trog/mem/alloc.h>
#include <math.h>
#include <stddef.h>
#include <test.h>

static void test_linalg_tr_vecdAlloc() {
        tr_alloc alloc;
        size_t M = 100;

        tr_allocCreate(&alloc, ALLOC_ARENA);

        tr_vecd *v;
        int res = 0;
        for (size_t i = 0; i < M; ++i) {
                v = tr_vecdAlloc(&alloc, i + 1);
                for (size_t j = 0; j < i + 1; ++j) {
                        *tr_vecdIdx(v, j) = j;
                } // test writeable

                if (v->x == NULL) {
                        ++res;
                }

                if (v->size != i + 1) {
                        ++res;
                }
        }

        TEST_ZERO(res);
        tr_allocDestroy(&alloc);
}

static void test_linalg_tr_vecdAllocZero() {
        tr_alloc alloc;
        size_t M = 100;

        tr_allocCreate(&alloc, ALLOC_ARENA);

        tr_vecd *v;
        int res = 0;
        for (size_t i = 0; i < M; ++i) {
                v = tr_vecdAllocZero(&alloc, i + 1);
                for (size_t j = 0; j < i + 1; ++j) {
                        if (*tr_vecdIdx(v, i) != 0) {
                                ++res;
                        }
                        *tr_vecdIdx(v, j) = j; // test writeable
                }

                if (v->x == NULL) {
                        ++res;
                }

                if (v->size != i + 1) {
                        ++res;
                }
        }

        TEST_ZERO(res);
        tr_allocDestroy(&alloc);
}

static void test_linalg_tr_vecdOne() {
        int res = 0;
        size_t n = 10;
        double x[n];
        tr_vecd v = {.size = n, .x = x};

        tr_vecdOne(&v);

        for (size_t i = 0; i < n; ++i) {
                if (*tr_vecdIdx(&v, i) != 1.0) {
                        ++res;
                }
        }

        TEST_ZERO(res);
}

static void test_linalg_tr_vecdZero() {
        int res = 0;
        size_t n = 10;
        double x[n];
        tr_vecd v = {.size = n, .x = x};

        tr_vecdZero(&v);
        for (size_t i = 0; i < n; ++i) {
                if (*tr_vecdIdx(&v, i) != 0.0) {
                        ++res;
                }
        }

        TEST_ZERO(res);
}

static void test_linalg_tr_vecdIdx() {
        double x[] = {1.0f, 2.0f, 3.0f};
        tr_vecd v = {.size = 3U, .x = x};
        int res = 0;
        for (uint8_t i = 0; i < v.size; ++i) {
                if (x[i] != *tr_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST_ZERO(res);
}

static void test_linalg_tr_vecdSum() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);
        tr_vecd *v = tr_vecdAllocZero(&arena, 100);

        double actualSum = 0;
        for (size_t i = 0; i < v->size; ++i) {
                *tr_vecdIdx(v, i) = i;
                actualSum += i;
        }
        TEST_ZERO(actualSum - tr_vecdSum(v));
}

static void test_linalg_fvecdNorm() {
        double xs[] = {1, 2, 3, 4, 5};
        tr_vecd v = {.size = 5, .x = xs};

        double actualNorm = 0;
        for (size_t i = 0; i < 5; ++i) {
                actualNorm += xs[i] * xs[i];
        }

        actualNorm = sqrt(actualNorm);

        TEST_EQUAL(actualNorm, tr_vecdNorm(&v));
}

static void test_linalg_fvecdENorm() {
        double xs[] = {1, 2, 3, 4, 5};
        double ns[5];
        double rs[5];

        tr_vecd v = {.size = 5, .x = xs};
        tr_vecd elemNorm = {.size = 5, .x = rs};
        const tr_vecd *vs[] = {&v, &v};
        tr_vecd res = {.size = 5, .x = rs};

        for (size_t i = 0; i < 5; ++i) {
                ns[i] = sqrt(pow(xs[i], 2) * 2);
        }
        tr_vecd actualNorm = {.size = 5, .x = ns};

        tr_vecdENorm(&elemNorm, vs, 2);
        tr_vecdDiff(&res, &elemNorm, &actualNorm);
        TEST_ZERO(tr_vecdSum(&res));
}

static void test_linalg_tr_vecdMean() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);
        tr_vecd *v = tr_vecdAllocZero(&arena, 100);

        double actualMean = 0;
        for (size_t i = 0; i < v->size; ++i) {
                *tr_vecdIdx(v, i) = i;
                actualMean += i;
        }
        actualMean /= v->size;
        TEST_ZERO(actualMean - tr_vecdMean(v));
}

static void test_linalg_tr_vecdEMean() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);
        tr_vecd *v = tr_vecdAlloc(&arena, 100);
        tr_vecd *w = tr_vecdAlloc(&arena, 100);
        tr_vecd *testV = tr_vecdAlloc(&arena, 100);
        tr_vecd *testW = tr_vecdAllocZero(&arena, 100);

        for (size_t i = 0; i < v->size; ++i) {
                *tr_vecdIdx(v, i) = i;
                *tr_vecdIdx(w, i) = i * i;
                *tr_vecdIdx(testV, i) = ((double)(i + i * i)) / 2;
        }
        const tr_vecd *vs[] = {v, w};
        tr_vecdEMean(testW, vs, 2);

        int res = 0;
        for (size_t i = 0; i < v->size; ++i) {
                if (*tr_vecdIdx(testV, i) != *tr_vecdIdx(testW, i)) {
                        ++res;
                }
        }
        TEST_ZERO(res);
}

static void test_linalg_tr_vecdAdd() {
        double x[] = {1.0f, 2.0f, 3.0f};
        double y[] = {4.0f, 5.0f, 6.0f};
        double z[3];

        tr_vecd v = {.size = 3U, .x = x};
        tr_vecd w = {.size = 3U, .x = y};
        tr_vecd r = {.size = 3U, .x = z};
        int res = 0;

        tr_vecdAdd(&r, &v, &w);
        for (uint8_t i = 0; i < v.size; ++i) {
                if (x[i] + y[i] != *tr_vecdIdx(&r, i)) {
                        ++res;
                }
        }

        TEST_ZERO(res);
}

static void test_linalg_tr_vecdDiff() {
        double x[] = {1.0f, 2.0f, 3.0f};
        double y[] = {4.0f, 5.0f, 6.0f};
        double z[3];

        tr_vecd v = {.size = 3U, .x = x};
        tr_vecd w = {.size = 3U, .x = y};
        tr_vecd r = {.size = 3U, .x = z};
        int res = 0;

        tr_vecdDiff(&r, &v, &w);
        for (uint8_t i = 0; i < v.size; ++i) {
                if (x[i] - y[i] != *tr_vecdIdx(&r, i)) {
                        ++res;
                }
        }

        TEST_ZERO(res);
}

static void test_linalg_tr_vecdIncr() {
        double a = 123.456;
        double x[] = {1.0f, 2.0f, 3.0f};
        double y[] = {a + 1.0f, a + 2.0f, a + 3.0f};

        tr_vecd v = {.size = 3U, .x = x};
        tr_vecdIncr(&v, a, &v);

        int res = 0;
        for (uint8_t i = 0; i < v.size; ++i) {
                if (y[i] != *tr_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST_ZERO(res);
}

static void test_linalg_tr_vecdEmul() {
        double a = 1.0, b = 2.0, c = 3.0;
        double d = 4.0, e = 2.0, f = 3.0;
        double x[] = {a, b, c};
        double y[] = {d, e, f};

        double alpha = 123.456;
        tr_vecd v = {.size = 3U, .x = x};
        tr_vecd w = {.size = 3U, .x = y};
        double z[] = {alpha * a * d, alpha * b * e, alpha * c * f};
        int res = 0;

        tr_vecdEmul(&v, alpha, &v, &w);
        for (uint8_t i = 0; i < v.size; ++i) {
                if (z[i] != *tr_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST_ZERO(res);
}

static void test_linalg_tr_vecdMul() {
        double a = 1.0, b = 2.0, c = 3.0;
        double d = 4.0, e = 2.0, f = 3.0;
        double x[] = {a, b, c};
        double y[] = {d, e, f};

        tr_vecd v = {.size = 3U, .x = x};
        tr_vecd w = {.size = 3U, .x = y};
        int res = 0;

        double s = tr_vecdMul(&v, &w);
        double r = a * d + b * e + c * f;

        if (s != r) {
                ++res;
        }
        TEST_ZERO(res);
}

static void test_linalg_tr_vecdScale() {
        double a = 1.0, b = 2.0, c = 3.0;
        double alpha = 123.456;
        double x[] = {a, b, c};
        double y[] = {alpha * a, alpha * b, alpha * c};
        tr_vecd v = {.size = 3U, .x = x};
        tr_vecdScale(&v, alpha, &v);

        int res = 0;
        for (uint8_t i = 0; i < v.size; ++i) {
                if (y[i] != *tr_vecdIdx(&v, i)) {
                        ++res;
                }
        }

        if (v.size != 3U) {
                ++res;
        }
        TEST_ZERO(res);
}

static void test_linalg_tr_matdIdx() {
        double x[3][2] = {{1, 4}, {2, 5}, {3, 6}}; // column major
        tr_matd m = {.rows = 2, .cols = 3, .x = (double *)x};
        int res = 0;
        size_t idx = 0;
        for (size_t i = 0; i < m.rows; ++i) {
                for (size_t j = 0; j < m.cols; ++j) {
                        idx = m.rows * j + i;
                        // printf("%f %f %d %d %d\n", m.x[idx],
                        //        *tr_matdIdx(&m, i, j), i, j, idx);
                        if (m.x[idx] != *tr_matdIdx(&m, i, j)) {
                                ++res;
                        }
                }
        }

        // tr_matdPrint(&m);
        TEST_ZERO(res);
}

static void test_linalg_tr_matdIsTranspose() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);
        tr_matd *m0 = tr_matdAlloc(&arena, 4, 6);
        tr_matd *m1 = tr_matdAlloc(&arena, 6, 4);

        for (size_t r = 0; r < m0->rows; ++r) {
                for (size_t c = 0; c < m0->cols; ++c) {
                        *tr_matdIdx(m0, r, c) = r * c;
                        *tr_matdIdx(m1, c, r) = r * c;
                }
        }

        TEST_TRUE(tr_matdIsTranspose(m0, m1));
}
static void test_linalg_tr_matdTranspose() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);
        tr_matd *m = tr_matdAlloc(&arena, 10, 5);
        tr_matd *mT = tr_matdAlloc(&arena, 5, 10);
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *tr_matdIdx(m, r, c) = r * c;
                }
        }

        tr_matdTranspose(mT, m);
        TEST_TRUE(tr_matdIsTranspose(mT, m));
}

static void test_linalg_tr_matdMVMul() {
        int res = 0;

        double mx[3][2] = {{1, 4}, {2, 5}, {3, 6}}; // column major
        double vx[3] = {7, 8, 9};
        double yx[2] = {0, 0};
        double expectedY[2] = {550, 1342};

        tr_matd m = {.rows = 2, .cols = 3, .x = (double *)mx};
        tr_vecd v = {.size = 3, .x = vx};
        tr_vecd y = {.size = 2, .x = yx};
        double alpha = 11;
        tr_matdMVMul(&y, &m, &v, alpha);

        /*
            tr_matdPrint(&m);
            tr_vecdPrint(&v);
            tr_vecdPrint(&y);
        */

        for (size_t i = 0; i < 2; ++i) {
                if (expectedY[i] != *tr_vecdIdx(&y, i)) {
                        ++res;
                }
        }
        TEST_ZERO(res);
}

static void test_linalg_tr_matdMMul() {
        int res = 0;

        double mx[3][2] = {{1, 4}, {2, 5}, {3, 6}}; // column major
        double nx[2][3] = {{1, 3, 5}, {2, 4, 6}};
        double yx[2][2] = {{0, 0}, {0, 0}};

        double expectedY[2][2] = {{242, 539}, {308, 704}};

        tr_matd m = {.rows = 2, .cols = 3, .x = (double *)mx};
        tr_matd n = {.rows = 3, .cols = 2, .x = (double *)nx};
        tr_matd y = {.rows = 2, .cols = 2, .x = (double *)yx};
        tr_matd expected = {.rows = 2, .cols = 2, .x = (double *)expectedY};
        double alpha = 11;

        tr_matdMMul(&y, alpha, &m, &n);

        /*
            tr_matdPrint(&m);
            tr_matdPrint(&n);
            tr_matdPrint(&y);
            tr_matdPrint(&expected);
        */

        for (size_t i = 0; i < y.rows; ++i) {
                for (size_t j = 0; j < y.cols; ++j) {
                        if (*tr_matdIdx(&expected, i, j) !=
                            *tr_matdIdx(&y, i, j)) {
                                ++res;
                        }
                }
        }

        TEST_ZERO(res)
}

void test_linalg_tr_matdRowCpy() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);

        size_t stride = 3;
        tr_matd *M = tr_matdAlloc(&arena, 10, 20);
        tr_vecd *row = tr_vecdAlloc(&arena, M->cols / stride);

        for (size_t r = 0; r < M->rows; ++r) {
                for (size_t c = 0; c < M->cols; ++c) {
                        *tr_matdIdx(M, r, c) = r * c;
                }
        }

        tr_matdColCpy(row, M, 4, stride);

        int res = 0;

        for (size_t c = 0; c < M->cols / stride; ++c) {
                if (*tr_matdIdx(M, 4, c) != *tr_vecdIdx(row, c)) {
                        ++res;
                }
        }

        TEST_ZERO(res);
}

void test_linalg_tr_matdColCpy() {
        tr_alloc arena;
        tr_allocCreate(&arena, ALLOC_ARENA);

        size_t stride = 3;
        tr_matd *M = tr_matdAlloc(&arena, 10, 20);
        tr_vecd *col = tr_vecdAlloc(&arena, M->rows / stride);

        for (size_t r = 0; r < M->rows; ++r) {
                for (size_t c = 0; c < M->cols; ++c) {
                        *tr_matdIdx(M, r, c) = r * c;
                }
        }

        tr_matdColCpy(col, M, 4, stride);

        int res = 0;

        for (size_t r = 0; r < M->rows / stride; ++r) {
                if (*tr_matdIdx(M, r, 4) != *tr_vecdIdx(col, r)) {
                        ++res;
                }
        }

        TEST_ZERO(res);
}

void tr_matdRowCpy(tr_vecd *dest, const tr_matd *m, const size_t r,
                   size_t stride);

void test_modLinalg() {
        // vectors
        test_linalg_tr_vecdAlloc();
        test_linalg_tr_vecdAllocZero();

        test_linalg_tr_vecdZero();
        test_linalg_tr_vecdOne();

        test_linalg_tr_vecdIdx();
        test_linalg_tr_vecdAdd();
        test_linalg_tr_vecdDiff();
        test_linalg_tr_vecdIncr();
        test_linalg_tr_vecdEmul();
        test_linalg_tr_vecdMul();
        test_linalg_tr_vecdScale();

        test_linalg_fvecdENorm();
        test_linalg_fvecdNorm();
        test_linalg_tr_vecdSum();
        test_linalg_tr_vecdEMean();
        test_linalg_tr_vecdMean();

        // matrices
        test_linalg_tr_matdIdx();
        test_linalg_tr_matdMVMul();
        test_linalg_tr_matdMMul();
        test_linalg_tr_matdIsTranspose();
        test_linalg_tr_matdTranspose();
}

#endif // TEST_ZERO_LINALG_
