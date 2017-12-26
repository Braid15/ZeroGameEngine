#pragma once

#include "../ZeroEngineStd.h"
#include "Entity.h"
#include "EntityComponent.h"
#include "../Utils/Xml/XmlReader.h"
#include "../Utils/Xml/XmlWriter.h"

namespace ZeroEngine {

    class EntityFactory : public IZeroObject {
    private:
        EntityId _last_id;

        // @TEMP: Hardcoding XML for now
        XmlReader _reader;
        XmlWriter _writer;
    public:
        EntityFactory() : _last_id(INVALID_ENTITY_ID) {}
        inline virtual StringRepr to_string() const override { return "EntityFactory"; }
        std::shared_ptr<Entity> create_entity();
        std::shared_ptr<Entity> create_entity(const char* resource_path);
        // modify_entity()
    protected:
        std::shared_ptr<EntityComponent> create_component();
    private:
        EntityId get_next_id();
    };
}