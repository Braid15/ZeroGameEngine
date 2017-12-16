#include "Entity.h"

namespace ZeroEngine {

    const EntityId INVALID_ENTITY_ID = 0;


    Entity::Entity(EntityId id) {
        _id = id;
        _name = "Entity_" + std::to_string(_id); 
    }

    Entity::Entity(EntityId id, std::string name) {
        _id = id;
        _name = name;
    }

    Entity::Entity(EntityId id, const char* name) {
        _id = id;
        _name = name;
    }

    Entity::~Entity() {
        // If not true then destroy was not called
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

    bool Entity::initialize() {
        bool success = true;
        return success;
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

    void Entity::add_component(EntityComponentPtr component) {
        std::pair<EntityComponentMap::iterator, bool> success = _components.insert(std::make_pair(component->get_id(), component));
        std::cout << "Component added to " << to_string() << ": " << ((success.second == true) ? "true." : "false.");
    }
}