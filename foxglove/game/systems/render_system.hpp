#pragma once

#include <engine.hpp>
#include <core/event_bus.hpp>
#include <ecs/world.hpp>

namespace foxglove::renderer {
    class Renderer;
}

namespace foxglove::game {
    class RenderSystem : public core::IEventListener<core::MainLoopRenderEvent> {
    public:
        explicit RenderSystem(ecs::World *world);

        void OnEvent(const core::MainLoopRenderEvent& event) override;

    private:
        ecs::World* world_;
        renderer::Renderer* renderer_;
    };
}