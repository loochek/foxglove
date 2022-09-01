#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <engine.hpp>
#include <core/event_bus.hpp>
#include <core/events.hpp>
#include <core/window.hpp>
#include <utils/singleton.hpp>

#include <renderer/gl_assert.hpp>
#include "shader.hpp"

namespace foxglove::renderer {
    class Renderer :
        public utils::Singleton<Renderer>,
        public core::IEventListener<core::WindowResizeEvent> {
    public:
        Renderer();
        ~Renderer() = default;

        void Clear() {
            GL_ASSERT(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
            GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));
        }

        void SwapBuffers() {
            GL_ASSERT(glfwSwapBuffers(window_handle_));
        }

        virtual void OnEvent(const core::WindowResizeEvent& event) override {
            GL_ASSERT(glViewport(0, 0, event.new_size_.x, event.new_size_.y));
        }

    private:
        GLFWwindow* window_handle_;


    };
}
