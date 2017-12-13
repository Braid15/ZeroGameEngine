#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef uint32_t EntityComponentId;
    extern const EntityComponentId INVALID_ENTITY_COMPONENT_ID;

    class EntityFactory;
    class Entity;
    class EntityComponent;

    typedef std::shared_ptr<Entity> StrongEntityPtr;
    typedef std::weak_ptr<Entity> WeakEntityPtr;
    typedef std::shared_ptr<EntityComponent> StrongEntityComponentPtr;
    typedef std::weak_ptr<EntityComponent> WeakEntityComponentPtr;

    class EntityComponent : public IZeroObject {
    private:
        friend class EntityFactory;
        std::shared_ptr<Entity> _owner;
    public:
        virtual ~EntityComponent() {}
        virtual const EntityComponentId& get_id() const = 0; 
        virtual StringRepr to_string() const = 0;
        virtual bool initialize() = 0;
        virtual void post_initialize() = 0;
        inline virtual void update(double delta_time) {}
    protected:
        inline std::shared_ptr<Entity> get_owner() const { return _owner; }
    private:
        inline void set_owner(std::shared_ptr<Entity> owner) { _owner = owner; }
    };
}