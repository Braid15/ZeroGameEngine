#pragma once 

#include "ZeroEngineStd.h"
#include "Events/Events.h"
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Process\Process.h"

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
    private:
        EntityCreatedEvent();
        EntityCreatedEvent(const EntityCreatedEvent&);
    };


    //
    // MoveEntityEvent
    //

    class MoveEntityEvent : public BaseEventData {
    private:
        // @TODO: This needs to be changed to somehting more less specific
        const Point<float> _new_location;
        const EntityId _entity_id;
    public:
        typedef std::shared_ptr<MoveEntityEvent> ptr;
        static const EventType type;
    public:
        inline MoveEntityEvent(const EntityId id, const Point<float> new_location) : 
            _entity_id(id), _new_location(new_location) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "MoveEntityEvent"; }
        static MoveEntityEvent::ptr create(const EntityId id, const Point<float> new_location);
        static MoveEntityEvent::ptr cast(IEventDataPtr);
        inline const EntityId& get_entity_id() const { return _entity_id; }
        inline const Point<float> get_new_location() const { return _new_location; }
    private:
        MoveEntityEvent();
        MoveEntityEvent(const MoveEntityEvent&);
    };

    //
    // AttachProcessEvent
    //

    // Used for sending a process to be attached to the game logic from the game view
    class AttachProcessEvent : public BaseEventData {
    private:
        Process::ptr _process;
    public:
        typedef std::shared_ptr<AttachProcessEvent> ptr;
        static const EventType type;
    public:
        inline explicit AttachProcessEvent(Process::ptr process) : _process(process) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "AttachProcessEvent"; }
        static AttachProcessEvent::ptr create(Process::ptr process);
        static AttachProcessEvent::ptr cast(IEventDataPtr);
        inline Process::ptr get_process() const { return _process; }
    private:
        inline AttachProcessEvent() {}
        inline AttachProcessEvent(const AttachProcessEvent&) {}
    };

}