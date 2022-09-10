#include "window.hpp"

#include <stdexcept>
#include <GLFW/glfw3.h>
#include <engine.hpp>
#include <core/input.hpp>

namespace foxglove::core {
    Window::Window(const math::Vec2i& size, const char* title) {
        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        try {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            handle_ = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
            if (handle_ == nullptr)
                throw std::runtime_error("Failed to create window");
        } catch (...) {
            glfwTerminate();
            throw;
        }

        glfwMakeContextCurrent(handle_);

        glfwSetWindowSizeCallback(handle_, [](GLFWwindow*, int width, int height) {
            Engine::Instance()->events_->Emit(WindowResizeEvent(math::Vec2i(width, height)));
        });

        glfwSetWindowCloseCallback(handle_, [](GLFWwindow*) {
            Engine::Instance()->events_->Emit(WindowCloseEvent());
        });

        glfwSetKeyCallback(handle_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS) {
                Engine::Instance()->events_->Emit(KeyDownEvent(key));
            } else if (action == GLFW_RELEASE) {
                Engine::Instance()->events_->Emit(KeyUpEvent(key));
            }
        });

        glfwSetMouseButtonCallback(handle_, [](GLFWwindow* window, int button, int action, int mods) {
            if (action == GLFW_PRESS) {
                Engine::Instance()->events_->Emit(MouseDownEvent(button));
            } else if (action == GLFW_RELEASE) {
                Engine::Instance()->events_->Emit(MouseUpEvent(button));
            }
        });

        glfwSetCursorPosCallback(handle_, [](GLFWwindow* window, double xpos, double ypos) {
            Engine::Instance()->events_->Emit(MouseMoveEvent(math::Vec2f(xpos, ypos)));
        });
        
        Engine::Instance()->events_->Subscribe<core::MainLoopNativePollEvent>(this);
    }

    Window::~Window() {
        glfwTerminate();
    }

    void Window::Resize(const math::Vec2i& new_size) {
        glfwSetWindowSize(handle_, new_size.x, new_size.y);
    }

    math::Vec2i Window::GetSize() {
        math::Vec2i ret;
        glfwGetWindowSize(handle_, &ret.x, &ret.y);
        return ret;
    }

    void Window::SetTitle(const char* new_title) {
        glfwSetWindowTitle(handle_, new_title);
    }

    void Window::OnEvent(const core::MainLoopNativePollEvent&) {
        glfwPollEvents();
    }
};
