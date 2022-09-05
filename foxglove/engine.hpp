#pragma once


#include <iostream>

#include <utils/singleton.hpp>
#include <core/event_bus.hpp>
#include <core/events.hpp>

namespace foxglove {
    namespace core {
        class EventBus;
        class Window;
    }

    namespace renderer {
        class Renderer;
    }

    namespace asset {
        class AssetManager;
    }
    
    /// Global engine state. Responsible to engine subsystems initialization and shutdown
    class Engine :
        public utils::Singleton<Engine>,
        public core::IEventsListener<core::WindowCloseEvent, core::ShutdownInitiatedEvent> {
    public:
        Engine();
        ~Engine() = default;

        void Init();
        void Run();
        void Shutdown();

        void OnEvent(const core::WindowCloseEvent&) override;
        void OnEvent(const core::ShutdownInitiatedEvent&) override;

    public:
        core::EventBus* events_;
        core::Window* window_;

        asset::AssetManager* assets_;

        renderer::Renderer* renderer_;

    private:
        bool running_;
    };
}
