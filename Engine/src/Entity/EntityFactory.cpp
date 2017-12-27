#include "EntityFactory.h"
#include "Components\TransformComponent2D.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    EntityFactory::EntityFactory() {
        _last_id = INVALID_ENTITY_ID;
        _component_creation_map[std::string(TransformComponent2D::name)] = TransformComponent2D::create;

    }

    std::shared_ptr<Entity> EntityFactory::create_entity() {
        std::shared_ptr<Entity> entity(zero_new Entity(get_next_id()));
        entity->add_component(std::shared_ptr<EntityComponent>(zero_new TransformComponent2D()));
        entity->post_initialize();
        return entity;
    }

    std::shared_ptr<Entity> EntityFactory::create_entity(char* resource_path) {
        XmlReader reader;
        if (reader.load(resource_path)) {
            std::shared_ptr<Entity> entity(zero_new Entity(get_next_id()));
            reader.move_to_root_element();
            entity->set_type(reader.get_element_attribute_value("type"));
            entity->set_resource_path(reader.get_element_attribute_value("resource"));

            while (reader.move_to_next_element()) {
                std::shared_ptr<EntityComponent> component = create_component(reader);
                if (component) {
                    std::cout << component->get_name() << "\n";
                    entity->add_component(component);
                }
            }

            return entity;
        }
        return std::shared_ptr<Entity>();
    }

    std::shared_ptr<Entity> EntityFactory::create_entity(std::string resource_path) {
        return create_entity(const_cast<char*>(resource_path.c_str()));
    }

    std::shared_ptr<EntityComponent> EntityFactory::create_component(const XmlReader& reader) {
        auto iter = _component_creation_map.find(std::string(reader.get_element_name()));
        if (iter == _component_creation_map.end()) return std::shared_ptr<EntityComponent>();

        return std::shared_ptr<EntityComponent>(_component_creation_map[std::string(reader.get_element_name())](reader));
    }

    EntityId EntityFactory::get_next_id() {
        ++_last_id;
        return _last_id;
    }
}