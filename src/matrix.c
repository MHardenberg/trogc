#include <assert.h>
#include <openblas/cblas.h>
#include <float.h>

#include <forge.h>
#include <forge/mem/alloc.h>
#include <forge/linalg.h>
#include <string.h>

f_matd *f_matdAlloc(f_alloc *alloc, size_t rows, size_t cols) {
        f_assert(alloc != NULL);
        f_matd *dest = f_allocPush(alloc, sizeof(f_matd));
        dest->x = f_allocPush(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

f_matd *f_matdAllocZero(f_alloc *alloc, size_t rows, size_t cols) {
        f_assert(alloc != NULL);
        f_matd *dest = f_allocPush(alloc, sizeof(f_matd));
        dest->x = f_allocPushZero(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

void f_matdFree(f_alloc *alloc, f_matd *m) {
        f_assert(alloc != NULL);
        f_assert(m != NULL);
        f_allocFree(alloc, m->x);
        f_allocFree(alloc, m);
}

void f_matdCopy(f_matd *dest, f_matd *source) {
        f_assert(dest != NULL);
        f_assert(source != NULL);
        dest->cols = source->cols;
        dest->rows = source->rows;
        memcpy(dest->x, source->x, sizeof(double) * dest->cols * dest->rows);
}

double *f_matdIdx(const f_matd *m, const size_t r, const size_t c) {
        f_assert(m != NULL);
        f_assert(r < m->rows);
        f_assert(c < m->cols);
        return m->x + (c * m->rows + r);
}

void f_matdCol(f_vecd *dest, const f_matd *m, const size_t c) {
        f_assert(dest != NULL);
        f_assert(m != NULL);
        dest->size = m->rows;
        dest->x = f_matdIdx(m, 0, c);
}

f_vec2d *f_matdColv2(const f_matd *m, const size_t c) {
        f_assert(m != NULL);
        f_assert(m->rows == 2);
        f_vec2d *v = (void *)f_matdIdx(m, 0, c);
        return v;
}

f_vec3d *f_matdColv3(const f_matd *m, const size_t c) {
        f_assert(m != NULL);
        f_assert(m->rows == 3);
        f_vec3d *v = (void *)f_matdIdx(m, 0, c);
        return v;
}

f_vec4d *f_matdColv4(const f_matd *m, const size_t c) {
        f_assert(m != NULL);
        f_assert(m->rows == 4);
        f_vec4d *v = (void *)f_matdIdx(m, 0, c);
        return v;
}

void f_matdColslice(f_matd *dest, const f_matd *m, const size_t fromCol,
                    const size_t toCol) {
        f_assert(dest != NULL);
        f_assert(m != NULL);
        f_assert(fromCol < m->cols);
        f_assert(toCol <= m->cols);

        dest->cols = toCol - fromCol;
        dest->rows = m->rows;

        dest->x = f_matdIdx(m, 0, fromCol);
}

void f_matdRowCpy(f_vecd *dest, const f_matd *m, const size_t r,
                  size_t stride) {
        f_assert(dest->size == m->cols / stride);
        f_assert(stride > 0 && stride <= m->cols);
        f_assert(dest->size <= m->cols);
        for (size_t i = 0; i < dest->size; i += stride) {
                dest->x[i] = *f_matdIdx(m, r, i);
        }
}

void f_matdColCpy(f_vecd *dest, const f_matd *m, const size_t c,
                  size_t stride) {
        f_assert(dest->size == m->rows / stride);
        f_assert(stride > 0 && stride <= m->rows);
        f_assert(dest->size <= m->rows);
        for (size_t i = 0; i < dest->size; i += stride) {
                dest->x[i] = *f_matdIdx(m, i, c);
        }
}

bool f_matdIsTranspose(f_matd *m0, f_matd *m1) {
        if (m0->rows != m1->cols) {
                return false;
        }
        if (m1->rows != m0->cols) {
                return false;
        }

        for (size_t r = 0; r < m0->rows; ++r) {
                for (size_t c = 0; c < m0->cols; ++c) {
                        if (*f_matdIdx(m0, r, c) != *f_matdIdx(m1, c, r))
                                return false;
                }
        }
        return true;
}

void f_matdTranspose(f_matd *dest, const f_matd *m) {
        f_assert(m != NULL);
        f_assert(dest != NULL);
        // check if enough allocated space
        f_assert(dest->cols * dest->rows == m->rows * m->cols);

        f_matd *mT;
        f_alloc alloc;
        size_t srcRows = m->rows;
        size_t srcCols = m->cols;
        if (dest == m) {
                // allow for inplace transposition by copying memory later
                f_allocCreate(&alloc, ALLOC_HEAP);
                mT = f_matdAlloc(&alloc, srcCols, srcRows);
        } else {
                mT = dest;
        }

        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *f_matdIdx(mT, c, r) = *f_matdIdx(m, r, c);
                }
        }

        if (dest == m) {
                memcpy(dest->x, mT->x, sizeof(double) * mT->rows * mT->cols);
                f_matdFree(&alloc, mT);
        }

        dest->cols = srcRows;
        dest->rows = srcCols;
}

void f_matdOne(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *f_matdIdx(m, r, c) = 1.0;
                }
        }
}

