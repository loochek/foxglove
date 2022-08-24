#include "world.hpp"

namespace foxglove::ecs {
    Entity World::CreateEntity() {
        ent_signatures_[next_ent_id_] = 0;
        return next_ent_id_++;
    }

    void World::DestroyEntity(Entity entity) {
        auto sig = ent_signatures_[entity];
        for (ComponentID id = 0; id < registered_comp_count_; id++) {
            if (sig[id]) {
                comp_arrays_[id]->Remove(entity);
            }
        }

        ent_signatures_.erase(entity);
        Engine::Instance()->events_->Emit(EntityDestroyedEvent(entity));
    }
}
