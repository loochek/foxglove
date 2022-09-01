#pragma once

#include <string>
#include <asset/asset.hpp>
#include <asset/asset_manager.hpp>
#include <asset/handlers/handler_base.hpp>

namespace foxglove::renderer {
    class Shader;
}

namespace foxglove::asset {
    struct ShaderAsset : AssetBase {
        std::unique_ptr<renderer::Shader> shader;
        std::string vs_src;
        std::string fs_src;

        ShaderAsset() = delete;
        ShaderAsset(std::string name) : AssetBase(std::move(name)) {}
    };

    class ShaderAssetHandler : public AssetHandlerBase<ShaderAsset> {
        friend const renderer::Shader* AssetPtr<renderer::Shader>::Access();

    public:
        ShaderAssetHandler(AssetManager& asset_mgr);

    private:
        void Load(ShaderAsset& asset) override;
        void Initialize(ShaderAsset& asset) override;
    };
}
