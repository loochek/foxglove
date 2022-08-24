#pragma once

#include <vector>
#include <string>
#include <utils/assert.hpp>

namespace foxglove::asset {
    enum class AssetState {
        Void,
        Uninitialized,
        ReadyToUse
    };

    struct AssetBase {
        AssetBase() : state(AssetState::Void), ref_counter(0) {}

        AssetState state;
        int ref_counter;
    };

    template<typename AssetType>
    class AssetPtr {
        friend class AssetManager;

    public:
        AssetPtr() : asset_(nullptr) {}

        AssetPtr(AssetBase* asset) : asset_(asset) {
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
            FXG_ASSERT(asset_ != nullptr);
            FXG_ASSERT(asset_->state == AssetState::ReadyToUse);
            return *Access();
        }

        const AssetType* operator->() {
            FXG_ASSERT(asset_ != nullptr);
            FXG_ASSERT(asset_->state == AssetState::ReadyToUse);
            return Access();
        }

        // Must be implemented for each asset type
        const AssetType* Access();

        /// Upcasting
        template<typename AssetType_>
        AssetPtr<AssetBase> Upcast() {
            return AssetPtr<AssetBase>(asset_);
        }

    private:
        /// Downcasting. Used by AssetManager
        template<typename AssetType_>
        AssetPtr<AssetType_> Downcast() {
            static_assert(std::is_same_v<AssetType, AssetBase>,
                "Downcasting should be applied only for pointer to the base asset");
            return AssetPtr<AssetType_>(asset_);
        }

        void Swap(AssetPtr& other) {
            std::swap(asset_, other.asset_);
        }

    private:
        AssetBase* asset_;
    };
};
