#include "shader_handler.hpp"

#include <fmt/core.h>
#include <utils/filesystem.hpp>
#include <renderer/shader.hpp>

namespace foxglove::asset {
    ShaderAssetHandler::ShaderAssetHandler(AssetManager &asset_mgr) : AssetHandlerBase(asset_mgr) {}

    void ShaderAssetHandler::Load(ShaderAsset& asset) {
        FXG_ASSERT(asset.state == AssetState::Void);

        std::string vs_path = fmt::format("assets/shaders/{}.vsh", asset.name);
        std::string fs_path = fmt::format("assets/shaders/{}.fsh", asset.name);

        asset.vs_src = utils::ReadTextFile(vs_path);
        asset.fs_src = utils::ReadTextFile(fs_path);

        asset.state = AssetState::Uninitialized;
    }

    void ShaderAssetHandler::Initialize(ShaderAsset& asset) {
        FXG_ASSERT(asset.state == AssetState::Uninitialized);

        asset.shader = std::make_unique<renderer::Shader>(asset.vs_src.c_str(), asset.fs_src.c_str());
        asset.state = AssetState::ReadyToUse;
    }

    template<>
    const renderer::Shader* AssetPtr<renderer::Shader>::Access() {
        return const_cast<const renderer::Shader*>(static_cast<ShaderAsset*>(asset_)->shader.get());
    }
}
