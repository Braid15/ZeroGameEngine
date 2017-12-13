#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef uint32_t ComponentId;

    class EntityFactory;
    class Entity;

    class EntityComponent : public IZeroObject {
    private:
        friend class EntityFactory;
        std::shared_ptr<Entity> _owner;
    public:
        virtual ~EntityComponent() {}
        virtual const ComponentId& get_id() const = 0; 
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