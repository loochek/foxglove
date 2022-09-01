#pragma once

#include <string>
#include <renderer/shader.hpp>
#include <renderer/texture.hpp>

namespace foxglove::renderer {
    class Material {
        friend class Renderer;

    public:
        Material(const Shader* shader);

        void AppendTexture(std::string name, const Texture* texture);

        void Bind() const;
        void Unbind() const;

        const Shader* GetShader() const {
            return shader_;
        }

    private:
        struct TextureSampler {
            std::string name;
            const Texture* texture;

            TextureSampler(std::string name, const Texture* texture) : name(std::move(name)), texture(texture) {}
        };

        const Shader* shader_;

        std::vector<TextureSampler> samplers_;
    };
}
