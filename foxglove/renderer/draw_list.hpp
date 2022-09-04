#pragma once

#include <renderer/mesh.hpp>
#include <renderer/material.hpp>
#include <renderer/shader.hpp>

namespace foxglove::renderer {
    struct DrawCommand {
        const Mesh* mesh;
        const Material* material;
        ShaderParamList params;

        DrawCommand() : mesh(nullptr), material(nullptr) {}
        DrawCommand(const Mesh* mesh, const Material* material, ShaderParamList params) :
            mesh(mesh), material(material), params(std::move(params)) {}

        DrawCommand(const DrawCommand& other) = default;

        DrawCommand(DrawCommand&& other) : mesh(other.mesh), material(other.material), params(std::move(other.params)) {
            other.mesh = nullptr;
            other.material = nullptr;
        }
    };

    class DrawList {
    public:
        void AddCommand(DrawCommand command) {
            cmds_.push_back(std::move(command));
        }

        auto& GetCommands() const {
            return cmds_;
        }

    private:
        std::vector<DrawCommand> cmds_;
    };
}