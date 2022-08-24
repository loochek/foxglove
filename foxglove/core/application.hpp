#pragma once


#include <engine.hpp>

namespace foxglove::core {
    // Base class for application powered by Foxglove Engine
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        /// Called by engine before initialization
        virtual void SetupEngine() {}
        /// Called by engine after initialization but before main loop
        virtual void AppInit() {}
        /// Called by engine each frame
        virtual void AppUpdate() {}
        /// Called by engine after main loop exit
        virtual void AppShutdown() {}

    protected:
        Engine engine_;
    };
}
