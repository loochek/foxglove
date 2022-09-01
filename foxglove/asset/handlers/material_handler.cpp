#include "material_handler.hpp"

#include <fmt/core.h>
#include <json.hpp>
#include <utils/filesystem.hpp>
#include <renderer/material.hpp>
#include <iostream>

using json = nlohmann::json;

namespace foxglove::asset {
    MaterialAssetHandler::MaterialAssetHandler(AssetManager &mgr) : AssetHandlerBase(mgr) {}

    void MaterialAssetHandler::Load(MaterialAsset& asset) {
        FXG_ASSERT(asset.state == AssetState::Void);

        std::string path = fmt::format("assets/materials/{}", asset.name);
        std::string material_json = utils::ReadTextFile(path);

        json material_data = json::parse(material_json);
        std::string shader_asset_name = material_data["shader"].get<std::string>();

        // Fetch and load dependencies

        asset.shader_dep = asset_mgr_.GetAsset<renderer::Shader>(shader_asset_name,
                                                                 AssetState::Uninitialized);
        for (auto& sampler : material_data["samplers"].items()) {
            const std::string& name = sampler.key();
            const std::string& texture_asset_name = sampler.value().get<std::string>();

            asset.samplers.push_back(name);
            asset.texture_deps.push_back(asset_mgr_.GetAsset<renderer::Texture>(texture_asset_name,
                                                                                AssetState::Uninitialized));
        }

        asset.state = AssetState::Uninitialized;
    }

    void MaterialAssetHandler::Initialize(MaterialAsset& asset) {
        asset_mgr_.Initialize(asset.shader_dep);
        asset.material = std::make_unique<renderer::Material>(asset.shader_dep.Get());

        for (int i = 0; i < asset.texture_deps.size(); i++) {
            AssetPtr<renderer::Texture> texture_dep = asset.texture_deps[i];
            asset_mgr_.Initialize(texture_dep);
            asset.material->AppendTexture(asset.samplers[i], texture_dep.Get());
        }

        asset.state = AssetState::ReadyToUse;
    }

    template<>
    const renderer::Material* AssetPtr<renderer::Material>::Access() {
        return const_cast<const renderer::Material*>(static_cast<MaterialAsset*>(asset_)->material.get());
    }
}
