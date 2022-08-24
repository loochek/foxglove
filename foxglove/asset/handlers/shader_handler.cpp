#include "shader_handler.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <fmt/core.h>
#include <renderer/shader.hpp>

namespace foxglove::asset {
    void ShaderAssetHandler::Load(const std::string& name) {
        ShaderAsset& asset = assets_[name];
        FXG_ASSERT(asset.state == AssetState::Void);

        std::string vs_path = fmt::format("assets/shaders/{}.vsh", name);
        std::string fs_path = fmt::format("assets/shaders/{}.fsh", name);

        asset.vs_src = ReadFile(vs_path);
        asset.fs_src = ReadFile(fs_path);
    
        asset.state = AssetState::Uninitialized;
    }

    void ShaderAssetHandler::Initialize(const std::string& name) {
        ShaderAsset& asset = assets_[name];
        FXG_ASSERT(asset.state == AssetState::Uninitialized);

        asset.shader = std::make_unique<renderer::Shader>(asset.vs_src.c_str(), asset.fs_src.c_str());
        asset.state = AssetState::ReadyToUse;
    }

    std::string ShaderAssetHandler::ReadFile(const std::string& path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}
