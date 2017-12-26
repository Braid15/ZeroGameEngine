#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "EntityComponent.h"

namespace ZeroEngine {

    typedef uint32_t EntityId;
    extern const EntityId INVALID_ENTITY_ID;

    class EntityFactory;

    class Entity : public IZeroObject {
        typedef std::map<EntityComponentId, EntityComponentPtr> EntityComponentMap;
    private:
        friend class EntityFactory;
        EntityId _id;
        std::string _name;
        EntityComponentMap _components;
    public:
        explicit Entity(EntityId id);
        explicit Entity(EntityId id, std::string name);
        explicit Entity(EntityId id, const char* name);
        virtual ~Entity();
        virtual StringRepr to_string() const override;
        bool initialize();
        void post_initialize();
        void destroy();
        void update(Tick delta_time);
        inline const EntityId& get_id() const { return _id; }
        inline const std::string& get_name() const { return _name; }
        inline void set_name(const char* name) { _name = name; }
        inline void set_name(std::string name) { _name = name; }
        inline const EntityComponentMap* get_components() const { return &_components; }

        template <class ComponentType>
        inline std::weak_ptr<ComponentType> get_component(const EntityComponentId id) {
            EntityComponentMap::iterator iter = _components.find(id);
            if (iter != _components.end()) {
                EntityComponentPtr base_class_component(iter->second);
                std::shared_ptr<ComponentType> sub_class_component(std::static_pointer_cast<ComponentType>(base_class_component));
                std::weak_ptr<ComponentType> ret_ptr(sub_class_component);
                return ret_ptr;
            }
            return weak_ptr<ComponentType>();
        }

        // @@TODO: These methods rely on EntityComponent::get_id_from_name() which is not yet implemented
        //
        // template <class ComponentType>
        // inline std::weak_ptr<ComponentType> get_component(const std::string& name) {
        //     const EntityComponentId id = EntityComponent::get_id_from_name(name);
        //     return get_component(id);
        // }

        // template <class ComponentType>
        // inline std::weak_ptr<ComponentType> get_component(const char* name) {
        //     const EntityComponentId id = EntityComponent::get_id_from_name(name);
        //     return get_component(id);
        // }

    private:
        // should only be called by EntityFactory
        void add_component(EntityComponentPtr);
    };
}