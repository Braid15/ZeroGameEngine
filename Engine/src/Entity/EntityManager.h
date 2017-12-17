#pragma once

#include "../ZeroEngineStd.h"
#include "IEntityManager.h"

namespace ZeroEngine {
    
    class EntityManager : public IEntityManager {
    private:
        class IEntityStorage;
        IEntityStorage* _storage;
        EntityFactory* _factory;
    public:
        EntityManager();
        ~EntityManager();
        bool initialize() override;
        bool shutdown() override;
        void update_entities(Tick delta_time) override;
        EntityPtr create_entity() override;
        void destroy_entity(const EntityId&) override;
        WeakEntityPtr get_entity(const EntityId&) override;
        inline uint32_t get_entity_count() const { return _storage->get_entity_count(); }
        inline StringRepr to_string() const override { return "EntityManager"; }
    private:
        struct IFilter {
            virtual void on_filter(EntityPtr) = 0;
        };

        struct UpdateFilter : public IFilter {
            Tick delta_time = -1;
            inline void on_filter(EntityPtr entity) override {
                assert(delta_time != -1);
                entity->update(delta_time);
            }
        };

        class IEntityStorage {
        public:
            virtual WeakEntityPtr retrieve_entity(const EntityId&) = 0;
            virtual void store_entity(EntityPtr) = 0;
            virtual void destroy_entity(const EntityId&) = 0;
            virtual void filter_entities(IFilter*) = 0;
            virtual uint32_t get_entity_count() const = 0;
            inline virtual ~IEntityStorage() {}
        };

        // @TODO: Factor this out of ENtityMangager so that user
        // can change implementation
        class StlMapEntityStorage : public IEntityStorage {
        private:
            typedef std::map<EntityId, EntityPtr> EntityMap;
            EntityMap _entities;
        public:
            inline StlMapEntityStorage() {}
            ~StlMapEntityStorage();
            WeakEntityPtr retrieve_entity(const EntityId& id) override;
            void store_entity(EntityPtr entity) override;
            void destroy_entity(const EntityId& id) override;
            void filter_entities(IFilter*) override;
            uint32_t get_entity_count() const override;
        };
    };
}