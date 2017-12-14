#pragma once 

#include "ZeroEngineStd.h"
#include "Events/Events.h"
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"

namespace ZeroEngine {

    //
    // RequestDestroyEntityEvent
    //

    class RequestDestroyEntityEvent : public BaseEventData {
    private:
        const EntityId _entity_id;
    public:
        typedef std::shared_ptr<RequestDestroyEntityEvent> ptr;
        static const EventType type;
    public:
        inline RequestDestroyEntityEvent(const EntityId& id) : _entity_id(id) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "RequestDestroyEntityEvent"; }
        inline const EntityId& get_entity_id() const { return _entity_id; }
        static RequestDestroyEntityEvent::ptr create(const EntityId& id);
        static RequestDestroyEntityEvent::ptr cast(IEventDataPtr);
    };

    //
    // EntityDestroyedEvent
    //

    class EntityDestroyedEvent : public BaseEventData {
    private:
        const EntityId _entity_id;
    public:
        typedef std::shared_ptr<EntityDestroyedEvent> ptr;
        static const EventType type;
    public:
        inline EntityDestroyedEvent(const EntityId& id) : _entity_id(id) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "EntityDestroyedEvent"; }
        inline const EntityId& get_entity_id() const { return _entity_id; }
        static EntityDestroyedEvent::ptr create(const EntityId& id);
        static EntityDestroyedEvent::ptr cast(IEventDataPtr);
    };

    //
    // RequestCreateEntityEvent
    //

    class RequestCreateEntityEvent : public BaseEventData {
    public:
        typedef std::shared_ptr<RequestCreateEntityEvent> ptr;
        static const EventType type;
    public:
        inline RequestCreateEntityEvent() {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "RequestCreateEntityEvent"; }
        static RequestCreateEntityEvent::ptr create();
        static RequestCreateEntityEvent::ptr cast(IEventDataPtr);
    };

    //
    // EntityCreatedEvent
    //

    class EntityCreatedEvent : public BaseEventData {
    private:
        const EntityId _entity_id;
    public:
        typedef std::shared_ptr<EntityCreatedEvent> ptr;
        static const EventType type;
    public:
        inline EntityCreatedEvent(const EntityId& entity_id) : _entity_id(entity_id) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "EntityCreatedEvent"; }
        inline const EntityId& get_entity_id() const { return _entity_id; }
        static EntityCreatedEvent::ptr create(const EntityId& id);
        static EntityCreatedEvent::ptr cast(IEventDataPtr);
    };


    //
    // MoveEntityEvent
    //

    class MoveEntityEvent : public BaseEventData {
    private:
        // @TODO: This needs to be changed to somehting more less specific
        const Point<float> _new_location;
    public:
        typedef std::shared_ptr<MoveEntityEvent> ptr;
        static const EventType type;
    public:
        inline MoveEntityEvent(const Point<float> new_location) : _new_location(new_location) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "MoveEntityEvent"; }
        static MoveEntityEvent::ptr create(const Point<float> new_location);
        static MoveEntityEvent::ptr cast(IEventDataPtr);
    };

}