#pragma once

#include <glad/glad.h>
#include <utils/common.hpp>
#include <renderer/hardware_buffer.hpp>
#include <renderer/gl_assert.hpp>
#include <renderer/vertex_attribute.hpp>

namespace foxglove::renderer {
    /// Representation of GPU object that holds geometry data
    class HardwareVertexData {
    public:
        HardwareVertexData();
        ~HardwareVertexData();

        void SetVertexBuffer(HardwareVertexBuffer& vertex_buffer, const VertexAttributeMapping& mapping);
        void SetIndexBuffer(HardwareIndexBuffer& index_buffer);

        void Bind() {
            GL_ASSERT(glBindVertexArray(handle_));
        }

        static void Unbind() {
            GL_ASSERT(glBindVertexArray(0));
        }

    private:
        void SetVertexAttributeMapping(const VertexAttributeMapping& mapping);

    private:
        // OpenGL's VAO
        GLuint handle_;
    };
}
