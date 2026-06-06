#include <trog/geometry.h>
#include <math.h>

void tr_vecdCos(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = cos(src->x[i]);
        }
}

void tr_vec2dCos(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = cos(src->x);
        dest->y = cos(src->y);
}

void tr_vec3dCos(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = cos(src->x);
        dest->y = cos(src->y);
        dest->z = cos(src->z);
}

void tr_vec4dCos(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = cos(src->a);
        dest->b = cos(src->b);
        dest->c = cos(src->c);
        dest->d = cos(src->d);
}

void tr_vecdSin(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = sin(src->x[i]);
        }
}

void tr_vec2dSin(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = sin(src->x);
        dest->y = sin(src->y);
}

void tr_vec3dSin(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = sin(src->x);
        dest->y = sin(src->y);
        dest->z = sin(src->z);
}

void tr_vec4dSin(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = sin(src->a);
        dest->b = sin(src->b);
        dest->c = sin(src->c);
        dest->d = sin(src->d);
}

void tr_vecdTan(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = tan(src->x[i]);
        }
}

void tr_vec2dTan(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = tan(src->x);
        dest->y = tan(src->y);
}

void tr_vec3dTan(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = tan(src->x);
        dest->y = tan(src->y);
        dest->z = tan(src->z);
}

void tr_vec4dTan(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = tan(src->a);
        dest->b = tan(src->b);
        dest->c = tan(src->c);
        dest->d = tan(src->d);
}

void tr_vecdSec(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = 1.0 / cos(src->x[i]);
        }
}

void tr_vec2dSec(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = 1.0 / cos(src->x);
        dest->y = 1.0 / cos(src->y);
}

void tr_vec3dSec(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = 1.0 / cos(src->x);
        dest->y = 1.0 / cos(src->y);
        dest->z = 1.0 / cos(src->z);
}

void tr_vec4dSec(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = 1.0 / cos(src->a);
        dest->b = 1.0 / cos(src->b);
        dest->c = 1.0 / cos(src->c);
        dest->d = 1.0 / cos(src->d);
}

void tr_vecdCsec(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = 1.0 / sin(src->x[i]);
        }
}

void tr_vec2dCsec(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = 1.0 / sin(src->x);
        dest->y = 1.0 / sin(src->y);
}

void tr_vec3dCsec(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = 1.0 / sin(src->x);
        dest->y = 1.0 / sin(src->y);
        dest->z = 1.0 / sin(src->z);
}

void tr_vec4dCsec(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = 1.0 / sin(src->a);
        dest->b = 1.0 / sin(src->b);
        dest->c = 1.0 / sin(src->c);
        dest->d = 1.0 / sin(src->d);
}

// Inverse
void tr_vecdArccos(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = acos(src->x[i]);
        }
}

void tr_vec2dArccos(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = acos(src->x);
        dest->y = acos(src->y);
}

void tr_vec3dArccos(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = acos(src->x);
        dest->y = acos(src->y);
        dest->z = acos(src->z);
}

void tr_vec4dArccos(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = acos(src->a);
        dest->b = acos(src->b);
        dest->c = acos(src->c);
        dest->d = acos(src->d);
}

void tr_vecdArcsin(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = asin(src->x[i]);
        }
}

void tr_vec2dArcsin(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = asin(src->x);
        dest->y = asin(src->y);
}

void tr_vec3dArcsin(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = asin(src->x);
        dest->y = asin(src->y);
        dest->z = asin(src->z);
}

void tr_vec4dArcsin(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = asin(src->a);
        dest->b = asin(src->b);
        dest->c = asin(src->c);
        dest->d = asin(src->d);
}

void tr_vecdArctan(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = atan(dest->x[i]);
        }
}

void tr_vec2dArctan(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = atan(src->x);
        dest->y = atan(src->y);
}

void tr_vec3dArctan(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = atan(src->x);
        dest->y = atan(src->y);
        dest->z = atan(src->z);
}

void tr_vec4dArctan(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = atan(src->a);
        dest->b = atan(src->b);
        dest->c = atan(src->c);
        dest->d = atan(src->d);
}
