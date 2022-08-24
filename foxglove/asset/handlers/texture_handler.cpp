#include "texture_handler.hpp"

#include <fmt/core.h>
#include <stb_image.h>
#include <math/vector.hpp>
#include <renderer/texture.hpp>

namespace foxglove::asset {
    void TextureAssetHandler::Load(const std::string& name) {
        TextureAsset& asset = assets_[name];
        FXG_ASSERT(asset.state == AssetState::Void);

        std::string path = fmt::format("assets/textures/{}.jpg", name);

        math::Vec2i size;
        void* raw_texture = stbi_load(path.c_str(), &size.x, &size.y, NULL, 0);
        if (raw_texture == nullptr) {
            throw std::runtime_error("Unable to load texture");
        }
        
        asset.texture = std::make_unique<renderer::Texture>(size);
        asset.texture->SetData(raw_texture, asset.texture->GetRawDataSize());

        asset.state = AssetState::Uninitialized;
    }

    void TextureAssetHandler::Initialize(const std::string& name) {
        TextureAsset& asset = assets_[name];
        FXG_ASSERT(asset.state == AssetState::Uninitialized);

        asset.texture->CommitToGPU();
        asset.state = AssetState::ReadyToUse;
    }
}
