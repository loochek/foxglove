#pragma once

#include <ecs/ecs.hpp>

/**
 * Entity-component subsystem-related events
 */

namespace foxglove::ecs {
    template<typename ComponentType>
    struct ComponentAddedEvent {
        explicit ComponentAddedEvent(Entity entity) : entity_(entity) {}
        Entity entity_;
    };

    struct ComponentRemovedEvent {
        explicit ComponentRemovedEvent(Entity entity) : entity_(entity) {}
        Entity entity_;
    };

    struct EntityDestroyedEvent {
        explicit EntityDestroyedEvent(Entity entity) : entity_(entity) {}
        Entity entity_;
    };
}
