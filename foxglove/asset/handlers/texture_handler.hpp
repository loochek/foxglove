#pragma once

#include <asset/asset.hpp>
#include <asset/asset_manager.hpp>
#include <asset/handler_base.hpp>

namespace foxglove::renderer {
    class Texture;
}

namespace foxglove::asset {
    struct TextureAsset : AssetBase {
        std::unique_ptr<renderer::Texture> texture;
    };

    class TextureAssetHandler : public AssetHandlerBase<TextureAsset> {
        friend const renderer::Texture* AssetPtr<renderer::Texture>::Access();

    public:
        TextureAssetHandler() = default;

    private:
        virtual void Load(const std::string& name) override;
        virtual void Initialize(const std::string& name) override;
    };

    template<>
    inline const renderer::Texture* AssetPtr<renderer::Texture>::Access() {
        return const_cast<const renderer::Texture*>(static_cast<TextureAsset*>(asset_)->texture.get());
    }
}
