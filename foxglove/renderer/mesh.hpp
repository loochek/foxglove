#pragma once

#include <glad/glad.h>
#include <vector>
#include <utils/common.hpp>
#include <utils/non_copyable.hpp>
#include <math/vector.hpp>
#include <renderer/material.hpp>
#include <renderer/hardware_vertex_data.hpp>

namespace foxglove::renderer {
    class Mesh : public utils::NonCopyable {
        friend class Renderer;
    public:
        Mesh() = delete;
        explicit Mesh(std::vector<math::Vec3f> vertices);

        void SetIndices(std::vector<unsigned int> indices);
        void SetNormals(std::vector<math::Vec3f> normals);
        void SetTexCoords(std::vector<math::Vec2f> tex_coords);

        void SetMaterial(const Material* material);

        void CommitToGPU();

    private:
        bool indexed_draw_;
        bool has_normals_;
        bool has_tex_coords_;

        std::vector<math::Vec3f> positions_;
        std::vector<math::Vec3f> normals_;
        std::vector<math::Vec2f> tex_coords_;

        std::vector<unsigned int> indices_;

        const Material* material_;

        std::unique_ptr<HardwareVertexBuffer> vertex_buffer_;
        std::unique_ptr<HardwareIndexBuffer> index_buffer_;
        std::unique_ptr<HardwareVertexData> vert_data_;
    };
};
