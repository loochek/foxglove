#pragma once

namespace foxglove::game {
    struct CameraComponent {
        float fov;
        float aspect_ratio;
        float near_plane;
        float far_plane;

        CameraComponent(float fov = 0.785398f, float aspect_ratio = 16.0f / 9.0f, float near_plane = 0.1f, float far_plane = 100.0f) :
                fov(fov), aspect_ratio(aspect_ratio), near_plane(near_plane), far_plane(far_plane) {}
    };
}