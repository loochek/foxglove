#pragma once

#include <cmath>
#include <math/vector.hpp>
#include <math/matrix.hpp>

namespace foxglove::math {
    inline Mat4f Translate(const Vec3f& offset) {
        return Mat4f({
            { 1, 0, 0, offset.x },
            { 0, 1, 0, offset.y },
            { 0, 0, 1, offset.z }, 
            { 0, 0, 0, 1 }
        });
    }

    inline Mat4f Scale(const Vec3f& scale) {
        return Mat4f({
            { scale.x, 0,       0,       0 },
            { 0,       scale.y, 0,       0 },
            { 0,       0,       scale.z, 0 }, 
            { 0,       0,       0,       1 }
        });
    }

    inline Mat4f Rotate(const Vec3f& axis_unnorm, float angle) {
        Vec3f axis = axis_unnorm.Normalized();
        float c = cosf(angle);
        float s = sinf(angle);

        return Mat4f({
            { c + axis.x * axis.x * (1 - c)         , axis.x * axis.y * (1 - c) - axis.z * s, axis.x * axis.z * (1 - c) + axis.y * s, 0 },
            { axis.y * axis.x * (1 - c) + axis.z * s, c + axis.y * axis.y * (1 - c),          axis.y * axis.z * (1 - c) - axis.x * s, 0 },
            { axis.z * axis.x * (1 - c) - axis.y * s, axis.z * axis.y * (1 - c) + axis.x * s, c + axis.z * axis.z * (1 - c),          0 },
            { 0,                                      0,                                      0,                                      1 }
        });
    }

    inline Mat4f Rotate(const Vec3f& euler_angles) {
        return math::Rotate(math::Vec3f(0.0f, 0.0f, 1.0f), euler_angles.z) *
               math::Rotate(math::Vec3f(0.0f, 1.0f, 0.0f), euler_angles.y) *
               math::Rotate(math::Vec3f(1.0f, 0.0f, 0.0f), euler_angles.x);
    }

    inline Mat4f PerspectiveProj(float fov, float ratio, float near, float far) {
        float half_fov_tan = tanf(fov / 2.0f);
        float width_half = half_fov_tan * near;
        float height_half = width_half / ratio;

        return Mat4f({{ near / width_half, 0.0f, 0.0f, 0.0f },
                      { 0.0f, near / height_half, 0.0f, 0.0f },
                      { 0.0f, 0.0f, -(far + near) / (far - near), -2.0f * far * near / (far - near) },
                      { 0.0f, 0.0f,  -1.0f, 0.0f } });
    }
}
