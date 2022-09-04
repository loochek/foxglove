#pragma once

#include <vector>
#include <utils/non_copyable.hpp>
#include <renderer/mesh.hpp>
#include <renderer/material.hpp>
#include <renderer/draw_list.hpp>

namespace foxglove::renderer {
    class Model : public utils::NonCopyable {
    public:
        void AddMesh(const Mesh* mesh, const Material* material);
        void Draw(DrawList &draw_list, const ShaderParamList& params) const;

    private:
        struct ModelPart {
            const Mesh* mesh;
            const Material* material;

            ModelPart(const Mesh* mesh, const Material* material) : mesh(mesh), material(material) {}
        };

        std::vector<ModelPart> parts_;
    };
}