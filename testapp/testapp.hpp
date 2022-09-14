#pragma once

#include <core/application.hpp>
#include <asset/asset.hpp>
#include <ecs/world.hpp>

using namespace foxglove;

namespace foxglove::renderer {
    class Model;
}

namespace foxglove::game {
    class RenderSystem;
    class CameraControlSystem;
}

class TestApp :
        public core::Application,
        public core::IEventListener<core::GameUpdateEvent> {
public:
    void AppInit() override;
    void OnEvent(const core::GameUpdateEvent& event) override;

private:
    asset::AssetPtr<renderer::Model> model_;

    ecs::World world_;

    std::unique_ptr<game::RenderSystem> render_system_;
    std::unique_ptr<game::CameraControlSystem> camera_system_;

    ecs::Entity entity_;
    ecs::Entity camera_;
};
