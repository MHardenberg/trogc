#include "trogAssert.h"
#include <assert.h>
#include <openblas/cblas.h>
#include <float.h>

#include <trog.h>
#include <trog/mem/alloc.h>
#include <trog/linalg.h>
#include <string.h>

tr_matd *tr_matdAlloc(tr_alloc *alloc, size_t rows, size_t cols) {
        tr_assert(alloc != NULL);
        tr_matd *dest = tr_allocPush(alloc, sizeof(tr_matd));
        dest->x = tr_allocPush(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

tr_matd *tr_matdAllocZero(tr_alloc *alloc, size_t rows, size_t cols) {
        tr_assert(alloc != NULL);
        tr_matd *dest = tr_allocPush(alloc, sizeof(tr_matd));
        dest->x = tr_allocPushZero(alloc, sizeof(double) * cols * rows);
        dest->cols = cols;
        dest->rows = rows;
        return dest;
}

tr_matd *tr_matdAllocLike(tr_alloc *alloc, tr_matd *source) {
        tr_assert(alloc != NULL);
        tr_assert(source != NULL);
        return tr_matdAlloc(alloc, source->rows, source->cols);
}

tr_matd *tr_matdAllocLikeZero(tr_alloc *alloc, tr_matd *source) {
        tr_assert(alloc != NULL);
        tr_assert(source != NULL);
        return tr_matdAllocZero(alloc, source->rows, source->cols);
}

tr_matd *tr_matdAllocCpy(tr_alloc *alloc, tr_matd *source) {
        tr_assert(alloc != NULL);
        tr_assert(source != NULL);
        tr_matd *dest = tr_matdAllocLike(alloc, source);
        tr_matdCopy(dest, source);
        return dest;
}

void tr_matdFree(tr_alloc *alloc, tr_matd *m) {
        tr_assert(alloc != NULL);
        tr_assert(m != NULL);
        tr_allocFree(alloc, m->x);
        tr_allocFree(alloc, m);
}

void tr_matdCopy(tr_matd *dest, tr_matd *source) {
        tr_assert(dest != NULL);
        tr_assert(source != NULL);
        dest->cols = source->cols;
        dest->rows = source->rows;
        memcpy(dest->x, source->x, sizeof(double) * dest->cols * dest->rows);
}

double *tr_matdIdx(const tr_matd *m, const size_t r, const size_t c) {
        tr_assert(m != NULL);
        tr_assert(r < m->rows);
        tr_assert(c < m->cols);
        return m->x + (c * m->rows + r);
}

void tr_matdCol(tr_vecd *dest, const tr_matd *m, const size_t c) {
        tr_assert(dest != NULL);
        tr_assert(m != NULL);
        dest->size = m->rows;
        dest->x = tr_matdIdx(m, 0, c);
}

tr_vec2d *tr_matdColv2(const tr_matd *m, const size_t c) {
        tr_assert(m != NULL);
        tr_assert(m->rows == 2);
        tr_vec2d *v = (void *)tr_matdIdx(m, 0, c);
        return v;
}

tr_vec3d *tr_matdColv3(const tr_matd *m, const size_t c) {
        tr_assert(m != NULL);
        tr_assert(m->rows == 3);
        tr_vec3d *v = (void *)tr_matdIdx(m, 0, c);
        return v;
}

tr_vec4d *tr_matdColv4(const tr_matd *m, const size_t c) {
        tr_assert(m != NULL);
        tr_assert(m->rows == 4);
        tr_vec4d *v = (void *)tr_matdIdx(m, 0, c);
        return v;
}

void tr_mat2NdRotCols(tr_matd *m, const tr_vecd *stepwise_phase,
                      const double const_phase) {
        tr_assert(m->rows = 2);
        tr_assert((stepwise_phase != NULL) ? stepwise_phase->size == m->rows
                                           : true);
        tr_vec2d *v2;
        for (size_t c = 0; c < m->cols; ++c) {
                v2 = tr_matdColv2(m, c);
                double phase = (stepwise_phase != NULL)
                                   ? stepwise_phase->x[c] + const_phase
                                   : const_phase;

                tr_vec2dRotate(v2, v2, phase);
        }
}

void tr_mat3NdRotColsx(tr_matd *m, const tr_vecd *stepwise_phase,
                       const double const_phase) {
        tr_assert(m->rows = 3);
        tr_assert((stepwise_phase != NULL) ? stepwise_phase->size == m->rows
                                           : true);
        tr_vec3d *v3;
        for (size_t c = 0; c < m->cols; ++c) {
                v3 = tr_matdColv3(m, c);
                double phase = (stepwise_phase != NULL)
                                   ? stepwise_phase->x[c] + const_phase
                                   : const_phase;

                tr_vec3dRotatex(v3, v3, phase);
        }
}

void tr_mat3NdRotColsy(tr_matd *m, const tr_vecd *stepwise_phase,
                       const double const_phase) {
        tr_assert(m->rows = 3);
        tr_assert((stepwise_phase != NULL) ? stepwise_phase->size == m->rows
                                           : true);
        tr_vec3d *v3;
        for (size_t c = 0; c < m->cols; ++c) {
                v3 = tr_matdColv3(m, c);
                double phase = (stepwise_phase != NULL)
                                   ? stepwise_phase->x[c] + const_phase
                                   : const_phase;

                tr_vec3dRotatey(v3, v3, phase);
        }
}

void tr_mat3NdRotColsz(tr_matd *m, const tr_vecd *stepwise_phase,
                       const double const_phase) {
        tr_assert(m->rows = 3);
        tr_assert((stepwise_phase != NULL) ? stepwise_phase->size == m->rows
                                           : true);
        tr_vec3d *v3;
        for (size_t c = 0; c < m->cols; ++c) {
                v3 = tr_matdColv3(m, c);
                double phase = (stepwise_phase != NULL)
                                   ? stepwise_phase->x[c] + const_phase
                                   : const_phase;

                tr_vec3dRotatez(v3, v3, phase);
        }
}

void tr_mat3NCrossCols(tr_matd *dest, const tr_matd *m, const tr_matd *n) {
        tr_assert(m->rows = 3);
        tr_assert(m->cols == n->cols);
        tr_assert((dest->cols * dest->rows) == (m->cols * 3));

        for (size_t c = 0; c < dest->cols; ++c) {
                tr_vec3d *destc = tr_matdColv3(dest, c);
                tr_vec3d *mc = tr_matdColv3(m, c);
                tr_vec3d *nc = tr_matdColv3(n, c);

                tr_vec3dCross(destc, mc, nc);
        }
}

void tr_mat2NCrossCols(tr_vecd *dest, const tr_matd *m, const tr_matd *n) {
        tr_assert(m->rows = 2);
        tr_assert(m->cols == n->cols);
        tr_assert(dest->size == m->cols * 3);

        for (size_t c = 0; c < dest->size; ++c) {
                tr_vec2d *mc = tr_matdColv2(m, c);
                tr_vec2d *nc = tr_matdColv2(n, c);

                dest->x[c] = tr_vec2dCross(mc, nc);
        }
}

void tr_matdColslice(tr_matd *dest, const tr_matd *m, const size_t fromCol,
                     const size_t toCol) {
        tr_assert(dest != NULL);
        tr_assert(m != NULL);
        tr_assert(fromCol < m->cols);
        tr_assert(toCol <= m->cols);

        dest->cols = toCol - fromCol;
        dest->rows = m->rows;

        dest->x = tr_matdIdx(m, 0, fromCol);
}

void tr_matdRowCpy(tr_vecd *dest, const tr_matd *m, const size_t r,
                   size_t stride) {
        tr_assert(dest->size == m->cols / stride);
        tr_assert(stride > 0 && stride <= m->cols);
        tr_assert(dest->size <= m->cols);
        for (size_t i = 0; i < dest->size; i += stride) {
                dest->x[i] = *tr_matdIdx(m, r, i);
        }
}

void tr_matdColCpy(tr_vecd *dest, const tr_matd *m, const size_t c,
                   size_t stride) {
        tr_assert(dest->size == m->rows / stride);
        tr_assert(stride > 0 && stride <= m->rows);
        tr_assert(dest->size <= m->rows);
        for (size_t i = 0; i < dest->size; i += stride) {
                dest->x[i] = *tr_matdIdx(m, i, c);
        }
}

bool tr_matdIsTranspose(tr_matd *m0, tr_matd *m1) {
        if (m0->rows != m1->cols) {
                return false;
        }
        if (m1->rows != m0->cols) {
                return false;
        }

        for (size_t r = 0; r < m0->rows; ++r) {
                for (size_t c = 0; c < m0->cols; ++c) {
                        if (*tr_matdIdx(m0, r, c) != *tr_matdIdx(m1, c, r))
                                return false;
                }
        }
        return true;
}

void tr_matdTranspose(tr_matd *dest, const tr_matd *m) {
        tr_assert(m != NULL);
        tr_assert(dest != NULL);
        // check if enough allocated space
        tr_assert(dest->cols * dest->rows == m->rows * m->cols);

        tr_matd *mT;
        tr_alloc alloc;
        size_t srcRows = m->rows;
        size_t srcCols = m->cols;
        if (dest == m) {
                // allow for inplace transposition by copying memory later
                tr_allocCreate(&alloc, ALLOC_HEAP);
                mT = tr_matdAlloc(&alloc, srcCols, srcRows);
        } else {
                mT = dest;
        }

        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *tr_matdIdx(mT, c, r) = *tr_matdIdx(m, r, c);
                }
        }

        if (dest == m) {
                memcpy(dest->x, mT->x, sizeof(double) * mT->rows * mT->cols);
                tr_matdFree(&alloc, mT);
        }

        dest->cols = srcRows;
        dest->rows = srcCols;
}

