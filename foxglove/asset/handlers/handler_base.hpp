#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <asset/asset.hpp>
#include <asset/asset_handler.hpp>
#include <asset/asset_manager.hpp>

namespace foxglove::asset {
    // Common asset handler stuff
    template<typename AssetInternalType>
    class AssetHandlerBase : public IAssetHandler {
    public:
        explicit AssetHandlerBase(AssetManager& asset_mgr) : asset_mgr_(asset_mgr) {}

        AssetPtr<GenericAsset> GetAsset(const std::string& name, AssetState required_state) override {
            auto emplace_res = assets_.emplace(name, name);
            AssetInternalType& asset = emplace_res.first->second;
            if (emplace_res.second) {
                // Set the name if inserted
                asset.name = name;
            }

            if (required_state == AssetState::Uninitialized) {
                if (asset.state == AssetState::Void) {
                    Load(asset);
                }
            } else if (required_state == AssetState::ReadyToUse) {
                if (asset.state == AssetState::Void) {
                    Load(asset);
                }

                if (asset.state == AssetState::Uninitialized) {
                    Initialize(asset);
                }
            }

            return AssetPtr<GenericAsset>(&asset);
        }

        void Load(AssetPtr<GenericAsset> asset_ptr) override {
            Load(PtrToInternal(asset_ptr));
        }

        void Initialize(AssetPtr<GenericAsset> asset_ptr) override {
            Initialize(PtrToInternal(asset_ptr));
        }

        void LoadAll() override {
            for (auto& asset_pair : assets_) {
                AssetInternalType& asset = asset_pair.second;
                if (asset.state == AssetState::Void) {
                    Load(asset);
                }
            }
        }

        void InitializeAll() override {
            for (auto& asset_pair : assets_) {
                AssetInternalType& asset = asset_pair.second;
                if (asset.state == AssetState::Uninitialized) {
                    Initialize(asset);
                }
            }
        }

        void Cleanup() override {
            for (auto& asset_pair : assets_) {
                const std::string& name = asset_pair.first;
                AssetInternalType& asset = asset_pair.second;

                if (asset.ref_counter == 0) {
                    assets_.erase(name);
                }
            }
        }

    protected:
        virtual void Load(AssetInternalType& asset) = 0;
        virtual void Initialize(AssetInternalType& asset) = 0;

    private:
        AssetInternalType& PtrToInternal(AssetPtr<GenericAsset> ptr) {
            return *static_cast<AssetInternalType*>(ptr.GetInternalAsset());
        }

    protected:
        AssetManager& asset_mgr_;
        std::unordered_map<std::string, AssetInternalType> assets_;
    };
}
