#pragma once

#include <asset/asset.hpp>
#include <asset/handlers/handler_base.hpp>

namespace foxglove::renderer {
    class Shader;
    class Texture;
    class Material;
}

namespace foxglove::asset {
    struct MaterialAsset : AssetBase {
        std::unique_ptr<renderer::Material> material;

        // dependencies
        AssetPtr<renderer::Shader> shader_dep;
        std::vector<AssetPtr<renderer::Texture>> texture_deps;

        // temporary cross-state data
        std::vector<std::string> samplers;

        MaterialAsset() = delete;
        MaterialAsset(std::string name) : AssetBase(std::move(name)) {}
    };

    class MaterialAssetHandler : public AssetHandlerBase<MaterialAsset> {
        friend const renderer::Material* AssetPtr<renderer::Material>::Access();

    public:
        MaterialAssetHandler(AssetManager& mgr);

    private:
        void Load(MaterialAsset& asset) override;
        void Initialize(MaterialAsset& asset) override;
    };
}
