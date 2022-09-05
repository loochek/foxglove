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
#include <renderer/mesh.hpp>
#include <renderer/model.hpp>
#include <renderer/draw_list.hpp>

namespace foxglove::renderer {
    class Renderer :
        public utils::Singleton<Renderer>,
        public core::IEventListener<core::WindowResizeEvent> {
    public:
        Renderer();
        ~Renderer() = default;

        void Clear() {
            GL_ASSERT(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
            GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        }

        void DrawList(DrawList &list) {
            auto& cmds = list.GetCommands();

            for (const DrawCommand& cmd : cmds) {
                cmd.mesh->Bind();
                cmd.material->shader_->ApplyParamList(cmd.params);
                cmd.material->Bind();

                if (cmd.mesh->indexed_draw_) {
                    GL_ASSERT(glDrawElements(GL_TRIANGLES, cmd.mesh->indices_.size(), GL_UNSIGNED_SHORT, nullptr));
                } else {
                    GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, cmd.mesh->positions_.size()));
                }

                Mesh::Unbind();
                cmd.material->Unbind();
            }
        }

        void SwapBuffers() {
            GL_ASSERT(glfwSwapBuffers(window_handle_));
        }

        void OnEvent(const core::WindowResizeEvent& event) override {
            GL_ASSERT(glViewport(0, 0, event.new_size_.x, event.new_size_.y));
        }

    private:
        GLFWwindow* window_handle_;
    };
}
