#pragma once

#include <asset/asset.hpp>
#include <asset/asset_manager.hpp>
#include <asset/handlers/handler_base.hpp>

namespace foxglove::renderer {
    class Texture;
}

namespace foxglove::asset {
    struct TextureAsset : AssetBase {
        std::unique_ptr<renderer::Texture> texture;

        TextureAsset() = delete;
        TextureAsset(std::string name) : AssetBase(std::move(name)) {}
    };

    class TextureAssetHandler : public AssetHandlerBase<TextureAsset> {
        friend const renderer::Texture* AssetPtr<renderer::Texture>::Access();

    public:
        TextureAssetHandler(AssetManager& asset_mgr);

    private:
        void Load(TextureAsset &asset) override;
        void Initialize(TextureAsset &asset) override;
    };
}
