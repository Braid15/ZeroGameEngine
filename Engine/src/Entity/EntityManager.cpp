#include "EntityManager.h"
#include "../Math/MathTypes.h"

namespace ZeroEngine {

    EntityManager::EntityManager() {
        _storage = zero_new StlMapEntityStorage();
        _factory = zero_new EntityFactory();
    }

    EntityManager::~EntityManager() {
        zero_delete(_storage);
        zero_delete(_factory);
    }

    bool EntityManager::initialize() {
        return true;
    }

    bool EntityManager::shutdown() {
        return true;
    }

    void EntityManager::update_entities(Tick delta_time) {
        UpdateFilter filter;
        filter.delta_time = delta_time;
        _storage->filter_entities(&filter);
    }

    EntityPtr EntityManager::create_entity() {
        EntityPtr entity = _factory->create_entity();
        _storage->store_entity(entity);
        return entity;
    }

    EntityPtr EntityManager::create_entity(char* resource_path) {
        EntityPtr entity = _factory->create_entity(resource_path);
        _storage->store_entity(entity);
        return entity;
    }

    EntityPtr EntityManager::create_entity(std::string resource_path) {
        EntityPtr entity = _factory->create_entity(resource_path);
        _storage->store_entity(entity);
        return entity;
    }

    EntityPtr EntityManager::create_entity(std::string path, Vector3 pos) {
        EntityPtr entity = _factory->create_entity(path, pos);
        _storage->store_entity(entity);
        return entity;
    }

    void EntityManager::destroy_entity(const EntityId& id) {
        _storage->destroy_entity(id);
    }

    void EntityManager::get_all_entity_id(std::list<EntityId>* list) {
        _storage->get_all_entity_id(list);
    }

    WeakEntityPtr EntityManager::get_entity(const EntityId& id) {
        return _storage->retrieve_entity(id);
    }

    // ----------------------------------
    // EntityManager::StlMapEntityStorage
    // ----------------------------------

    EntityManager::StlMapEntityStorage::~StlMapEntityStorage() {
        _entities.clear();
    }

    WeakEntityPtr EntityManager::StlMapEntityStorage::retrieve_entity(const EntityId& id) {
        EntityMap::iterator iter = _entities.find(id);
        if (iter != _entities.end()) {
            return iter->second;
        }
        return WeakEntityPtr();
    }

    void EntityManager::StlMapEntityStorage::store_entity(EntityPtr entity) {
        _entities.insert(std::pair<EntityId, EntityPtr>(entity->get_id(), entity));
    }

    void EntityManager::StlMapEntityStorage::destroy_entity(const EntityId& id) {
        EntityMap::iterator iter = _entities.find(id);
        if (iter != _entities.end()) {
            iter->second->destroy();
            _entities.erase(iter);
        } else {
            LOG_DEBUG("EntityManager", "Unable to delete entity")
        }
    }

    void EntityManager::StlMapEntityStorage::get_all_entity_id(std::list<EntityId>* list) {
        for (EntityMap::iterator iter = _entities.begin(); iter != _entities.end(); iter++) {
            list->push_back(iter->first);
        }
    }

    void EntityManager::StlMapEntityStorage::filter_entities(IFilter* filter) {
        for (EntityMap::iterator iter = _entities.begin(); iter != _entities.end(); iter++) {
            filter->on_filter(iter->second);
        }
    }

    Uint32 EntityManager::StlMapEntityStorage::get_entity_count() const {
        return static_cast<Uint32>(_entities.size());
    }
}