void tr_matdOne(tr_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *tr_matdIdx(m, r, c) = 1.0;
                }
        }
}

void tr_matdZero(tr_matd *m) {
        for (size_t r = 0; r < m->rows; ++r) {
                for (size_t c = 0; c < m->cols; ++c) {
                        *tr_matdIdx(m, r, c) = 0.0;
                }
        }
}

void tr_matdIdent(tr_matd *m) {
        tr_assert(m->rows == m->cols);
        for (size_t c = 0; c < m->cols; ++c) {
                for (size_t r = 0; r < m->rows; ++r) {
                        *tr_matdIdx(m, r, c) = (c == r) ? 1.0 : 0.0;
                }
        }
}

void tr_matdScale(tr_matd *dest, tr_matd *m, double a) {
        tr_assert(dest != NULL);
        tr_assert(m != NULL);
        tr_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] * a;
        }
}

void tr_matdIncr(tr_matd *dest, tr_matd *m, double a) {
        tr_assert(dest != NULL);
        tr_assert(m != NULL);
        tr_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] + a;
        }
}

void tr_matdAdd(tr_matd *dest, tr_matd *m, tr_matd *n) {
        tr_assert(dest != NULL);
        tr_assert(m != NULL);
        tr_assert(n != NULL);
        tr_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        tr_assert((n->cols = m->cols) && (n->rows = m->rows));

        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] + n->x[i];
        }
}

