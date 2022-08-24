#pragma once

#include <ecs/ecs.hpp>

/**
 * Entity-component subsystem-related events
 */

namespace foxglove::ecs {
    template<typename ComponentType>
    struct ComponentAddedEvent {
        ComponentAddedEvent(Entity entity) : entity_(entity) {}
        Entity entity_;
    };

    struct ComponentRemovedEvent {
        ComponentRemovedEvent(Entity entity) : entity_(entity) {}
        Entity entity_;
    };

    struct EntityDestroyedEvent {
        EntityDestroyedEvent(Entity entity) : entity_(entity) {}
        Entity entity_;
    };
}
