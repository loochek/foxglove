#include "material.hpp"
#include <glad/glad.h>

namespace foxglove::renderer {
    Material::Material(const Shader *shader) : shader_(shader) {}

    void Material::AppendTexture(std::string name, const Texture* texture) {
        samplers_.emplace_back(std::move(name), texture);
    }

    void Material::Bind() const {
        for (int i = 0; i < samplers_.size(); i++) {
            const TextureSampler& sampler = samplers_[i];
            shader_->SetUniform(sampler.name.c_str(), i);
            sampler.texture->GetHardwareTexture()->Bind(i);
        }

        shader_->Bind();
    }

    void Material::Unbind() const {
        Shader::Unbind();
        for (int i = 0; i < samplers_.size(); i++) {
            HardwareTexture::Unbind(i);
        }
    }
}