#include "hardware_vertex_data.hpp"

namespace foxglove::renderer {
    HardwareVertexData::HardwareVertexData() : handle_(0) {
        GL_ASSERT(glGenVertexArrays(1, &handle_));
    }

    HardwareVertexData::~HardwareVertexData() {
        GL_ASSERT(glDeleteVertexArrays(1, &handle_));
    }

    void HardwareVertexData::SetVertexBuffer(HardwareVertexBuffer& vertex_buffer,
                                             const VertexAttributeMapping& mapping) {
        Bind();
        vertex_buffer.Bind();
        SetVertexAttributeMapping(mapping);
        Unbind();
    }

    void HardwareVertexData::SetIndexBuffer(HardwareIndexBuffer& index_buffer) {
        Bind();
        index_buffer.Bind();
        Unbind();
    }

    void HardwareVertexData::SetVertexAttributeMapping(const VertexAttributeMapping& mapping) {
        Bind();
        for (int i = 0; i < mapping.GetAttributeCount(); i++) {
            VertexAttributeType type = mapping.GetAttributeType(i);
            size_t offset = mapping.GetAttributeOffset(i);
            size_t stride = mapping.GetAttributeStride(i);

            GL_ASSERT(glVertexAttribPointer(i, GetVertexAttributeDim(type), GetVertexAttributeGLType(type),
                                            GL_FALSE, stride, (void*)offset));
            GL_ASSERT(glEnableVertexAttribArray(i));
        }
        Unbind();
    }
}
