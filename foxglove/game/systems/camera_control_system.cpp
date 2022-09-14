#include "camera_control_system.hpp"
#include <math/3d_stuff.hpp>
#include <game/components/transform.hpp>

namespace foxglove::game {
    constexpr float ALMOST_PI2 = M_PI_2 - 0.017f;

    CameraControlSystem::CameraControlSystem(ecs::World *world) :
            world_(world),
            controlled_camera_(ecs::NullEntity),
            camera_transform_(nullptr),
            mouse_state_(MouseState::Initial) {
        Engine::Instance()->events_->Subscribe<core::KeyDownEvent>(this);
        Engine::Instance()->events_->Subscribe<core::KeyUpEvent>(this);
        Engine::Instance()->events_->Subscribe<core::MouseMoveEvent>(this);
        Engine::Instance()->events_->Subscribe<core::GameUpdateEvent>(this);
    }

    void CameraControlSystem::OnEvent(const core::KeyDownEvent &event) {
        switch (event.key) {
            case core::KEY_W:
                pressed_keys_.set(0);
                break;

            case core::KEY_S:
                pressed_keys_.set(1);
                break;

            case core::KEY_A:
                pressed_keys_.set(2);
                break;

            case core::KEY_D:
                pressed_keys_.set(3);
                break;

            default:
                break;
        }
    }

    void CameraControlSystem::OnEvent(const core::KeyUpEvent &event) {
        switch (event.key) {
            case core::KEY_W:
                pressed_keys_.reset(0);
                break;

            case core::KEY_S:
                pressed_keys_.reset(1);
                break;

            case core::KEY_A:
                pressed_keys_.reset(2);
                break;

            case core::KEY_D:
                pressed_keys_.reset(3);
                break;

            default:
                break;
        }
    }

    void CameraControlSystem::OnEvent(const core::MouseMoveEvent &event) {
        prev_mouse_pos_ = new_mouse_pos_;
        new_mouse_pos_ = event.new_pos;

        if (mouse_state_ == MouseState::Initial) {
            mouse_state_ = MouseState::NotMoved;
            return;
        }

        // Not reached if prev pos is not yet present
        mouse_state_ = MouseState::Moved;
    }

    void CameraControlSystem::OnEvent(const core::GameUpdateEvent &event) {
        FXG_ASSERT(controlled_camera_ != ecs::NullEntity);

        math::Vec3f camera_dir = math::Direction(camera_transform_->rotation);
        // Not really up (but the direction and up vectors define a plane parallel to the Y axis)
        math::Vec3f camera_up = math::Vec3f(0.0f, 1.0f, 0.0f);

        float camera_speed = 1.0f;
        float multiplier = camera_speed * event.time_delta;

        if (pressed_keys_.test(0)) {
            camera_transform_->translation += camera_dir * multiplier;
        }

        if (pressed_keys_.test(1)) {
            camera_transform_->translation -= camera_dir * multiplier;
        }

        // Right vector = vector_mul(dir, up)

        if (pressed_keys_.test(2)) {
            camera_transform_->translation -= (camera_dir ^ camera_up).Normalized() * multiplier;
        }

        if (pressed_keys_.test(3)) {
            camera_transform_->translation += (camera_dir ^ camera_up).Normalized() * multiplier;
        }

        if (mouse_state_ == MouseState::Moved) {
            math::Vec2f offset = new_mouse_pos_ - prev_mouse_pos_;

            float sensitivity = 0.1f;
            offset *= sensitivity * event.time_delta;

            camera_transform_->rotation.x -= offset.y;
            camera_transform_->rotation.y += offset.x;

            if (camera_transform_->rotation.x > ALMOST_PI2) {
                camera_transform_->rotation.x = ALMOST_PI2;
            }

            if (camera_transform_->rotation.x < -ALMOST_PI2) {
                camera_transform_->rotation.x = -ALMOST_PI2;
            }
        }

        if (pressed_keys_.any() || mouse_state_ == MouseState::Moved) {
            Engine::Instance()->events_->Emit(TransformChangedEvent(controlled_camera_));
        }

        if (mouse_state_ == MouseState::Moved) {
            mouse_state_ = MouseState::NotMoved;
        }
    }

    void CameraControlSystem::AssignCamera(ecs::Entity camera) {
        FXG_ASSERT(world_->HasComponent<TransformComponent>(camera));

        controlled_camera_ = camera;
        camera_transform_ = &world_->GetComponent<TransformComponent>(camera);
    }
}