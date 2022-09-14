#include "testapp.hpp"
#include <asset/asset_manager.hpp>
#include <renderer/model.hpp>
#include <renderer/renderer.hpp>
#include <math/3d_stuff.hpp>
#include <game/systems/render_system.hpp>
#include <game/systems/camera_control_system.hpp>
#include <game/components/model_renderer.hpp>
#include <game/components/camera.hpp>
#include <fmt/core.h>

void TestApp::AppInit() {
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
//            mesh_->CommitToGPU();

    Engine::Instance()->window_->SetTitle("rat spinning to freebird 10 hours");
    Engine::Instance()->events_->Subscribe<core::GameUpdateEvent>(this);

    // Initializing high-level game subsystems

    world_.RegisterComponent<game::TransformComponent>();
    world_.RegisterComponent<game::ModelRendererComponent>();
    world_.RegisterComponent<game::CameraComponent>();

    render_system_ = std::make_unique<game::RenderSystem>(&world_);
    camera_system_ = std::make_unique<game::CameraControlSystem>(&world_);

    // Loading assets

    model_ = Engine::Instance()->assets_->GetAsset<renderer::Model>("rat2");
    Engine::Instance()->assets_->Precache();

    // Creating entity
    entity_ = world_.CreateEntity();
    world_.AddComponent<game::TransformComponent>(entity_).scale = math::Vec3f(0.1f, 0.1f, 0.1f);
    world_.AddComponent<game::ModelRendererComponent>(entity_).model = model_.Get();

    // Creating camera
    camera_ = world_.CreateEntity();
    auto& camera_transform = world_.AddComponent<game::TransformComponent>(camera_);
    world_.AddComponent<game::CameraComponent>(camera_);

    camera_transform.translation = math::Vec3f(-1.0f, 0.0f, 0.0f);

    render_system_->AssignCamera(camera_);
    camera_system_->AssignCamera(camera_);
}

void TestApp::OnEvent(const core::GameUpdateEvent& event) {
//    fmt::print("FPS: {}\n", 1.0f / event.time_delta);

    static float angle = 0.0f;
    angle += event.time_delta;

    // auto& camera_transform = world_.GetComponent<game::TransformComponent>(camera_);
    // fmt::print("{} {} {}\n", camera_transform.translation.x, camera_transform.translation.y, camera_transform.translation.z);

    // Model 1: rat2
    auto& transform = world_.GetComponent<game::TransformComponent>(entity_);
    transform.rotation = math::Vec3f(angle / 1.4f, angle / 1.1f,angle);

    // Model 1: rat2
//    shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, 0.0f, -10.0f)));
//    shader_params.SetParam("model",  math::Rotate(math::Vec3f(1.0f, 1.0f, 1.0f), angle));

    // Model 2: backpack
//    shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, 0.0f, -10.0f)));
//    shader_params.SetParam("model",  math::Rotate(math::Vec3f(1.0f, 1.0f, 1.0f), angle));

    // Model 3: Diona
//    shader_params.SetParam("view", math::Translate(math::Vec3f(0.0f, -3.0f, -10.0f)));
//    shader_params.SetParam("model",  math::Rotate(math::Vec3f(0.0f, 1.0f, 0.0f), angle) * math::Rotate(math::Vec3f(1.0f, 0.0f, 0.0f), -1.57) * math::Scale(math::Vec3f(5.0f, 5.0f, 5.0f)));
}

namespace foxglove {
    core::Application* CreateApplication() {
        return new TestApp();
    }
}