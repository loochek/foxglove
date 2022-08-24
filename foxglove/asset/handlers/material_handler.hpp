#pragma once

#include <asset/asset.hpp>
#include <asset/handler_base.hpp>

namespace foxglove::renderer {
    class Shader;
    class Texture;
    class Material;
}

namespace foxglove::asset {
    struct MaterialAsset : AssetBase {
        std::unique_ptr<renderer::Material> material;
        std::string material_json;

        // dependencies
        AssetPtr<renderer::Shader> shader_dep;
        std::vector<AssetPtr<renderer::Texture>> texture_deps;
    };

    class ShaderAssetHandler : public AssetHandlerBase<MaterialAsset> {
        friend const renderer::Shader* AssetPtr<renderer::Shader>::Access();

    public:
        ShaderAssetHandler() = default;

    private:
        virtual void Load(const std::string& name) override;
        virtual void Initialize(const std::string& name) override;

        static std::string ReadFile(const std::string& path);
    };

    template<>
    inline const renderer::Material* AssetPtr<renderer::Material>::Access() {
        return const_cast<const renderer::Material*>(static_cast<MaterialAsset*>(asset_)->material.get());
    }
}
