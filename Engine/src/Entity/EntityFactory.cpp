#include "EntityFactory.h"
#include "Components\SpriteRenderComponent.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    using std::make_shared;

    EntityFactory::EntityFactory() {
        _last_id = invalid_entity_id();

        // @TODO: WOuld like to use entity id instead of name, but the code that uses this map is currently
        // putting in the component types name from the xml file
        _component_creation_map[std::string(TextureRenderComponent_2D::name)] = TextureRenderComponent_2D::create;
    }

    std::shared_ptr<Entity> EntityFactory::create_entity() {
        std::shared_ptr<Entity> entity = make_shared<Entity>(get_next_id());
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

    // @TODO: This is temporary. Need to pass in entity transform instead of reading it from file
    std::shared_ptr<Entity> EntityFactory::create_entity(std::string path, Vector3 pos) {
        XmlReader reader;
        char* resource_path = const_cast<char*>(path.c_str());
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

                LOG_TODO("EntityFactory", "REFACTOR THIS!");
                entity->get_transform().set_position(pos);

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