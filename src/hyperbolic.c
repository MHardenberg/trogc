#include "trogAssert.h"
#include <trog/geometry.h>
#include <math.h>

// hyperbolic
// ----------------------------------------------------------------------------

void tr_vecdCosh(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = cosh(src->x[i]);
        }
}

void tr_vec2dCosh(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = cosh(src->x);
        dest->y = cosh(src->y);
}

void tr_vec3dCosh(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = cosh(src->x);
        dest->y = cosh(src->y);
        dest->z = cosh(src->z);
}

void tr_vec4dCosh(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = cosh(src->a);
        dest->b = cosh(src->b);
        dest->c = cosh(src->c);
        dest->d = cosh(src->d);
}

void tr_vecdSinh(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = sinh(src->x[i]);
        }
}

void tr_vec2dSinh(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = sinh(src->x);
        dest->y = sinh(src->y);
}

void tr_vec3dSinh(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = sinh(src->x);
        dest->y = sinh(src->y);
        dest->z = sinh(src->z);
}

void tr_vec4dSinh(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = sinh(src->a);
        dest->b = sinh(src->b);
        dest->c = sinh(src->c);
        dest->d = sinh(src->d);
}

void tr_vecdTanh(tr_vecd *dest, const tr_vecd *src) {
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = tanh(src->x[i]);
        }
}

void tr_vec2dTanh(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = tanh(src->x);
        dest->y = tanh(src->y);
}

void tr_vec3dTanh(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = tanh(src->x);
        dest->y = tanh(src->y);
        dest->z = tanh(src->z);
}

void tr_vec4dTanh(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = tanh(src->a);
        dest->b = tanh(src->b);
        dest->c = tanh(src->c);
        dest->d = tanh(src->d);
}

void tr_vecdSech(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = 1.0 / cosh(src->x[i]);
        }
}

void tr_vec2dSech(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = 1.0 / cosh(src->x);
        dest->y = 1.0 / cosh(src->y);
}

void tr_vec3dSech(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = 1.0 / cosh(src->x);
        dest->y = 1.0 / cosh(src->y);
        dest->z = 1.0 / cosh(src->z);
}

void tr_vec4dSech(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = 1.0 / cosh(src->a);
        dest->b = 1.0 / cosh(src->b);
        dest->c = 1.0 / cosh(src->c);
        dest->d = 1.0 / cosh(src->d);
}

void tr_vecdCsech(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = 1.0 / sinh(src->x[i]);
        }
}

void tr_vec2dCsech(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = 1.0 / sinh(src->x);
        dest->y = 1.0 / sinh(src->y);
}

void tr_vec3dCsech(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = 1.0 / sinh(src->x);
        dest->y = 1.0 / sinh(src->y);
        dest->z = 1.0 / sinh(src->z);
}

void tr_vec4dCsech(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = 1.0 / sinh(src->a);
        dest->b = 1.0 / sinh(src->b);
        dest->c = 1.0 / sinh(src->c);
        dest->d = 1.0 / sinh(src->d);
}

// inverse
void tr_vecdArccosh(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = acosh(src->x[i]);
        }
}

void tr_vec2dArccosh(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = acosh(src->x);
        dest->y = acosh(src->y);
}

void tr_vec3dArccosh(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = acosh(src->x);
        dest->y = acosh(src->y);
        dest->z = acosh(src->z);
}

void tr_vec4dArccosh(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = acosh(src->a);
        dest->b = acosh(src->b);
        dest->c = acosh(src->c);
        dest->d = acosh(src->d);
}

void tr_vecdArcsinh(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = asinh(src->x[i]);
        }
}

void tr_vec2dArcsinh(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = asinh(src->x);
        dest->y = asinh(src->y);
}

void tr_vec3dArcsinh(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = asinh(src->x);
        dest->y = asinh(src->y);
        dest->z = asinh(src->z);
}

void tr_vec4dArcsinh(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = asinh(src->a);
        dest->b = asinh(src->b);
        dest->c = asinh(src->c);
        dest->d = asinh(src->d);
}

void tr_vecdArctanh(tr_vecd *dest, const tr_vecd *src) {
        tr_assert(dest->size == src->size);
        for (size_t i = 0; i < src->size; ++i) {
                dest->x[i] = atanh(src->x[i]);
        }
}

void tr_vec2dArctanh(tr_vec2d *dest, const tr_vec2d *src) {
        dest->x = atanh(src->x);
        dest->y = atanh(src->y);
}

void tr_vec3dArctanh(tr_vec3d *dest, const tr_vec3d *src) {
        dest->x = atanh(src->x);
        dest->y = atanh(src->y);
        dest->z = atanh(src->z);
}

void tr_vec4dArctanh(tr_vec4d *dest, const tr_vec4d *src) {
        dest->a = atanh(src->a);
        dest->b = atanh(src->b);
        dest->c = atanh(src->c);
        dest->d = atanh(src->d);
}
