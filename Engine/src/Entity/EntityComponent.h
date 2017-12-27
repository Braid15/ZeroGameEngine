#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Utils/Xml/XmlReader.h"

namespace ZeroEngine {

    typedef uint32_t EntityComponentId;
    extern const EntityComponentId INVALID_ENTITY_COMPONENT_ID;

    class XmlWriter;
    class EntityFactory;
    class Entity;
    class EntityComponent;

    typedef std::shared_ptr<Entity> EntityPtr;
    typedef std::weak_ptr<Entity> WeakEntityPtr;
    typedef std::shared_ptr<EntityComponent> EntityComponentPtr;
    typedef std::weak_ptr<EntityComponent> WeakEntityComponentPtr;

    class EntityComponent : public IZeroObject {
    private:
        friend class EntityFactory;
        friend class Entity;
        EntityPtr _owner;
    public:
        virtual ~EntityComponent() {}
        virtual const EntityComponentId& get_id() const = 0; 
        virtual const char* get_name() const = 0;
        virtual StringRepr to_string() const = 0;
        virtual bool initialize(const XmlReader&) = 0;
        virtual void post_initialize() = 0;
        inline virtual void update(Tick delta_time) {}

        // @@TODO: IMPLEMENT
        // static const EntityComponentId get_id_from_name(const char* name);
        // static const EntityComponentId get_id_from_name(const std::string& name);
    protected:
        inline WeakEntityPtr get_owner() const { return WeakEntityPtr(_owner); }
    private:
        inline void set_owner(EntityPtr owner) { _owner = owner; }
        virtual void on_write_xml(const XmlWriter& writer) = 0;
    };
}