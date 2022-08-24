#pragma once


#include <typeindex>
#include <string>
#include <unordered_map>
#include <utils/singleton.hpp>
#include <asset/asset.hpp>
#include <asset/handler_base.hpp>

namespace foxglove::asset {
    class AssetManager : public utils::Singleton<AssetManager> {
    public:
        /// Registers an handler of specified asset type
        template<typename AssetType, typename AssetHandler>
        void RegisterAssetHandler() {
            FXG_ASSERT(handlers_.find(typeid(AssetType)) == handlers_.end());
            handlers_[typeid(AssetType)] = std::make_unique<AssetHandler>();
        }

        /**
         * Creates a new reference to the asset. 
         * If the specified asset is not already present, behavior is determined by the prepare_now flag
         * 
         * \param name Asset name
         * \param prepare_now If true, loading and initializing the asset and its 
         * dependencies will be done immediately. Otherwise, reference to the new void asset is created.
         */
        template<typename AssetType>
        AssetPtr<AssetType> GetAsset(const std::string& name, bool prepare_now = false) {
            FXG_ASSERT(handlers_.find(typeid(AssetType)) != handlers_.end());
            AssetPtr<AssetBase> asset = handlers_[typeid(AssetType)]->GetAsset(name, prepare_now);
            return asset.Downcast<AssetType>();
        }

        /// Tries to load all void assets from disk
        void LoadAll() {
            for (auto& handler_pair : handlers_) {
                handler_pair.second->LoadAll();
            }
        }

        /// Initializes all loaded but not initialized assets
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
