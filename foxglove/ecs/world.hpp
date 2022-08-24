#pragma once

#include <typeindex>
#include <bitset>
#include <unordered_map>


#include <engine.hpp>
#include <ecs/ecs.hpp>
#include <ecs/events.hpp>
#include <ecs/component_array.hpp>

namespace foxglove::ecs {
    /// Thing that holds entities and owns their components
    class World {
    public:
        World() : registered_comp_count_(0), next_ent_id_(1) {}

        template<typename Component>
        void RegisterComponent() {
            FXG_ASSERT(comp_ids_.find(typeid(Component)) == comp_ids_.end());

            ComponentID comp_id = registered_comp_count_;
            comp_ids_[typeid(Component)] = comp_id;
            comp_arrays_[comp_id] = std::make_unique<ComponentArray<Component>>();

            registered_comp_count_++;
        }

        Entity CreateEntity();
        void DestroyEntity(Entity entity);

        template<typename Component>
        bool HasComponent(Entity entity) {
            ComponentID comp_id = comp_ids_[typeid(Component)];
            return ent_signatures_[entity][comp_id];
        }

        template<typename Component>
        Component& AddComponent(Entity entity) {
            FXG_ASSERT(!HasComponent<Component>(entity));

            ComponentID comp_id = comp_ids_[typeid(Component)];
            ComponentArray<Component>* component_array =
                static_cast<ComponentArray<Component>*>(comp_arrays_[comp_id].get());

            ent_signatures_[entity].set(comp_id, true);

            Component& comp = component_array->Add(entity);
            Engine::Instance()->events_->Emit(ComponentAddedEvent<Component>(entity));
            return comp;
        }

        template<typename Component>
        void RemoveComponent(Entity entity) {
            FXG_ASSERT(HasComponent<Component>(entity));

            ComponentID comp_id = comp_ids_[typeid(Component)];
            ComponentArray<Component>* component_array =
                static_cast<ComponentArray<Component>*>(comp_arrays_[comp_id].get());

            ent_signatures_[entity].set(comp_id, false);
            Component& comp = component_array->Remove(entity);
            Engine::Instance()->events_->Emit(ComponentRemovedEvent(entity));
            return comp;
        }

    private:
        std::unordered_map<std::type_index, ComponentID> comp_ids_;

        std::array<std::unique_ptr<IComponentArray>, MAX_COMPONENTS> comp_arrays_;
        std::unordered_map<Entity, std::bitset<MAX_COMPONENTS>> ent_signatures_;
        
        int registered_comp_count_;
        Entity next_ent_id_;
    };
}
