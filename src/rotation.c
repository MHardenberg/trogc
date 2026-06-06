#include <trog/geometry.h>
#include <math.h>

void tr_vec3dGetAlignRotation(tr_matd *R, const tr_vec3d *m,
                              const tr_vec3d *n) {
        tr_vec3d axis;
        tr_vec3d z = {.x = 0, .y = 0, .z = 1};

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

        const double inner = tr_vec3dDot(&reflection, &reflection);

        tr_vec3dOuter(R, &reflection, &reflection);
        tr_matdScale(R, R, 2. / inner);

        *tr_matdIdx(R, 0, 0) -= -1;
        *tr_matdIdx(R, 1, 1) -= -1;
        *tr_matdIdx(R, 2, 2) -= -1;
}
