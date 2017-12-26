#include "EntityFactory.h"
#include "Components\TransformComponent2D.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    // @TODO: Incomplete
    std::shared_ptr<Entity> EntityFactory::create_entity() {
        std::shared_ptr<Entity> entity(zero_new Entity(get_next_id()));
        entity->add_component(std::shared_ptr<EntityComponent>(zero_new TransformComponent2D()));
        entity->post_initialize();
        return entity;
    }

    std::shared_ptr<Entity> EntityFactory::create_entity(const char* resource_path) {
        LOG_UNIMPLEMENTED();
        return std::shared_ptr<Entity>();
    }

    std::shared_ptr<EntityComponent> EntityFactory::create_component() {
        LOG_UNIMPLEMENTED();
        return std::shared_ptr<EntityComponent>();
    }

    EntityId EntityFactory::get_next_id() {
        ++_last_id;
        return _last_id;
    }
}