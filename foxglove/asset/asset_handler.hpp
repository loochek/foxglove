#pragma once

#include <asset/asset.hpp>

namespace foxglove::asset {
    class IAssetHandler {
    public:
        virtual ~IAssetHandler() = default;

        // Must provide interface defined by AssetManager class
        // (except that pointers point to GenericAsset)

        virtual AssetPtr <GenericAsset> GetAsset(const std::string &name, AssetState required_state) = 0;

        virtual void Load(AssetPtr <GenericAsset> asset_ptr) = 0;
        virtual void Initialize(AssetPtr <GenericAsset> asset_ptr) = 0;

        virtual void LoadAll() = 0;
        virtual void InitializeAll() = 0;

        virtual void Cleanup() = 0;
    };
}
