#include "material.hpp"
#include <glad/glad.h>

namespace foxglove::renderer {
    Material::Material(const Shader *shader) : shader_(shader) {}

    void Material::AppendTexture(std::string name, const Texture* texture) {
        params_.SetParam(name, int(textures_.size()));
        textures_.push_back(texture);
    }

    void Material::SetShaderParam(const std::string& name, ShaderParam param) {
        params_.SetParam(name, param);
    }

    void Material::Bind() const {
        for (int i = 0; i < textures_.size(); i++) {
            textures_[i]->GetHardwareTexture()->Bind(i);
            // Name-to-sampler mapping is specified in the param list
        }

        shader_->ApplyParamList(params_);
        shader_->Bind();
    }

    void Material::Unbind() const {
        Shader::Unbind();
        for (int i = 0; i < textures_.size(); i++) {
            HardwareTexture::Unbind(i);
        }
    }
}