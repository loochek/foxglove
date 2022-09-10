#pragma once

#include <utils/common.hpp>

namespace foxglove::ecs {
    using Entity = std::uint32_t;
    using ComponentID = std::uint32_t;

    constexpr int MAX_COMPONENTS = 32;
};
