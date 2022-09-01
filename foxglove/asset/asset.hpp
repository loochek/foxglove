#pragma once

#include <vector>
#include <string>
#include <utils/assert.hpp>

namespace foxglove::asset {
    enum class AssetState {
        /**
         * Asset that not yet loaded and initialized (therefore can't be used).
         * Makes possible to create references to the assets and load, then initialize all assets at once
         * (displaying cute loading screen at the time)
         */
        Void,

        /// Asset which data has already loaded into RAM
        Uninitialized,

        /// Fully prepared asset
        ReadyToUse
    };

    // Dummy type used by AssetPtr to represent a pointer to any asset
    struct GenericAsset {};

    struct AssetBase {
        std::string name;
        AssetState state;
        int ref_counter;

        AssetBase() = delete;
        explicit AssetBase(std::string name) : name(std::move(name)), state(AssetState::Void), ref_counter(0) {}
    };

    template<typename AssetType>
    class AssetPtr {
        friend class AssetManager;

    public:
        AssetPtr() : asset_(nullptr) {}

        explicit AssetPtr(AssetBase* asset) : asset_(asset) {
            if (asset_ != nullptr) {
                asset_->ref_counter++;
            }
        }

        ~AssetPtr() {
            if (asset_ != nullptr) {
                asset_->ref_counter--;
            }
        }

        AssetPtr(const AssetPtr& other) : asset_(other.asset_) {
            if (other.asset_ != nullptr) {
                other.asset_->ref_counter++;
            }
        }

        AssetPtr(AssetPtr&& other) : asset_(other.asset_) {
            other.asset_ = nullptr;
        }

        AssetPtr& operator=(const AssetPtr& other) {
            if (this != &other) {
                AssetPtr(other).Swap(*this);
            }

            return *this;
        }

        AssetPtr& operator=(AssetPtr&& other) {
            if (this != &other) {
                AssetPtr(std::move(other)).Swap(*this);
            }

            return *this;
        }

        const AssetType& operator*() {
            return *Get();
        }

        const AssetType* operator->() {
            return Get();
        }

        const AssetType* Get() {
            FXG_ASSERT(asset_ != nullptr);
            FXG_ASSERT(asset_->state == AssetState::ReadyToUse);
            return Access();
        }

        // Must be implemented for each asset type
        const AssetType* Access();

        /// Upcasting
        AssetPtr<GenericAsset> Upcast() {
            return AssetPtr<GenericAsset>(asset_);
        }

        AssetBase* GetInternalAsset() const {
            return asset_;
        }

    private:
        /// Downcasting. Used by AssetManager
        template<typename AssetType_>
        AssetPtr<AssetType_> Downcast() {
            static_assert(std::is_same_v<AssetType, GenericAsset>,
                "Downcasting should be applied only for pointer to the generic asset");
            return AssetPtr<AssetType_>(asset_);
        }

        void Swap(AssetPtr& other) {
            std::swap(asset_, other.asset_);
        }

    private:
        AssetBase* asset_;
    };
};
