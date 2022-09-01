#include "engine.hpp"

#include <core/window.hpp>
#include <asset/asset_manager.hpp>
#include <asset/handlers/texture_handler.hpp>
#include <asset/handlers/shader_handler.hpp>
#include <asset/handlers/material_handler.hpp>
#include <renderer/renderer.hpp>
#include <ecs/render_system.hpp>

namespace foxglove {
    Engine::Engine() : running_(true) {}

    void Engine::Init() {
        // Low-level engine subsystems
        events_ = new core::EventBus();
        events_->Subscribe<core::WindowCloseEvent>(this);
        events_->Subscribe<core::ShutdownInitiatedEvent>(this);

        assets_ = new asset::AssetManager();
        assets_->RegisterAssetHandler<renderer::Texture, asset::TextureAssetHandler>();
        assets_->RegisterAssetHandler<renderer::Shader, asset::ShaderAssetHandler>();
        assets_->RegisterAssetHandler<renderer::Material, asset::MaterialAssetHandler>();

        window_ = new core::Window(math::Vec2i(800, 600), "Foxglove Application");
        renderer_ = new renderer::Renderer();

        // High-level systems
        render_system_ = new ecs::RenderSystem();
    }

    void Engine::Run() {
        while (running_) {
            events_->Emit(core::MainLoopNativePollEvent());
            // events_->Emit(core::MainLoopPreUpdateEvent());
            // events_->Emit(core::MainLoopUpdateEvent());
            // events_->Emit(core::MainLoopPostUpdateEvent());
            events_->Emit(core::MainLoopRenderEvent());
        }
    }

    void Engine::Shutdown() {
        delete render_system_;

        delete renderer_;
        delete window_;
        delete assets_;
        delete events_;
    }

    void Engine::OnEvent(const core::WindowCloseEvent&) {
        events_->Emit(core::ShutdownInitiatedEvent());
    }

    void Engine::OnEvent(const core::ShutdownInitiatedEvent&) {
        running_ = false;
    }
}
