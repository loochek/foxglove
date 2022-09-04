#include "renderer.hpp"

namespace foxglove::renderer {
    Renderer::Renderer() {
        window_handle_ = static_cast<GLFWwindow*>(Engine::Instance()->window_->GetNativeHandle());

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        Engine::Instance()->events_->Subscribe<core::WindowResizeEvent>(this);

        GL_ASSERT(glEnable(GL_DEPTH_TEST));
//        GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }
}
