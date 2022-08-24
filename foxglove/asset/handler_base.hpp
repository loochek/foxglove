#pragma once


#include <string>
#include <unordered_map>
#include <asset/asset_manager.hpp>
#include <asset/asset.hpp>

namespace foxglove::asset {
    class IAssetHandler {
    public:
        virtual ~IAssetHandler() {}

        // Must provide interface defined by AssetManager class
        // (except that GetAsset must give reference to AssetBase)

        virtual AssetPtr<AssetBase> GetAsset(const std::string& name, bool prepare_now) = 0;

        virtual void LoadAll() = 0;
        virtual void InitializeAll() = 0;
        virtual void Cleanup() = 0;
    };

    // Common asset handler stuff
    template<typename AssetInternalType>
    class AssetHandlerBase : public IAssetHandler {
    public:
        virtual AssetPtr<AssetBase> GetAsset(const std::string& name, bool prepare_now) override {
            AssetInternalType& asset = assets_[name];
            if (asset.state == AssetState::Void && prepare_now) {
                Load(name);
                Initialize(name);
            }

            return AssetPtr<AssetBase>(&asset);
        }

        virtual void LoadAll() override {
            for (auto& asset_pair : assets_) {
                const std::string& name = asset_pair.first;
                AssetInternalType& asset = asset_pair.second;

                if (asset.state == AssetState::Void) {
                    Load(name);
                }
            }
        }

        virtual void InitializeAll() override {
            for (auto& asset_pair : assets_) {
                const std::string& name = asset_pair.first;
                AssetInternalType& asset = asset_pair.second;

                if (asset.state == AssetState::Uninitialized) {
                    Initialize(name);
                }
            }
        }

        virtual void Cleanup() override {
            for (auto& asset_pair : assets_) {
                const std::string& name = asset_pair.first;
                AssetInternalType& asset = asset_pair.second;

                if (asset.ref_counter == 0) {
                    assets_.erase(name);
                }
            }
        }

    protected:
        virtual void Load(const std::string& name) = 0;
        virtual void Initialize(const std::string& name) = 0;

    protected:
        std::unordered_map<std::string, AssetInternalType> assets_;
    };
}
