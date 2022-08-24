#include "hardware_texture.hpp"

namespace foxglove::renderer {
    HardwareTexture::HardwareTexture(math::Vec2i size) : size_(size), handle_(0), curr_texture_unit_(-1) {
        GL_ASSERT(glGenTextures(1, &handle_));        
        {
            Bind();
            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

            GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB,
                                   GL_UNSIGNED_BYTE, nullptr));
            Unbind();
        }   
    }

    HardwareTexture::~HardwareTexture() {
        GL_ASSERT(glDeleteTextures(1, &handle_));
    }

    void HardwareTexture::SetData(const void* data, math::Vec2i size, math::Vec2i offset) {
        Bind();
        GL_ASSERT(glTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, size.x, size.y,
                                  GL_RGB, GL_UNSIGNED_BYTE, data));
        Unbind();
    }

    void HardwareTexture::GenerateMipmap() {
        Bind();
        GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
        Unbind();
    }
}
