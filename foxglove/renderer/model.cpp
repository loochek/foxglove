#include "model.hpp"

namespace foxglove::renderer {
    void Model::AddMesh(const Mesh *mesh, const Material *material) {
        parts_.emplace_back(mesh, material);
    }

    void Model::Draw(DrawList &draw_list, const ShaderParamList& params) const {
        for (const ModelPart& part : parts_) {
            draw_list.AddCommand(DrawCommand(part.mesh, part.material, params));
        }
    }
}