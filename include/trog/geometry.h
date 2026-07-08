#ifndef _GEOMETRY
#define _GEOMETRY

#include <trog/linalg.h>

#ifdef __cplusplus
extern "C" {
#endif

// euclidean
// ----------------------------------------------------------------------------
void tr_vecdCos(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dCos(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dCos(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dCos(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdSin(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dSin(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dSin(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dSin(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdTan(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dTan(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dTan(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dTan(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdSec(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dSec(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dSec(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dSec(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdCsec(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dCsec(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dCsec(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dCsec(tr_vec4d *dest, const tr_vec4d *v);

// Inverse
void tr_vecdArccos(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dArccos(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dArccos(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dArccos(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdArcsin(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dArcsin(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dArcsin(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dArcsin(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdArctan(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dArctan(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dArctan(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dArctan(tr_vec4d *dest, const tr_vec4d *v);

// hyperbolic
// ----------------------------------------------------------------------------

void tr_vecdCosh(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dCosh(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dCosh(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dCosh(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdSinh(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dSinh(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dSinh(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dSinh(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdTanh(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dTanh(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dTanh(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dTanh(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdSech(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dSech(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dSech(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dSech(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdCsech(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dCsech(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dCsech(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dCsech(tr_vec4d *dest, const tr_vec4d *v);

// inverse
void tr_vecdArccosh(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dArccosh(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dArccosh(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dArccosh(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdArcsinh(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dArcsinh(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dArcsinh(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dArcsinh(tr_vec4d *dest, const tr_vec4d *v);

void tr_vecdArctanh(tr_vecd *dest, const tr_vecd *v);
void tr_vec2dArctanh(tr_vec2d *dest, const tr_vec2d *v);
void tr_vec3dArctanh(tr_vec3d *dest, const tr_vec3d *v);
void tr_vec4dArctanh(tr_vec4d *dest, const tr_vec4d *v);

// rotations
void tr_vec3dHouseholderRotation(tr_matd *R, tr_matd *Rinv, const tr_vec3d *m,
                                 const tr_vec3d *n);

void tr_vec3dRotateztox(tr_matd *R, tr_matd *Rinv, const tr_vec3d *p,
                        const tr_vec3d *q);

// Grid
/* TO BE ADDED
void tr_grid_spawn(tr_alloc *alloc, const double width,
                         const double height, const double depth,
                         const double grid_res) {
        const size_t width_points = round(width / grid_res);
        const size_t height_points = round(height / grid_res);
        const size_t depth_points = round(depth / grid_res);

        tr_tens3d *gridx =
            tr_tens3dAlloc(alloc, width_points, height_points, depth_points);
        tr_tens3d *gridy = tr_tens3dAllocLike(alloc, gridx);
        tr_tens3d *gridz = tr_tens3dAllocLike(alloc, gridx);

        for (size_t x = 0; x < width_points; ++x) {
                for (size_t y = 0; y < height_points; ++y) {
                        for (size_t z = 0; z < depth_points; ++z) {
                                *tr_tens3dIdx(gridx, x, y, z) = x * grid_res;
                                *tr_tens3dIdx(gridy, x, y, z) = y * grid_res;
                                *tr_tens3dIdx(gridz, x, y, z) = z * grid_res;
                        }
                }
        }
}

*/

#ifdef __cplusplus
}
#endif

#endif // _GEOMETRY
