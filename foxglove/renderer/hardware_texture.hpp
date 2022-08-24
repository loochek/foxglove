#pragma once

#include <glad/glad.h>
#include <utils/non_copyable.hpp>
#include <math/vector.hpp>
#include <renderer/gl_assert.hpp>

namespace foxglove::renderer {
    class HardwareTexture : public utils::NonCopyable {
        friend class Renderer;
        
    public:
        explicit HardwareTexture(math::Vec2i size);
        ~HardwareTexture();

        void SetData(const void* data, math::Vec2i size, math::Vec2i offset = math::Vec2i());
        void GenerateMipmap();

        void Bind(int texture_unit = 0) const {
            GL_ASSERT(glActiveTexture(GL_TEXTURE0 + texture_unit));
            GL_ASSERT(glBindTexture(GL_TEXTURE_2D, handle_));
        }

        static void Unbind(int texture_unit = 0) {
            GL_ASSERT(glActiveTexture(GL_TEXTURE0 + texture_unit));
            GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0));
        }

    private:

        math::Vec2i size_;
        GLuint handle_;
    };
}
