#pragma once

#include <core/application.hpp>
#include <asset/asset.hpp>

using namespace foxglove;

namespace foxglove::renderer {
    class Model;
}

class TestApp :
        public core::Application,
        public core::IEventListener<core::MainLoopRenderEvent> {
public:
    void AppInit() override;
    void OnEvent(const core::MainLoopRenderEvent&) override;

private:
    asset::AssetPtr<renderer::Model> model_;
    renderer::Renderer* renderer_;
};
