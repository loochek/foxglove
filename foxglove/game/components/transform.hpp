#pragma once

#include <math/vector.hpp>
#include <ecs/ecs.hpp>

namespace foxglove::game {
    struct TransformChangedEvent {
        ecs::Entity entity;

        explicit TransformChangedEvent(ecs::Entity entity) : entity(entity) {}
    };

    struct TransformComponent {
        math::Vec3f translation;
        math::Vec3f rotation;
        math::Vec3f scale;

        explicit TransformComponent(math::Vec3f translation = math::Vec3f(0.0f, 0.0f, 0.0f),
                                    math::Vec3f rotation = math::Vec3f(0.0f, 0.0f, 0.0f),
                                    math::Vec3f scale = math::Vec3f(1.0f, 1.0f, 1.0f)) :
            translation(translation), rotation(rotation), scale(scale) {}
    };
}