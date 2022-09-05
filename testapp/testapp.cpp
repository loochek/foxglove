#include "testapp.hpp"
#include <asset/asset_manager.hpp>
#include <renderer/model.hpp>
#include <renderer/renderer.hpp>
#include <math/3d_stuff.hpp>
#include <iostream>

void TestApp::AppInit() {
    Engine::Instance()->window_->SetTitle("rat spinning to freebird 10 hours");

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

void TestApp::OnEvent(const core::MainLoopRenderEvent &) {
    renderer_->Clear();
    static float angle = 0.0f;
    angle += 0.02f;

    renderer::ShaderParamList shader_params;
    shader_params.SetParam("proj", math::PerspectiveProj(0.785398f , 4.0f / 3.0f, 0.1f, 100.0f));

    // Model 1: rat2
    shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, 0.0f, -10.0f)));
    shader_params.SetParam("model",  math::Rotate(math::Vec3f(1.0f, 1.0f, 1.0f), angle));

    // Model 2: backpack
//    shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, 0.0f, -10.0f)));
//    shader_params.SetParam("model",  math::Rotate(math::Vec3f(1.0f, 1.0f, 1.0f), angle));

    // Model 3: Diona
//    shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, -3.0f, -10.0f)));
//    shader_params.SetParam("model",  math::Rotate(math::Vec3f(0.0f, 1.0f, 0.0f), angle) * math::Rotate(math::Vec3f(1.0f, 0.0f, 0.0f), -1.57) * math::Scale(math::Vec3f(5.0f, 5.0f, 5.0f)));

    renderer::DrawList draw_list;
    model_->Draw(draw_list, shader_params);
//            draw_list.AddCommand(renderer::DrawCommand(mesh_, material_.Get(), std::move(shader_params)));

    renderer_->DrawList(draw_list);
    renderer_->SwapBuffers();
}

namespace foxglove {
    core::Application* CreateApplication() {
        return new TestApp();
    }
}