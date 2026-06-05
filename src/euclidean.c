#include <trog/geometry.h>
#include <math.h>

void tr_vecdCos(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = cos(v->x[i]);
        }
}

void tr_vec2dCos(tr_vec2d *v) {
        v->x = cos(v->x);
        v->y = cos(v->y);
}

void tr_vec3dCos(tr_vec3d *v) {
        v->x = cos(v->x);
        v->y = cos(v->y);
        v->z = cos(v->z);
}

void tr_vec4dCos(tr_vec4d *v) {
        v->a = cos(v->a);
        v->b = cos(v->b);
        v->c = cos(v->c);
        v->d = cos(v->d);
}

void tr_vecdSin(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = sin(v->x[i]);
        }
}

void tr_vec2dSin(tr_vec2d *v) {
        v->x = sin(v->x);
        v->y = sin(v->y);
}

void tr_vec3dSin(tr_vec3d *v) {
        v->x = sin(v->x);
        v->y = sin(v->y);
        v->z = sin(v->z);
}

void tr_vec4dSin(tr_vec4d *v) {
        v->a = sin(v->a);
        v->b = sin(v->b);
        v->c = sin(v->c);
        v->d = sin(v->d);
}

void tr_vecdTan(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = tan(v->x[i]);
        }
}

void tr_vec2dTan(tr_vec2d *v) {
        v->x = tan(v->x);
        v->y = tan(v->y);
}

void tr_vec3dTan(tr_vec3d *v) {
        v->x = tan(v->x);
        v->y = tan(v->y);
        v->z = tan(v->z);
}

void tr_vec4dTan(tr_vec4d *v) {
        v->a = tan(v->a);
        v->b = tan(v->b);
        v->c = tan(v->c);
        v->d = tan(v->d);
}

void tr_vecdSec(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = 1.0 / cos(v->x[i]);
        }
}

void tr_vec2dSec(tr_vec2d *v) {
        v->x = 1.0 / cos(v->x);
        v->y = 1.0 / cos(v->y);
}

void tr_vec3dSec(tr_vec3d *v) {
        v->x = 1.0 / cos(v->x);
        v->y = 1.0 / cos(v->y);
        v->z = 1.0 / cos(v->z);
}

void tr_vec4dSec(tr_vec4d *v) {
        v->a = 1.0 / cos(v->a);
        v->b = 1.0 / cos(v->b);
        v->c = 1.0 / cos(v->c);
        v->d = 1.0 / cos(v->d);
}

void tr_vecdCsec(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = 1.0 / sin(v->x[i]);
        }
}

void tr_vec2dCsec(tr_vec2d *v) {
        v->x = 1.0 / sin(v->x);
        v->y = 1.0 / sin(v->y);
}

void tr_vec3dCsec(tr_vec3d *v) {
        v->x = 1.0 / sin(v->x);
        v->y = 1.0 / sin(v->y);
        v->z = 1.0 / sin(v->z);
}

void tr_vec4dCsec(tr_vec4d *v) {
        v->a = 1.0 / sin(v->a);
        v->b = 1.0 / sin(v->b);
        v->c = 1.0 / sin(v->c);
        v->d = 1.0 / sin(v->d);
}

// Inverse
void tr_vecdArccos(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = acos(v->x[i]);
        }
}

void tr_vec2dArccos(tr_vec2d *v) {
        v->x = acos(v->x);
        v->y = acos(v->y);
}

void tr_vec3dArccos(tr_vec3d *v) {
        v->x = acos(v->x);
        v->y = acos(v->y);
        v->z = acos(v->z);
}

void tr_vec4dArccos(tr_vec4d *v) {
        v->a = acos(v->a);
        v->b = acos(v->b);
        v->c = acos(v->c);
        v->d = acos(v->d);
}

void tr_vecdArcsin(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = asin(v->x[i]);
        }
}

void tr_vec2dArcsin(tr_vec2d *v) {
        v->x = asin(v->x);
        v->y = asin(v->y);
}

void tr_vec3dArcsin(tr_vec3d *v) {
        v->x = asin(v->x);
        v->y = asin(v->y);
        v->z = asin(v->z);
}

void tr_vec4dArcsin(tr_vec4d *v) {
        v->a = asin(v->a);
        v->b = asin(v->b);
        v->c = asin(v->c);
        v->d = asin(v->d);
}

void tr_vecdArctan(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = atan(v->x[i]);
        }
}

void tr_vec2dArctan(tr_vec2d *v) {
        v->x = atan(v->x);
        v->y = atan(v->y);
}

void tr_vec3dArctan(tr_vec3d *v) {
        v->x = atan(v->x);
        v->y = atan(v->y);
        v->z = atan(v->z);
}

void tr_vec4dArctan(tr_vec4d *v) {
        v->a = atan(v->a);
        v->b = atan(v->b);
        v->c = atan(v->c);
        v->d = atan(v->d);
}