void tr_matdScAdd(tr_matd *dest, tr_matd *m, double a, tr_matd *n) {
        tr_assert(dest != NULL);
        tr_assert(m != NULL);
        tr_assert(n != NULL);
        tr_assert((dest->cols = m->cols) && (dest->rows = m->rows));
        tr_assert((n->cols = m->cols) && (n->rows = m->rows));

        for (size_t i = 0; i < m->cols * m->rows; ++i) {
                dest->x[i] = m->x[i] + a * n->x[i];
        }
}

void tr_matdMVMul(tr_vecd *dest, const tr_matd *m, const tr_vecd *v,
                  const double a) {
#ifdef _BLAS
        cblas_dgemv(CblasColMajor, CblasNoTrans, m->rows, m->cols, a, m->x,
                    m->rows, v->x, 1, 0.0, dest->x, 1);
#else
#error "Not implemented!"
#endif
}

void tr_matdMMul(tr_matd *dest, const double alpha, const tr_matd *a,
                 const tr_matd *b) {
#ifdef _BLAS
        cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, a->rows, b->cols,
                    a->cols, alpha, a->x, a->rows, b->x, b->rows, 1.0, dest->x,
                    dest->rows);
#else
#error "Not implemented!"
#endif
}

void tr_matdPrint(tr_matd *m) {
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
                                               *tr_matdIdx(m, m->rows - 1, c));
                                } else {
                                        printf(", %.6e",
                                               *tr_matdIdx(m, m->rows - 1, c));
                                }
                        }

                        printf(" |\n");
                        break;
                }
                // actual print
                for (size_t c = 0; c < m->cols; ++c) {
                        if (c > 5) {
                                printf(", ...");
                                printf(", %.6e", *tr_matdIdx(m, r, c));
                                break;
                        }
                        if (0 == c) {
                                printf("%.6e", *tr_matdIdx(m, r, c));
                        } else {
                                printf(", %.6e", *tr_matdIdx(m, r, c));
                        }
                }
                printf(" |\n");
        }
        printf("<%lu by %lu matrix>\n", m->rows, m->cols);
}
