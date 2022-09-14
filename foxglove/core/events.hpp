#pragma once

#include <math/vector.hpp>

/**
 * Core engine events
 */

namespace foxglove::core {
    struct ShutdownInitiatedEvent {};

    // Window events
    struct WindowResizeEvent {
        math::Vec2i new_size_;
        explicit WindowResizeEvent(const math::Vec2i& new_size) : new_size_(new_size) {}
    };

    struct WindowCloseEvent {};

    // Main loop phases
    struct GameNativePollEvent {};
    struct GamePreUpdateEvent {};
    struct GameUpdateEvent {
        float time_delta;

        explicit GameUpdateEvent(float time_delta) : time_delta(time_delta) {}
    };
    struct GamePostUpdateEvent {};
    struct GameRenderEvent {};
};