void f_matdZero(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *f_matdIdx(m, r, c) = 0.0;
                }
        }
}

void f_matdIdent(f_matd *m) {
        f_assert(m->rows == m->cols);
        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *f_matdIdx(m, r, c) = (c == r) ? 1.0 : 0.0;
                }
        }
}

void f_matdScale(f_matd *dest, f_matd *m, double a) {
        f_assert(dest != NULL);
        f_assert(m != NULL);
        f_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] * a;
        }
}

void f_matdIncr(f_matd *dest, f_matd *m, double a) {
        f_assert(dest != NULL);
        f_assert(m != NULL);
        f_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] + a;
        }
}

void f_matdAdd(f_matd *dest, f_matd *m, f_matd *n) {
        f_assert(dest != NULL);
        f_assert(m != NULL);
        f_assert(n != NULL);
        f_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        f_assert((n->cols = m->cols) && (n->rows = m->rows));

        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] + n->x[i];
        }
}

void f_matdScAdd(f_matd *dest, f_matd *m, double a, f_matd *n) {
        f_assert(dest != NULL);
        f_assert(m != NULL);
        f_assert(n != NULL);
        f_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        f_assert((n->cols = m->cols) && (n->rows = m->rows));

        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] + a * n->x[i];
        }
}

void f_matdMVMul(f_vecd *dest, const f_matd *m, const f_vecd *v,
                 const double a) {
#ifdef _BLAS
        cblas_dgemv(CblasColMajor, CblasNoTrans, m->rows, m->cols, a, m->x,
                    m->rows, v->x, 1, 0.0, dest->x, 1);
#else
#error "Not implemented!"
#endif
}

void f_matdMMul(f_matd *dest, const double alpha, const f_matd *a,
                const f_matd *b) {
#ifdef _BLAS
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, a->rows, b->cols,
                    a->cols, alpha, a->x, a->rows, b->x, b->rows, 1.0, dest->x,
                    dest->rows);
#else
#error "Not implemented!"
#endif
}

void f_matdPrint(f_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                printf("| ");

                // shorten
                if (r > 10) {
                        for (size_t c = 0; c < m->cols; ++c) {
                                if (0 == c) {
                                        printf("     :      ");
                                } else {
                                        printf(",      :      ");
                                }
                        }
                        printf(" |\n| ");
                        for (size_t c = 0; c < m->cols; ++c) {
                                if (0 == c) {
                                        printf("%.6e",
                                               *f_matdIdx(m, m->rows - 1, c));
                                } else {
                                        printf(", %.6e",
                                               *f_matdIdx(m, m->rows - 1, c));
                                }
                        }

                        printf(" |\n");
                        break;
                }
                // actual print
                for (size_t c = 0; c < m->cols; ++c) {
                        if (c > 5) {
                                printf(", ...");
                                printf(", %.6e", *f_matdIdx(m, r, c));
                                break;
                        }
                        if (0 == c) {
                                printf("%.6e", *f_matdIdx(m, r, c));
                        } else {
                                printf(", %.6e", *f_matdIdx(m, r, c));
                        }
                }
                printf(" |\n");
        }
        printf("<%lu by %lu matrix>\n", m->rows, m->cols);
}
