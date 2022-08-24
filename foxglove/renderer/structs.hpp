#pragma once

#include <math/vector.hpp>

namespace foxglove::renderer {
    struct PackedVertex {
        math::Vec3f position;
        math::Vec3f normal;
        math::Vec2f uv;
    };
}
