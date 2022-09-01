#pragma once

#include <engine.hpp>
#include <core/event_bus.hpp>
#include <core/events.hpp>
#include <math/3d_stuff.hpp>
#include <utils/singleton.hpp>
#include <renderer/renderer.hpp>
#include <renderer/vertex_attribute.hpp>
#include <renderer/mesh.hpp>
#include <asset/asset_manager.hpp>
#include <renderer/material.hpp>

namespace foxglove::ecs {
    class RenderSystem :
        public core::IEventListener<core::MainLoopRenderEvent> {
    public:
        RenderSystem() {
            renderer_ = Engine::Instance()->renderer_;
            Engine::Instance()->events_->Subscribe<core::MainLoopRenderEvent>(this);

            std::vector<math::Vec3f> vertices = { math::Vec3f(-0.5f, -0.5f, 0.0f),
                                                  math::Vec3f(0.5f, -0.5f, 0.0f),
                                                  math::Vec3f(0.0f,  0.5f, 0.0f) };
//
//            std::vector<math::Vec3f> colors = { math::Vec3f(1.0f,  0.0f, 0.0f),
//                                                math::Vec3f(0.0f,  1.0f, 0.0f),
//                                                math::Vec3f(0.0f,  0.0f, 1.0f) };

            std::vector<math::Vec2f> uv = { math::Vec2f(0.0f, 0.0f),
                                            math::Vec2f(1.0f, 0.0f),
                                            math::Vec2f(0.5f, 1.0f) };

            mesh_ = new renderer::Mesh(vertices);
            mesh_->SetTexCoords(uv);

            material_ = Engine::Instance()->assets_->GetAsset<renderer::Material>("default");
            Engine::Instance()->assets_->Precache();

            mesh_->SetMaterial(material_.Get());
            mesh_->CommitToGPU();
        }

        ~RenderSystem() {
            delete mesh_;
        }

        virtual void OnEvent(const core::MainLoopRenderEvent&) override {
            renderer_->Clear();
            static float angle = 0.0f;
            angle += 0.01f;
            material_->GetShader()->SetUniform("transform", math::Rotate(math::Vec3f(0.0f, 0.0f, 1.0f), angle));
            mesh_->Draw();
            renderer_->SwapBuffers();
        }

    public:
        renderer::Renderer* renderer_;
        renderer::Mesh* mesh_;

        asset::AssetPtr<renderer::Material> material_;
    };
};
