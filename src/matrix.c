#include <openblas/cblas.h>
#include <float.h>

#include <forge.h>
#include <forge/mem/alloc.h>
#include <forge/linalg.h>

f_matd *f_matdAlloc(f_alloc *alloc, size_t rows, size_t cols) {
        assert(alloc != NULL);
        f_matd *dest = f_allocPush(alloc, sizeof(f_matd));
        dest->x = f_allocPush(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

f_matd *f_matdAllocZero(f_alloc *alloc, size_t rows, size_t cols) {
        assert(alloc != NULL);
        f_matd *dest = f_allocPush(alloc, sizeof(f_matd));
        dest->x = f_allocPushZero(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

void f_matdFree(f_alloc *alloc, f_matd *m) {
        assert(alloc != NULL);
        assert(m != NULL);
        f_allocFree(alloc, m->x);
        f_allocFree(alloc, m);
}

void f_matdCopy(f_matd *dest, f_matd *source) {
        dest->cols = source->cols;
        dest->rows = source->rows;
        memcpy(dest->x, source->x, sizeof(double) * dest->cols * dest->rows);
}

double *f_matdIdx(const f_matd *m, const size_t r, const size_t c) {
        assert((r < m->rows) && (c < m->cols));
        return m->x + (c * m->rows + r);
}

void f_matdCol(f_vecd *dest, const f_matd *m, const size_t c) {
        assert(dest != NULL);
        assert(m != NULL);
        dest->size = m->rows;
        dest->x = f_matdIdx(m, 0, c);
}

void f_matdRowCpy(f_vecd *dest, const f_matd *m, const size_t r,
                  size_t stride) {
        assert(dest->size == m->cols / stride);
        assert(stride > 0 && stride <= m->cols);
        assert(dest->size <= m->cols);
        for (size_t i = 0; i < dest->size; i += stride) {
                dest->x[i] = *f_matdIdx(m, r, i);
        }
}

void f_matdColCpy(f_vecd *dest, const f_matd *m, const size_t c,
                  size_t stride) {
        assert(dest->size == m->rows / stride);
        assert(stride > 0 && stride <= m->rows);
        assert(dest->size <= m->rows);
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
        assert(m != NULL);
        assert(dest != NULL);
        // check if enough allocated space
        assert(dest->cols * dest->rows == m->rows * m->cols);
        assert(dest->x != m->x); // cannot be inplace!

        // allow for inplace transposition by repurposing memory later
        f_matd mT = {.rows = m->cols, .cols = m->rows, .x = dest->x};
        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *f_matdIdx(&mT, c, r) = *f_matdIdx(m, r, c);
                }
        }

        *dest = mT; // copy / overwrite settings so that inplace works
                    // (its like 3 numbers - live with it)
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
        assert(m->rows == m->cols);
        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *f_matdIdx(m, r, c) = (c == r) ? 1.0 : 0.0;
                }
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
                                        printf(":");
                                } else {
                                        printf(", :");
                                }
                        }
                        for (size_t c = 0; c < m->cols; ++c) {
                                if (0 == c) {
                                        printf("%.6e",
                                               *f_matdIdx(m, m->rows - 1, c));
                                } else {
                                        printf(", %.6e",
                                               *f_matdIdx(m, m->rows - 1, c));
                                }
                        }
                        break;
                }
                // actual print
                for (size_t c = 0; c < m->cols; ++c) {
                        if (c > 10) {
                                printf(", ...");
                                printf(", %.4e", *f_matdIdx(m, r, c));
                                break;
                        }
                        if (0 == c) {
                                printf("%.4e", *f_matdIdx(m, r, c));
                        } else {
                                printf(", %.4e", *f_matdIdx(m, r, c));
                        }
                }
                printf(" |\n");
        }
        printf("\n");
}
