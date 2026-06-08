#include "trog/linalg.h"
#include "trogAssert.h"
#include <trog/geometry.h>

void tr_vec3dHouseholderRotation(tr_matd *R, tr_matd *Rinv, const tr_vec3d *m,
                                 const tr_vec3d *n) {
        tr_assert(R != NULL);
        tr_assert(Rinv != NULL);
        tr_assert(m != NULL);
        tr_assert(n != NULL);
        // See:
        // https://math.stackexchange.com/questions/180418/calculate-rotation-matrix-to-align-vector-a-to-vector-b-in-3d/476311#476311

        tr_vec3d axis;
        tr_vec3d z = {.x = 0, .y = 0, .z = 1};

        // normalised rotation axis
        tr_vec3dCross(&axis, m, n);
        tr_vec3dScale(&axis, 1. / tr_vec3dNorm(&axis), &axis);

        // align rotation and z axis
        double sign = tr_vec3dDot(&axis, &z);
        if (sign < 0) {
                tr_vec3dScale(&axis, -1, &axis);
        }

        // Householder reflection
        tr_vec3d reflection;
        tr_vec3dAdd(&reflection, &axis, &z);

        // denominator
        const double denom = tr_vec3dDot(&reflection, &reflection);

        // numerator
        tr_vec3dOuter(R, &reflection, &reflection);

        tr_matdScale(R, R, 2. / denom);

        *tr_matdIdx(R, 0, 0) -= 1;
        *tr_matdIdx(R, 1, 1) -= 1;
        *tr_matdIdx(R, 2, 2) -= 1;

        // invert by transposition
        tr_matdTranspose(Rinv, R);
}

void tr_vec3dRotateztox(tr_matd *R, tr_matd *Rinv, const tr_vec3d *p,
                        const tr_vec3d *q) {
        tr_assert(R != NULL);
        tr_assert(Rinv != NULL);
        tr_assert(p != NULL);
        tr_assert(q != NULL);

        tr_vec3d pq;
        tr_vec3dDiff(&pq, q, p);
        const double segmentLen = tr_vec3dNorm(&pq);

        double costheta = 1;
        double sintheta = 0;

        if (segmentLen > 0) {
                costheta = pq.x / segmentLen;
                sintheta = pq.y / segmentLen;

                *tr_matdIdx(R, 0, 0) = costheta;
                *tr_matdIdx(R, 0, 1) = sintheta;
                *tr_matdIdx(R, 1, 0) = -sintheta;
                *tr_matdIdx(R, 1, 1) = costheta;
                *tr_matdIdx(R, 2, 2) = 1.0;

                tr_matdTranspose(Rinv, R);
        }
}
