#pragma once


#include <typeindex>
#include <string>
#include <unordered_map>
#include <utils/singleton.hpp>
#include <asset/asset.hpp>
#include <asset/asset_handler.hpp>

namespace foxglove::asset {
    class AssetManager : public utils::Singleton<AssetManager> {
    public:
        /// Registers an handler of specified asset type
        template<typename AssetType, typename AssetHandler>
        void RegisterAssetHandler() {
            FXG_ASSERT(handlers_.find(typeid(AssetType)) == handlers_.end());
            handlers_[typeid(AssetType)] = std::make_unique<AssetHandler>(*this);
        }

        /**
         * Creates a new reference to the asset.
         * 
         * \param name Asset name
         * \param required_state Required asset state.
         */
        template<typename AssetType>
        AssetPtr<AssetType> GetAsset(const std::string& name, AssetState required_state = AssetState::Void) {
            FXG_ASSERT(handlers_.find(typeid(AssetType)) != handlers_.end());
            AssetPtr<GenericAsset> asset = handlers_[typeid(AssetType)]->GetAsset(name, required_state);
            return asset.Downcast<AssetType>();
        }

        /** Loads specified asset from disk if it's not yet loaded.
         *
         * \param asset_ptr Asset pointer
         */
        template<typename AssetType>
        void Load(AssetPtr<AssetType> asset_ptr) {
            FXG_ASSERT(handlers_.find(typeid(AssetType)) != handlers_.end());
            handlers_[typeid(AssetType)]->Load(asset_ptr.Upcast());
        }

        /** Initializes specified asset if it's not yet initialized.
         *
         * \param asset_ptr Asset pointer
         */
        template<typename AssetType>
        void Initialize(AssetPtr<AssetType> asset_ptr) {
            FXG_ASSERT(handlers_.find(typeid(AssetType)) != handlers_.end());
            handlers_[typeid(AssetType)]->Initialize(asset_ptr.Upcast());
        }

        /// Tries to load all void assets from disk
        void LoadAll() {
            for (auto& handler_pair : handlers_) {
                handler_pair.second->LoadAll();
            }
        }

        /// Tries to initialize all loaded but not initialized assets
        void InitializeAll() {
            for (auto& handler_pair : handlers_) {
                handler_pair.second->InitializeAll();
            }
        }

        void Precache() {
            LoadAll();
            InitializeAll();
        }

        /// Unloads assets that doesn't have any references
        void Cleanup() {
            for (auto& handler_pair : handlers_) {
                handler_pair.second->Cleanup();
            }
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<IAssetHandler>> handlers_;
    };
}
