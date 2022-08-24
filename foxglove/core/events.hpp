#pragma once

#include <math/vector.hpp>

/**
 * Core engine events
 */

namespace foxglove::core {
    struct ShutdownInitiatedEvent {};

    // Window events
    struct WindowResizeEvent {
        WindowResizeEvent(const math::Vec2i& new_size) : new_size_(new_size) {}
        math::Vec2i new_size_;
    };

    struct WindowCloseEvent {};

    // Main loop phases
    struct MainLoopNativePollEvent {};
    struct MainLoopPreUpdateEvent {};
    struct MainLoopUpdateEvent {};
    struct MainLoopPostUpdateEvent {};
    struct MainLoopRenderEvent {};
};
