#include "application.hpp"

#include <engine.hpp>

namespace foxglove::core {
    Application::Application() {
        SetupEngine();
        engine_.Init();
    }

    Application::~Application() {
        engine_.Shutdown();
    }

    void Application::Run() {
        AppInit();
        engine_.Run();
        AppShutdown();
    }
}

namespace foxglove {
    core::Application* CreateApplication() {
        return new core::Application();
    }
}
