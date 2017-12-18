#include "EntityFactory.h"

namespace ZeroEngine {

    // @TODO: Incomplete
    std::shared_ptr<Entity> EntityFactory::create_entity() {
        std::shared_ptr<Entity> entity(zero_new Entity(get_next_id()));
        entity->post_initialize();
        return entity;
    }

    EntityId EntityFactory::get_next_id() {
        ++_last_id;
        return _last_id;
    }
}