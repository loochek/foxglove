#pragma once

#include <engine.hpp>

namespace foxglove::core {
    // Base class for application powered by Foxglove framework
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

//        /// Called by framework before initialization
//        virtual void SetupEngine() {}
        /// Called by framework after initialization but before main loop
        virtual void AppInit() {}
        /// Called by framework each frame
        virtual void AppUpdate() {}
        /// Called by framework after main loop exit
        virtual void AppShutdown() {}

    protected:
        Engine engine_;
    };
}
