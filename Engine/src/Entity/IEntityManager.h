#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "EntityComponent.h"

namespace ZeroEngine {

    class IEntityManager : public IZeroObject {
    public:
        virtual bool initialize() = 0;
        virtual bool shutdown() = 0;
        virtual void update_entities(Tick delta_time) = 0;
        virtual EntityPtr create_entity() = 0;
        virtual uint32_t get_entity_count() const = 0;
        virtual void destroy_entity(const EntityId&) = 0;
        virtual WeakEntityPtr get_entity(const EntityId& entity_id) = 0;
        virtual StringRepr to_string() const = 0;
        virtual ~IEntityManager() {}
    };

    class NullEntityManager : public IEntityManager {
    public:
        inline bool initialize() override { return true; }
        inline bool shutdown() override { return true; }
        inline void update_entities(Tick delta_time) override {}
        inline uint32_t get_entity_count() const { return 0; }
        inline EntityPtr create_entity() override { return EntityPtr(); }
        inline WeakEntityPtr get_entity(const EntityId& entity_id) override { return WeakEntityPtr(); }
        inline void destroy_entity(const EntityId& entity_id) override {}
        inline StringRepr to_string() const { return "NullEntityManager"; }
    };
}