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
#include <renderer/shader.hpp>
// #include <renderer/vertex_data.hpp>
#include <renderer/texture.hpp>

namespace foxglove::renderer {
    class Renderer :
        public utils::Singleton<Renderer>,
        public core::IEventListener<core::WindowResizeEvent> {
    public:
        Renderer() {
            window_handle_ = static_cast<GLFWwindow*>(Engine::Instance()->window_->GetNativeHandle());

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                throw std::runtime_error("Failed to initialize GLAD");

            Engine::Instance()->events_->Subscribe<core::WindowResizeEvent>(this);
        }

        ~Renderer() {}

        // void DrawTriangles(const VertexData &geometry, const Shader &shader) {
        //     shader.BindScope([&]() {
        //         geometry.BindScope([&]() {
        //             GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, geometry.GetVertexCount()));
        //         });
        //     });
        // };

        // void DrawTriangles(const VertexData &geometry, const Shader &shader, const Texture& texture) {
        //     shader.BindScope([&]() {
        //         geometry.BindScope([&]() {
        //             texture.BindScope([&] {
        //                 GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, geometry.GetVertexCount()));
        //             });
        //         });
        //     });
        // };

        void Clear() {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void SwapBuffers() {
            glfwSwapBuffers(window_handle_);
        }

        virtual void OnEvent(const core::WindowResizeEvent& event) override {
            glViewport(0, 0, event.new_size_.x, event.new_size_.y);
        }

    private:
        GLFWwindow* window_handle_;
    };
}
