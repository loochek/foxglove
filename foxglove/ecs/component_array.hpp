#pragma once

#include <vector>
#include <unordered_map>

#include <core/event_bus.hpp>
#include <ecs/ecs.hpp>

namespace foxglove::ecs {
    class IComponentArray {
    public:
        virtual ~IComponentArray() {}
        virtual void Remove(Entity entity) = 0;
    };

    /// Associative container that holds components of specified type
    template<typename Component>
    class ComponentArray : public IComponentArray {
    public:
        ComponentArray() = default;
        ~ComponentArray() = default;
        
        Component& Get(Entity entity) const {
            int idx = GetIdx(entity);
            FXG_ASSERT(idx != -1);

            return components_[idx];
        }

        Component& Add(Entity entity) {
            FXG_ASSERT(GetIdx(entity) == -1);

            int idx = components_.size();
            idx2ent_[idx] = entity;
            ent2idx_[entity] = idx;

            components_.emplace_back();
            return components_[idx];
        }

        virtual void Remove(Entity entity) override {
            int last_idx = components_.size() - 1;
            int idx = GetIdx(entity);
            FXG_ASSERT(idx != -1);

            ent2idx_.erase(entity);
            if (idx == last_idx) {
                idx2ent_.erase(idx);
            } else {
                // Move last component in array into gap
                Entity last_idx_ent = idx2ent_[last_idx];
                components_[idx] = std::move(components_[last_idx]);
                ent2idx_[last_idx_ent] = idx;
                idx2ent_.erase(last_idx);
                idx2ent_[idx] = entity;
            }

            components_.pop_back();
        }

    private:
        int GetIdx(Entity entity) const {
            if (ent2idx_.find(entity) == ent2idx_.end())
                return -1;
                
            /// TODO: why not []?
            return ent2idx_.at(entity);
        }

    private:
        std::vector<Component> components_;

        std::unordered_map<int, Entity> idx2ent_;
        std::unordered_map<Entity, int> ent2idx_;
    };
}
