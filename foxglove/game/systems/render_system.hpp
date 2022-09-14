#pragma once

#include <math/matrix.hpp>
#include <engine.hpp>
#include <core/event_bus.hpp>
#include <ecs/world.hpp>
#include <game/components/transform.hpp>

namespace foxglove::renderer {
    class Renderer;
}

namespace foxglove::game {
    class CameraComponent;

    class RenderSystem : public core::IEventsListener<core::GameRenderEvent, TransformChangedEvent> {
    public:
        explicit RenderSystem(ecs::World *world);

        void OnEvent(const core::GameRenderEvent& event) override;
        void OnEvent(const TransformChangedEvent& event) override;

        void AssignCamera(ecs::Entity camera);

    private:
        void RecalculateViewMatrix();
        void RecalculateProjMatrix();

    private:
        ecs::World* world_;
        renderer::Renderer* renderer_;

        // Camera

        ecs::Entity controlled_camera_;
        TransformComponent* camera_transform_;
        CameraComponent* camera_camera_;

        math::Mat4f view_matrix_;
        math::Mat4f proj_matrix_;
    };
}