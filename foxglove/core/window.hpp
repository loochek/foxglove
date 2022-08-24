#pragma once

#include <math/vector.hpp>
#include <utils/singleton.hpp>
#include <core/event_bus.hpp>
#include <core/events.hpp>

class GLFWwindow;

namespace foxglove::core {
    class Window :
        public utils::Singleton<Window>,
        public core::IEventListener<core::MainLoopNativePollEvent> {
    public:
        Window(const math::Vec2i& size, const char* title);
        ~Window();

        void Resize(const math::Vec2i& new_size);
        math::Vec2i GetSize();

        void SetTitle(const char* new_title);

        void* GetNativeHandle() {
            return handle_;
        }

        virtual void OnEvent(const core::MainLoopNativePollEvent&) override;

    private:
        GLFWwindow* handle_;
    };
};
