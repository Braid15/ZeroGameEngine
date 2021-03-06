#include "Entity.h"
#include "../Utils/Xml/XmlWriter.h"

namespace ZeroEngine {

    const EntityId INVALID_ENTITY_ID = 0;


    Entity::Entity(EntityId id) {
        _id = id;
        _transform_type = "Unknown";
        _resource_path = "Unknown";
        _name = "Entity_" + std::to_string(_id); 
    }

    Entity::Entity(EntityId id, std::string name) {
        _id = id;
        _transform_type = "Unknown";
        _resource_path = "Unknown";
        _name = name;
    }

    Entity::Entity(EntityId id, const char* name) {
        _id = id;
        _name = name;
    }

    Entity::~Entity() {
        // If components isn't empty then destroy was not called
        assert(_components.empty() == true);
    }

    StringRepr Entity::to_string() const {
        std::string ret_str;
        ret_str += "[Entity] - Name: ";
        ret_str += _name;
        ret_str += " Id: ";
        ret_str += std::to_string(_id);
        return ret_str.c_str();
    }

    bool Entity::initialize(const XmlReader& reader) {
        assert(strcmp(reader.get_element_name(), "Entity") == 0);
        _transform_type = reader.get_element_attribute_value("type");
        _resource_path = reader.get_element_attribute_value("resource");
        return true;
    }

    void Entity::post_initialize() {
        for (EntityComponentMap::iterator it = _components.begin(); it != _components.end(); ++it) {
            it->second->post_initialize();
        }
    }

    void Entity::destroy() {
        _components.clear();
    }

    void Entity::update(Tick delta_time) {
        for (EntityComponentMap::iterator it = _components.begin(); it != _components.end(); ++it) {
            it->second->update(delta_time);
        }
    }

    std::string Entity::create_xml_string() {
        XmlWriter writer;
        writer.write_start_element("Entity");
        writer.write_start_attribute("type");
        writer.write_string(_transform_type.c_str());
        writer.write_end_attribute();
        writer.write_start_attribute("resource");
        writer.write_string(_resource_path.c_str());
        writer.write_end_attribute();

        for (auto iter = _components.begin(); iter != _components.end(); ++iter) {
            iter->second->on_write_xml(writer);
        }

        writer.write_end_element();

        return writer.get_xml_string();
    }

    void Entity::add_component(EntityComponentPtr component) {
        std::pair<EntityComponentMap::iterator, bool> success = _components.insert(std::make_pair(component->get_id(), component));

        if (!success.second) {
            LOG_DEBUG("Entity", "Error adding component");
        }
    }
}