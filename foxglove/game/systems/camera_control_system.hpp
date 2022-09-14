#pragma once

#include <core/event_bus.hpp>
#include <core/input.hpp>
#include <ecs/world.hpp>

namespace foxglove::game {
    class TransformComponent;

    class CameraControlSystem : public core::IEventsListener<core::KeyDownEvent, core::KeyUpEvent,core::MouseMoveEvent, core::GameUpdateEvent> {
    public:
        explicit CameraControlSystem(ecs::World* world);

        void OnEvent(const core::KeyDownEvent& event) override;
        void OnEvent(const core::KeyUpEvent& event) override;
        void OnEvent(const core::MouseMoveEvent& event) override;
        void OnEvent(const core::GameUpdateEvent& event) override;

        void AssignCamera(ecs::Entity camera);

    private:
        ecs::World* world_;

        ecs::Entity controlled_camera_;
        TransformComponent* camera_transform_;

        std::bitset<4> pressed_keys_;
        math::Vec2f prev_mouse_pos_;
        math::Vec2f new_mouse_pos_;

        enum class MouseState {
            Initial,
            Moved,
            NotMoved
        };

        MouseState mouse_state_;
    };
}