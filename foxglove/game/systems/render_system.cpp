#include "render_system.hpp"

#include <game/components/transform.hpp>
#include <game/components/model_renderer.hpp>

#include <math/3d_stuff.hpp>
#include <renderer/renderer.hpp>
#include <renderer/draw_list.hpp>

namespace foxglove::game  {
    RenderSystem::RenderSystem(ecs::World *world) : world_(world) {
        renderer_ = Engine::Instance()->renderer_;
        Engine::Instance()->events_->Subscribe<core::MainLoopRenderEvent>(this);
    }

    void RenderSystem::OnEvent(const core::MainLoopRenderEvent& event) {
        renderer::DrawList draw_list;

        math::Mat4f proj_matrix = math::PerspectiveProj(0.785398f , 4.0f / 3.0f, 0.1f, 100.0f);

        world_->ForEach<TransformComponent, ModelRendererComponent>([&](ecs::Entity entity) mutable {
            auto& transform = world_->GetComponent<TransformComponent>(entity);
            auto& model_renderer = world_->GetComponent<ModelRendererComponent>(entity);

            math::Mat4f model_matrix = math::Translate(transform.translation) *
                    math::Rotate(transform.rotation) * math::Scale(transform.scale);

            renderer::ShaderParamList shader_params;
            shader_params.SetParam("proj", proj_matrix);
            shader_params.SetParam("model", model_matrix);
            // For debug only
            shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, 0.0f, -10.0f)));

            model_renderer.model->Draw(draw_list, shader_params);
        });

        renderer_->Clear();
        renderer_->DrawList(draw_list);
        renderer_->SwapBuffers();
    }
}