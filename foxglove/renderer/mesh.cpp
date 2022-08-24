#include "mesh.hpp"
#include <cstring>

namespace foxglove::renderer {
    static_assert(sizeof(math::Vec3f) == 12);
    static_assert(sizeof(math::Vec2f) == 8);
    static_assert(offsetof(math::Vec3f, x) == 0);
    static_assert(offsetof(math::Vec2f, x) == 0);

    Mesh::Mesh(std::vector<math::Vec3f> vertices) : positions_(std::move(vertices)),
                                                    indexed_draw_(false), has_normals_(false), has_tex_coords_(false) {
    }

    void Mesh::SetIndices(std::vector<unsigned int> indices) {
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


    void Mesh::SetMaterial(const Material *material) {
        material_ = material;
    }

#define ATTR_COPY(array, type) \
    for (int i = 0; i < vertex_count; i++) { \
        memcpy(&packed_data[curr_attr_offset + i * one_vertex_size], (array)[i].RawData(), sizeof(type)); \
    }                   \
    \
    curr_attr_offset += sizeof(type)

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

        int one_vertex_size = mapping.GetOneVertexSize();
        int vertex_buffer_size = one_vertex_size * vertex_count;
        std::unique_ptr<float[]> packed_data =
                std::unique_ptr<float[]>(new float[vertex_buffer_size]);

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

        vertex_buffer_ = std::make_unique<HardwareVertexBuffer>(vertex_buffer_size);
        vertex_buffer_->SetData(packed_data.get(), vertex_buffer_size);
        vert_data_->SetVertexBuffer(*vertex_buffer_, mapping);

        if (indexed_draw_) {
            int index_buffer_size = vertex_count * sizeof(unsigned int);
            index_buffer_ = std::make_unique<HardwareIndexBuffer>(index_buffer_size);
            index_buffer_->SetData(indices_.data(), index_buffer_size);
            vert_data_->SetIndexBuffer(*index_buffer_);
        }
    }
}