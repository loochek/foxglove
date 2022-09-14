#include "engine.hpp"

#include <core/window.hpp>
#include <asset/asset_manager.hpp>
#include <asset/handlers/texture_handler.hpp>
#include <asset/handlers/shader_handler.hpp>
#include <asset/handlers/material_handler.hpp>
#include <asset/handlers/model_handler.hpp>
#include <renderer/renderer.hpp>

namespace foxglove::renderer {
    class Model;
}

namespace foxglove {
    Engine::Engine() : running_(true) {}

    void Engine::Init() {
        // Low-level engine subsystems
        events_ = new core::EventBus();
        events_->Subscribe<core::WindowCloseEvent>(this);
        events_->Subscribe<core::KeyDownEvent>(this);
        events_->Subscribe<core::ShutdownInitiatedEvent>(this);

        assets_ = new asset::AssetManager();
        assets_->RegisterAssetHandler<renderer::Texture, asset::TextureAssetHandler>();
        assets_->RegisterAssetHandler<renderer::Shader, asset::ShaderAssetHandler>();
        assets_->RegisterAssetHandler<renderer::Material, asset::MaterialAssetHandler>();
        assets_->RegisterAssetHandler<renderer::Model, asset::ModelAssetHandler>();

        window_ = new core::Window(math::Vec2i(800, 600), "Foxglove Application");
        renderer_ = new renderer::Renderer();
    }

    void Engine::Run() {
        float timestamp = window_->GetTime();
        while (running_) {
            float new_timestamp = window_->GetTime();
            float time_delta = new_timestamp - timestamp;
            timestamp = new_timestamp;

            events_->Emit(core::GameNativePollEvent());
            // events_->Emit(core::MainLoopPreUpdateEvent());
            events_->Emit(core::GameUpdateEvent(time_delta));
            // events_->Emit(core::MainLoopPostUpdateEvent());
            events_->Emit(core::GameRenderEvent());
        }
    }

    void Engine::Shutdown() {
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

    void Engine::OnEvent(const core::KeyDownEvent &event) {
        if (event.key == core::KeyboardKey::KEY_ESC) {
            events_->Emit(core::ShutdownInitiatedEvent());
        }
    }
}
