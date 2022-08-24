#pragma once

#include <string>
#include <renderer/shader.hpp>
#include <renderer/texture.hpp>

namespace foxglove::renderer {
    class Material {
        friend class Renderer;

    public:
        Material(Shader* shader);

        void AppendTexture(std::string name, Texture* texture);

    private:
        void Bind();
        void Unbind();

    private:
        struct TextureSampler {
            std::string name;
            Texture* texture;

            TextureSampler(std::string name, Texture* texture) : name(std::move(name)), texture(texture) {}
        };

        Shader* shader_;

        std::vector<TextureSampler> samplers_;
    };
}
