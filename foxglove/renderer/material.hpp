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
        void SetShaderParam(const std::string& name, ShaderParam param);

        void Bind() const;
        void Unbind() const;
        
    private:
        const Shader* shader_;
        std::vector<const Texture*> textures_;

        ShaderParamList params_;
    };
}
