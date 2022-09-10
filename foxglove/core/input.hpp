#pragma once

#include <math/vector.hpp>

namespace foxglove::core {
    enum KeyboardKey {
        KEY_LSHIFT = 340,
        KEY_LCTRL = 341,
        KEY_LALT = 342,
        KEY_RIGHT = 262,
        KEY_LEFT = 263,
        KEY_DOWN = 264,
        KEY_UP = 265,
        KEY_SPACE = 32,
        KEY_A = 65,
        KEY_B = 66,
        KEY_C = 67,
        KEY_D = 68,
        KEY_E = 69,
        KEY_F = 70,
        KEY_G = 71,
        KEY_H = 72,
        KEY_I = 73,
        KEY_J = 74,
        KEY_K = 75,
        KEY_L = 76,
        KEY_M = 77,
        KEY_N = 78,
        KEY_O = 79,
        KEY_P = 80,
        KEY_Q = 81,
        KEY_R = 82,
        KEY_S = 83,
        KEY_T = 84,
        KEY_U = 85,
        KEY_V = 86,
        KEY_W = 87,
        KEY_X = 88,
        KEY_Y = 89,
        KEY_Z = 90
    };

    enum MouseKey {
        MOUSE_LEFT = 1,
        MOUSE_RIGHT = 2
    };

    struct KeyDownEvent {
        KeyboardKey key;
        explicit KeyDownEvent(int key) : key(static_cast<KeyboardKey>(key)) {}
    };

    struct KeyUpEvent {
        KeyboardKey key;
        explicit KeyUpEvent(int key) : key(static_cast<KeyboardKey>(key)) {}
    };

    struct MouseMoveEvent {
        math::Vec2f new_pos;
        explicit MouseMoveEvent(const math::Vec2f& new_pos) : new_pos(new_pos) {}
    };

    struct MouseDownEvent {
        MouseKey key;
        explicit MouseDownEvent(int key) : key(static_cast<MouseKey>(key)) {}
    };

    struct MouseUpEvent {
        MouseKey key;
        explicit MouseUpEvent(int key) : key(static_cast<MouseKey>(key)) {}
    };
}