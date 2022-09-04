#include "texture_handler.hpp"

#include <fmt/core.h>
#include <stb_image.h>
#include <math/vector.hpp>
#include <renderer/texture.hpp>

namespace foxglove::asset {
    TextureAssetHandler::TextureAssetHandler(AssetManager &asset_mgr) : AssetHandlerBase(asset_mgr) {}

    void TextureAssetHandler::Load(TextureAsset &asset) {
        FXG_ASSERT(asset.state == AssetState::Void);

        std::string path = fmt::format("assets/textures/{}", asset.name);

        math::Vec2i size;
        void* raw_texture = stbi_load(path.c_str(), &size.x, &size.y, NULL, STBI_rgb);
        if (raw_texture == nullptr) {
            throw std::runtime_error("Unable to load texture");
        }

        asset.texture = std::make_unique<renderer::Texture>(size);
        asset.texture->SetData(raw_texture, asset.texture->GetRawDataSize());

        stbi_image_free(raw_texture);
        asset.state = AssetState::Uninitialized;
    }

    void TextureAssetHandler::Initialize(TextureAsset &asset) {
        FXG_ASSERT(asset.state == AssetState::Uninitialized);

        asset.texture->CommitToGPU();
        asset.state = AssetState::ReadyToUse;
    }

    template<>
    const renderer::Texture* AssetPtr<renderer::Texture>::Access() {
        return const_cast<const renderer::Texture*>(static_cast<TextureAsset*>(asset_)->texture.get());
    }
}
