#pragma once

#include <cmath>
#include <math/vector.hpp>
#include <math/matrix.hpp>

namespace foxglove::math {
    Mat4f Translate(const Vec3f& offset) {
        return Mat4f({
            { 1, 0, 0, offset.x },
            { 0, 1, 0, offset.y },
            { 0, 0, 1, offset.z }, 
            { 0, 0, 0, 1 }
        });
    }

    Mat4f Scale(const Vec3f& scale) {
        return Mat4f({
            { scale.x, 0,       0,       0 },
            { 0,       scale.y, 0,       0 },
            { 0,       0,       scale.z, 0 }, 
            { 0,       0,       0,       1 }
        });
    }

    Mat4f Rotate(const Vec3f& axis, float angle) {
        float c = cosf(angle);
        float s = sinf(angle);

        return Mat4f({
            { c + axis.x * axis.x * (1 - c)         , axis.x * axis.y * (1 - c) - axis.z * s, axis.x * axis.z * (1 - c) + axis.y * s, 0 },
            { axis.y * axis.x * (1 - c) + axis.z * s, c + axis.y * axis.y * (1 - c),          axis.y * axis.z * (1 - c) - axis.x * s, 0 },
            { axis.z * axis.x * (1 - c) - axis.y * s, axis.z * axis.y * (1 - c) - axis.x * s, c + axis.z * axis.z * (1 - c),          0 },
            { 0,                                      0,                                      0,                                      1 }
        });
    }
}
