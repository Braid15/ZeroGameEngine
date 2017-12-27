#include "EntityFactory.h"
#include "Components\TransformComponent2D.h"
#include "Components\ScreenElementRenderComponent.h"
#include "Components\SpriteRenderComponent.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    EntityFactory::EntityFactory() {
        _last_id = INVALID_ENTITY_ID;

        _component_creation_map[std::string(TransformComponent2D::name)] = TransformComponent2D::create;
        _component_creation_map[std::string(ScreenElementRenderComponent::name)] = ScreenElementRenderComponent::create;
        _component_creation_map[std::string(SpriteRenderComponent::name)] = SpriteRenderComponent::create;
    }

    std::shared_ptr<Entity> EntityFactory::create_entity() {
        std::shared_ptr<Entity> entity(zero_new Entity(get_next_id()));
        entity->post_initialize();
        return entity;
    }

    std::shared_ptr<Entity> EntityFactory::create_entity(char* resource_path) {
        XmlReader reader;
        if (reader.load(resource_path)) {
            std::shared_ptr<Entity> entity(zero_new Entity(get_next_id()));

            reader.move_to_root_element();
            if (entity->initialize(reader)) {
                while (reader.move_to_next_element()) {
                    std::shared_ptr<EntityComponent> component = create_component(reader);
                    if (component) {
                        component->set_owner(entity);
                        entity->add_component(component);
                    }
                }
                entity->post_initialize();
                return entity;
            } else {
                LOG_DEBUG("EntityFactory", "Error initializing entity");
            }
        }
        return std::shared_ptr<Entity>();
    }

    std::shared_ptr<Entity> EntityFactory::create_entity(std::string resource_path) {
        return create_entity(const_cast<char*>(resource_path.c_str()));
    }

    std::shared_ptr<EntityComponent> EntityFactory::create_component(const XmlReader& reader) {
        auto iter = _component_creation_map.find(std::string(reader.get_element_name()));
        if (iter == _component_creation_map.end()) return std::shared_ptr<EntityComponent>();
        std::shared_ptr<EntityComponent> component(_component_creation_map[std::string(reader.get_element_name())]());
        if (component) {
            if (component->initialize(reader)) {
                return component;
            } else {
                LOG_DEBUG("EntityFactory", "Error initializing component " + std::string(component->get_name()));
            }
        } else {
            LOG_DEBUG("EntityFactory" , "Error finding component named " + std::string(component->get_name()));
        }

        return std::shared_ptr<EntityComponent>();
    }

    EntityId EntityFactory::get_next_id() {
        ++_last_id;
        return _last_id;
    }
}