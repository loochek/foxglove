#include "mesh.hpp"
#include <cstring>
#include <type_traits>

namespace foxglove::renderer {
    static_assert(sizeof(math::Vec3f) == 12);
    static_assert(sizeof(math::Vec2f) == 8);
    static_assert(std::alignment_of_v<math::Vec2f> == 4);
    static_assert(std::alignment_of_v<math::Vec3f> == 4);

    Mesh::Mesh(std::vector<math::Vec3f> vertices) : positions_(std::move(vertices)),
                                                    indexed_draw_(false), has_normals_(false), has_tex_coords_(false) {
    }

    void Mesh::SetIndices(std::vector<unsigned short> indices) {
        indices_ = std::move(indices);
        indexed_draw_ = true;
    }

    void Mesh::SetNormals(std::vector<math::Vec3f> normals) {
        FXG_ASSERT(normals.size() == positions_.size());
        normals_ = std::move(normals);
        has_normals_ = true;
    }

    void Mesh::SetTexCoords(std::vector<math::Vec2f> tex_coords) {
        FXG_ASSERT(tex_coords.size() == positions_.size());
        tex_coords_ = std::move(tex_coords);
        has_tex_coords_ = true;
    }

#define ATTR_COPY(array, type) \
    for (int i = 0; i < vertex_count; i++) { \
        memcpy(&packed_data[curr_attr_offset + i * one_vertex_count], (array)[i].RawData(), sizeof(type)); \
    }                   \
    \
    curr_attr_offset += sizeof(type) / sizeof(float);

    void Mesh::CommitToGPU() {
        int vertex_count = positions_.size();

        // Prepare packed vertex data
        InterleavedAttributeMapping mapping;
        mapping.AppendAttribute(VertexAttributeType::Position);

        if (has_normals_) {
            mapping.AppendAttribute(VertexAttributeType::Normal);
        }

        if (has_tex_coords_) {
            mapping.AppendAttribute(VertexAttributeType::TexCoord);
        }

        int one_vertex_count = mapping.GetOneVertexSize() / sizeof(float);
        int vertex_buffer_count = one_vertex_count * vertex_count;
        std::unique_ptr<float[]> packed_data =
                std::unique_ptr<float[]>(new float[vertex_buffer_count]);

        int curr_attr_offset = 0;

        ATTR_COPY(positions_, math::Vec3f);

        if (has_normals_) {
            ATTR_COPY(normals_, math::Vec3f);
        }

        if (has_tex_coords_) {
            ATTR_COPY(tex_coords_, math::Vec2f);
        }

        // Create vertex and index buffer on GPU
        vert_data_ = std::make_unique<HardwareVertexData>();

        int vertex_buffer_size = vertex_buffer_count * sizeof(float);
        vertex_buffer_ = std::make_unique<HardwareVertexBuffer>(vertex_buffer_size);
        vertex_buffer_->SetData(packed_data.get(), vertex_buffer_size);
        vert_data_->SetVertexBuffer(*vertex_buffer_, mapping);

        if (indexed_draw_) {
            int index_buffer_size = vertex_count * sizeof(unsigned short);
            index_buffer_ = std::make_unique<HardwareIndexBuffer>(index_buffer_size);
            index_buffer_->SetData(indices_.data(), index_buffer_size);
            vert_data_->SetIndexBuffer(*index_buffer_);
        }
    }
}