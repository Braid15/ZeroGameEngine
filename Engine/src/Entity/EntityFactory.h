#pragma once

#include "../ZeroEngineStd.h"
#include "Entity.h"
#include "EntityComponent.h"
#include "../Utils/Xml/XmlReader.h"
#include "../Utils/Xml/XmlWriter.h"

namespace ZeroEngine {

    class Vector3;

    typedef EntityComponent* (*entity_component_creation_delegate)();

    class EntityFactory : public IZeroObject {
    private:
        EntityId _last_id;
        std::map<std::string, entity_component_creation_delegate> _component_creation_map;

        // @TEMP: Hardcoding XML for now
        XmlReader _reader;
        XmlWriter _writer;
    public:
        EntityFactory();
        inline virtual StringRepr to_string() const override { return "EntityFactory"; }
        std::shared_ptr<Entity> create_entity();
        std::shared_ptr<Entity> create_entity(char* resource_path);
        std::shared_ptr<Entity> create_entity(std::string resource_path);
        std::shared_ptr<Entity> create_entity(std::string resource_path, Vector3 pos);
        // modify_entity()
    protected:
        std::shared_ptr<EntityComponent> create_component(const XmlReader&);
    private:
        EntityId get_next_id();
    };
}