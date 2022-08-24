#include "material.hpp"
#include <glad/glad.h>

namespace foxglove::renderer {
    Material::Material(Shader *shader) : shader_(shader) {}

    void Material::AppendTexture(std::string name, Texture* texture) {
        samplers_.emplace_back(std::move(name), texture);
    }

    void Material::Bind() {
        shader_->Bind();
        for (int i = 0; i < samplers_.size(); i++) {
            TextureSampler& sampler = samplers_[i];
            shader_->SetUniform(sampler.name.c_str(), i);
            sampler.texture->GetHardwareTexture()->Bind(i);
        }
    }

    void Material::Unbind() {
        Shader::Unbind();
        for (int i = 0; i < samplers_.size(); i++) {
            HardwareTexture::Unbind(i);
        }
    }
}