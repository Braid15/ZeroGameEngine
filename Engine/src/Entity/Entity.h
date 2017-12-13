#pragma once

#include "../ZeroEngineStd.h"
#include "EntityComponent.h"

namespace ZeroEngine {

    typedef uint32_t EntityId;

    class EntityFactory;

    class Entity : public IZeroObject {
        typedef std::map<ComponentId, std::shared_ptr<EntityComponent>> ComponentMap;
    private:
        friend class EntityFactory;
        EntityId _id;
        std::string _name;
        ComponentMap _components;
    public:
        explicit Entity(EntityId id);
        explicit Entity(EntityId id, std::string name);
        explicit Entity(EntityId id, const char* name);
        virtual ~Entity();
        virtual StringRepr to_string() const override;
        inline const EntityId& get_id() const { return _id; }
        inline const std::string& get_name() const { return _name; }
        inline void set_name(const char* name) { _name = name; }
        inline void set_name(std::string name) { _name = name; }
        bool initialize();
        void post_initialize();
        void destroy();
        void update(double delta_time);
        template <class ComponentType>
        inline std::weak_ptr<ComponentType> get_component(ComponentId id) {
            ComponentMap::iterator iter = _components.find(id);
            if (iter != _components.end()) {
                std::shared_ptr<EntityComponent> base_class_component(iter->second);
                std::shared_ptr<ComponentType> sub_class_component(std::static_pointer_cast<ComponentType>(base_class_component));
                std::weak_ptr<ComponentType> ret_ptr(sub_class_component);
                return ret_ptr;
            }
            return weak_ptr<ComponentType>();
        }
    private:
        // should only be called by EntityFactory
        void add_component(std::shared_ptr<EntityComponent>);
    };
}