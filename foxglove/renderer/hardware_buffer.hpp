#pragma once

#include <glad/glad.h>
#include <utils/common.hpp>
#include <utils/non_copyable.hpp>

namespace foxglove::renderer {
    template<int BufferType>
    class GLBuffer : private foxglove::utils::NonCopyable {
    public:
        GLBuffer(size_t size) {
            glGenBuffers(1, &handle_);

            Bind();
            glBufferData(BufferType, size, NULL, GL_DYNAMIC_DRAW);
            Unbind();
        }

        ~GLBuffer() {
            glDeleteBuffers(1, &handle_);
        }

        void SetData(const void* data, size_t size, size_t offset = 0) {
            Bind();
            glBufferSubData(BufferType, offset, size, data);
            Unbind();
        }
        
        void Bind() const {
            glBindBuffer(BufferType, handle_);
        }
        
        static void Unbind() {
            glBindBuffer(BufferType, 0);
        }

    private:
        GLuint handle_;
    };

    using HardwareVertexBuffer = GLBuffer<GL_ARRAY_BUFFER>;
    using HardwareIndexBuffer = GLBuffer<GL_ELEMENT_ARRAY_BUFFER>;
}
