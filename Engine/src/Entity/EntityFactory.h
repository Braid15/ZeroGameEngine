#pragma once

#include "../ZeroEngineStd.h"
#include "Entity.h"
#include "EntityComponent.h"

namespace ZeroEngine {

    const EntityId INVALID_ENTITY_ID = 0;

    class EntityFactory : public IZeroObject {
    private:
        EntityId _last_id;
    public:
        EntityFactory() : _last_id(INVALID_ENTITY_ID) {}
        inline virtual StringRepr to_string() const override { return "EntityFactory"; }
        std::shared_ptr<Entity> create_entity();
        // modify_entity()
    protected:
        // create_component();
    private:
        EntityId get_next_id();
    };
}