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
#include <renderer/model.hpp>
#include <renderer/draw_list.hpp>

namespace foxglove::ecs {
    class RenderSystem :
        public core::IEventListener<core::MainLoopRenderEvent> {
    public:
        RenderSystem() {
            renderer_ = Engine::Instance()->renderer_;
            Engine::Instance()->events_->Subscribe<core::MainLoopRenderEvent>(this);

//            std::vector<math::Vec3f> vertices = { math::Vec3f(-0.5f, -0.5f, 0.0f),
//                                                  math::Vec3f(0.5f, -0.5f, 0.0f),
//                                                  math::Vec3f(0.0f,  0.5f, 0.0f) };
////
////            std::vector<math::Vec3f> colors = { math::Vec3f(1.0f,  0.0f, 0.0f),
////                                                math::Vec3f(0.0f,  1.0f, 0.0f),
////                                                math::Vec3f(0.0f,  0.0f, 1.0f) };
//
//            std::vector<math::Vec2f> uv = { math::Vec2f(0.0f, 0.0f),
//                                            math::Vec2f(1.0f, 0.0f),
//                                            math::Vec2f(0.5f, 1.0f) };

//            std::vector<math::Vec3f> vertices = { { -0.5f, -0.5f, -0.5f },
//                                                  { 0.5f, -0.5f, -0.5f },
//                                                  { 0.5f, 0.5f, -0.5f },
//                                                  { 0.5f, 0.5f, -0.5f },
//                                                  { -0.5f, 0.5f, -0.5f },
//                                                  { -0.5f, -0.5f, -0.5f },
//                                                  { -0.5f, -0.5f, 0.5f, },
//                                                  { 0.5f, -0.5f, 0.5f },
//                                                  {0.5f, 0.5f, 0.5f},
//                                                  { 0.5f, 0.5f, 0.5f},
//                                                  {-0.5f, 0.5f,0.5f},
//                                                  {-0.5f, -0.5f,0.5f},
//                                                  {-0.5f, 0.5f, 0.5f},
//                                                  {-0.5f, 0.5f, -0.5f},
//                                                  {-0.5f, -0.5f, -0.5f},
//                                                  {-0.5f, -0.5f, -0.5f},
//                                                  {-0.5f, -0.5f, 0.5f},
//                                                  {-0.5f, 0.5f, 0.5f},
//                                                  {0.5f, 0.5f, 0.5f},
//                                                  {0.5f, 0.5f, -0.5f},
//                                                  {0.5f, -0.5f, -0.5f},
//                                                  {0.5f, -0.5f, -0.5f},
//                                                  {0.5f, -0.5f, 0.5f},
//                                                  {0.5f, 0.5f, 0.5f},
//                                                  {-0.5f, -0.5f, -0.5f},
//                                                  {0.5f, -0.5f, -0.5f},
//                                                  {0.5f, -0.5f, 0.5f},
//                                                  {0.5f, -0.5f, 0.5f},
//                                                  {-0.5f, -0.5f, 0.5f},
//                                                  {-0.5f, -0.5f, -0.5f},
//                                                  {-0.5f,0.5f, -0.5f},
//                                                  {0.5f,0.5f, -0.5f},
//                                                  {0.5f, 0.5f, 0.5f},
//                                                  {0.5f,0.5f, 0.5f},
//                                                  {-0.5f,0.5f, 0.5f},
//                                                  {-0.5f,0.5f, -0.5f}};
//            std::vector<math::Vec2f> uvs = {{ 0.0f, 0.0f },
//                                                  { 1.0f, 0.0f },
//                                                  { 1.0f, 1.0f },
//                                                  { 1.0f, 1.0f },
//                                                  { 0.0f, 1.0f },
//                                                  { 0.0f, 0.0f },
//                                                  { 0.0f, 0.0f },
//                                                  { 1.0f, 0.0f},
//                                                  {1.0f, 1.0f},
//                                                  {1.0f, 1.0f},
//                                                  {0.0f, 1.0f},
//                                                  {0.0f, 0.0f},
//                                                  {1.0f, 0.0f},
//                                                  {1.0f, 1.0f},
//                                                  {0.0f, 1.0f},
//                                                  {0.0f, 1.0f},
//                                                  {0.0f, 0.0f},
//                                                  {1.0f, 0.0f},
//                                                  {1.0f, 0.0f},
//                                                  {1.0f, 1.0f},
//                                                  {0.0f, 1.0f},
//                                                  {0.0f, 1.0f},
//                                                  {0.0f, 0.0f},
//                                                  {1.0f, 0.0f},
//                                                  {0.0f, 1.0f},
//                                                  {1.0f, 1.0f},
//                                                  {1.0f, 0.0f},
//                                                  {1.0f, 0.0f},
//                                                  {0.0f, 0.0f},
//                                                  {0.0f, 1.0f},
//                                                  {0.0f, 1.0f},
//                                                  {1.0f, 1.0f},
//                                                  {1.0f, 0.0f},
//                                                  {1.0f, 0.0f},
//                                                  {0.0f, 0.0f},
//                                                  {0.0f, 1.0f}};
//
//            mesh_ = new renderer::Mesh(vertices);
//            mesh_->SetTexCoords(uvs);

            model_ = Engine::Instance()->assets_->GetAsset<renderer::Model>("rat2");
            Engine::Instance()->assets_->Precache();

//            mesh_->CommitToGPU();
        }

        ~RenderSystem() {
//            delete mesh_;
        }

        virtual void OnEvent(const core::MainLoopRenderEvent&) override {
            renderer_->Clear();
            static float angle = 0.0f;
            angle += 0.01f;

            renderer::ShaderParamList shader_params;
            shader_params.SetParam("proj", math::PerspectiveProj(0.785398f , 4.0f / 3.0f, 0.1f, 100.0f));
            shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, 0.0f, -10.0f)));
//            shader_params.SetParam("model", math::Scale(math::Vec3f(0.1f, 0.1f, 0.1f)));
            shader_params.SetParam("model", math::Rotate(math::Vec3f(1.0f, 1.0f, 1.0f), angle));

            renderer::DrawList draw_list;
            model_->Draw(draw_list, shader_params);
//            draw_list.AddCommand(renderer::DrawCommand(mesh_, material_.Get(), std::move(shader_params)));

            renderer_->DrawList(draw_list);
            renderer_->SwapBuffers();
        }

    public:
        asset::AssetPtr<renderer::Model> model_;
        renderer::Renderer* renderer_;
//        renderer::Mesh* mesh_;
//        asset::AssetPtr<renderer::Material> material_;
    };
};
