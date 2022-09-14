#include "render_system.hpp"

#include <game/components/transform.hpp>
#include <game/components/model_renderer.hpp>
#include <game/components/camera.hpp>

#include <math/3d_stuff.hpp>
#include <renderer/renderer.hpp>

namespace foxglove::game  {
    RenderSystem::RenderSystem(ecs::World *world) : world_(world) {
        renderer_ = Engine::Instance()->renderer_;
        Engine::Instance()->events_->Subscribe<core::GameRenderEvent>(this);
        Engine::Instance()->events_->Subscribe<TransformChangedEvent>(this);

        // view_matrix_ is an identity matrix by default
        // default proj:
        math::Vec2i window_size = Engine::Instance()->window_->GetSize();
        proj_matrix_ = math::PerspectiveProj(70.0f * 180.0f / M_PI , window_size.x / window_size.y, 0.1f, 100.0f);
    }

    void RenderSystem::OnEvent(const core::GameRenderEvent& event) {
        renderer::DrawList draw_list;

        world_->ForEach<TransformComponent, ModelRendererComponent>([&](ecs::Entity entity) mutable {
            auto& transform = world_->GetComponent<TransformComponent>(entity);
            auto& model_renderer = world_->GetComponent<ModelRendererComponent>(entity);

            math::Mat4f model_matrix = math::Translate(transform.translation) *
                    math::Rotate(transform.rotation) * math::Scale(transform.scale);

            renderer::ShaderParamList shader_params;
            shader_params.SetParam("proj", proj_matrix_);
            shader_params.SetParam("view", view_matrix_);
            shader_params.SetParam("model", model_matrix);

            model_renderer.model->Draw(draw_list, shader_params);
        });

        renderer_->Clear();
        renderer_->DrawList(draw_list);
        renderer_->SwapBuffers();
    }

    void RenderSystem::OnEvent(const TransformChangedEvent &event) {
        if (event.entity == controlled_camera_) {
            RecalculateViewMatrix();
        }
    }

    void RenderSystem::AssignCamera(ecs::Entity camera) {
        FXG_ASSERT(world_->HasComponent<TransformComponent>(camera));
        FXG_ASSERT(world_->HasComponent<CameraComponent>(camera));

        controlled_camera_ = camera;
        camera_transform_ = &world_->GetComponent<TransformComponent>(camera);
        camera_camera_ = &world_->GetComponent<CameraComponent>(camera);

        RecalculateViewMatrix();
        RecalculateProjMatrix();
    }

    void RenderSystem::RecalculateViewMatrix() {
        view_matrix_ = math::LookTo(camera_transform_->translation,
                                    math::Direction(camera_transform_->rotation),
                                    math::Vec3f(0.0f, 1.0f, 0.0f));
    }

    void RenderSystem::RecalculateProjMatrix() {
        proj_matrix_ = math::PerspectiveProj(camera_camera_->fov,
                                             camera_camera_->aspect_ratio,
                                             camera_camera_->near_plane,
                                             camera_camera_->far_plane);
    }
}