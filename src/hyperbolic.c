#include <trog/geometry.h>
#include <math.h>

// hyperbolic
// ----------------------------------------------------------------------------

void tr_vecdCosh(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = cosh(v->x[i]);
        }
}

void tr_vec2dCosh(tr_vec2d *v) {
        v->x = cosh(v->x);
        v->y = cosh(v->y);
}

void tr_vec3dCosh(tr_vec3d *v) {
        v->x = cosh(v->x);
        v->y = cosh(v->y);
        v->z = cosh(v->z);
}

void tr_vec4dCosh(tr_vec4d *v) {
        v->a = cosh(v->a);
        v->b = cosh(v->b);
        v->c = cosh(v->c);
        v->d = cosh(v->d);
}

void tr_vecdSinh(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = sinh(v->x[i]);
        }
}

void tr_vec2dSinh(tr_vec2d *v) {
        v->x = sinh(v->x);
        v->y = sinh(v->y);
}

void tr_vec3dSinh(tr_vec3d *v) {
        v->x = sinh(v->x);
        v->y = sinh(v->y);
        v->z = sinh(v->z);
}

void tr_vec4dSinh(tr_vec4d *v) {
        v->a = sinh(v->a);
        v->b = sinh(v->b);
        v->c = sinh(v->c);
        v->d = sinh(v->d);
}

void tr_vecdTanh(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = tanh(v->x[i]);
        }
}

void tr_vec2dTanh(tr_vec2d *v) {
        v->x = tanh(v->x);
        v->y = tanh(v->y);
}

void tr_vec3dTanh(tr_vec3d *v) {
        v->x = tanh(v->x);
        v->y = tanh(v->y);
        v->z = tanh(v->z);
}

void tr_vec4dTanh(tr_vec4d *v) {
        v->a = tanh(v->a);
        v->b = tanh(v->b);
        v->c = tanh(v->c);
        v->d = tanh(v->d);
}

void tr_vecdSech(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = 1.0 / cosh(v->x[i]);
        }
}

void tr_vec2dSech(tr_vec2d *v) {
        v->x = 1.0 / cosh(v->x);
        v->y = 1.0 / cosh(v->y);
}

void tr_vec3dSech(tr_vec3d *v) {
        v->x = 1.0 / cosh(v->x);
        v->y = 1.0 / cosh(v->y);
        v->z = 1.0 / cosh(v->z);
}

void tr_vec4dSech(tr_vec4d *v) {
        v->a = 1.0 / cosh(v->a);
        v->b = 1.0 / cosh(v->b);
        v->c = 1.0 / cosh(v->c);
        v->d = 1.0 / cosh(v->d);
}

void tr_vecdCsech(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = 1.0 / sinh(v->x[i]);
        }
}

void tr_vec2dCsech(tr_vec2d *v) {
        v->x = 1.0 / sinh(v->x);
        v->y = 1.0 / sinh(v->y);
}

void tr_vec3dCsech(tr_vec3d *v) {
        v->x = 1.0 / sinh(v->x);
        v->y = 1.0 / sinh(v->y);
        v->z = 1.0 / sinh(v->z);
}

void tr_vec4dCsech(tr_vec4d *v) {
        v->a = 1.0 / sinh(v->a);
        v->b = 1.0 / sinh(v->b);
        v->c = 1.0 / sinh(v->c);
        v->d = 1.0 / sinh(v->d);
}

// inverse
void tr_vecdArccosh(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = acosh(v->x[i]);
        }
}

void tr_vec2dArccosh(tr_vec2d *v) {
        v->x = acosh(v->x);
        v->y = acosh(v->y);
}

void tr_vec3dArccosh(tr_vec3d *v) {
        v->x = acosh(v->x);
        v->y = acosh(v->y);
        v->z = acosh(v->z);
}

void tr_vec4dArccosh(tr_vec4d *v) {
        v->a = acosh(v->a);
        v->b = acosh(v->b);
        v->c = acosh(v->c);
        v->d = acosh(v->d);
}

void tr_vecdArcsinh(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = asinh(v->x[i]);
        }
}

void tr_vec2dArcsinh(tr_vec2d *v) {
        v->x = asinh(v->x);
        v->y = asinh(v->y);
}

void tr_vec3dArcsinh(tr_vec3d *v) {
        v->x = asinh(v->x);
        v->y = asinh(v->y);
        v->z = asinh(v->z);
}

void tr_vec4dArcsinh(tr_vec4d *v) {
        v->a = asinh(v->a);
        v->b = asinh(v->b);
        v->c = asinh(v->c);
        v->d = asinh(v->d);
}

void tr_vecdArctanh(tr_vecd *v) {
        for (size_t i = 0; i < v->size; ++i) {
                v->x[i] = atanh(v->x[i]);
        }
}

void tr_vec2dArctanh(tr_vec2d *v) {
        v->x = atanh(v->x);
        v->y = atanh(v->y);
}

void tr_vec3dArctanh(tr_vec3d *v) {
        v->x = atanh(v->x);
        v->y = atanh(v->y);
        v->z = atanh(v->z);
}

void tr_vec4dArctanh(tr_vec4d *v) {
        v->a = atanh(v->a);
        v->b = atanh(v->b);
        v->c = atanh(v->c);
        v->d = atanh(v->d);
}
