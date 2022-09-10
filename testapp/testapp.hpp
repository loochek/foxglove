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
}

class TestApp :
        public core::Application,
        public core::IEventListener<core::MainLoopUpdateEvent> {
public:
    void AppInit() override;
    void OnEvent(const core::MainLoopUpdateEvent&) override;

private:
    asset::AssetPtr<renderer::Model> model_;

    std::unique_ptr<game::RenderSystem> render_system_;
    ecs::World world_;

    ecs::Entity entity_;
};
