#include "ZeroEngineEvents.h"

namespace ZeroEngine {
    
    //
    // RequestDestroyEntityEvent
    //

    const EventType RequestDestroyEntityEvent::type = 0x6cf99d0;

    IEventDataPtr RequestDestroyEntityEvent::copy() const {
        return IEventDataPtr(zero_new RequestDestroyEntityEvent(_entity_id));
    }

    RequestDestroyEntityEvent::ptr RequestDestroyEntityEvent::create(const EntityId& id) {
        return RequestDestroyEntityEvent::ptr(zero_new RequestDestroyEntityEvent(id));
    }

    RequestDestroyEntityEvent::ptr RequestDestroyEntityEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == RequestDestroyEntityEvent::type);
        return std::static_pointer_cast<RequestDestroyEntityEvent>(data_ptr);
    }

    //
    // EntityDestroyedEvent
    //

    const EventType EntityDestroyedEvent::type = 0x616cced;

    IEventDataPtr EntityDestroyedEvent::copy() const {
        return IEventDataPtr(zero_new EntityDestroyedEvent(_entity_id));
    }

    EntityDestroyedEvent::ptr EntityDestroyedEvent::create(const EntityId& id) {
        return EntityDestroyedEvent::ptr(zero_new EntityDestroyedEvent(id));
    }

    EntityDestroyedEvent::ptr EntityDestroyedEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == EntityDestroyedEvent::type);
        return std::static_pointer_cast<EntityDestroyedEvent>(data_ptr);
    }

    //
    // RequestCreateEntityEvent
    //

    const EventType RequestCreateEntityEvent::type = 0x817a4c4e;

    IEventDataPtr RequestCreateEntityEvent::copy() const {
        return IEventDataPtr(zero_new RequestCreateEntityEvent());
    }

    RequestCreateEntityEvent::ptr RequestCreateEntityEvent::create() {
        return RequestCreateEntityEvent::ptr(zero_new RequestCreateEntityEvent());
    }

    RequestCreateEntityEvent::ptr RequestCreateEntityEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == RequestCreateEntityEvent::type);
        return std::static_pointer_cast<RequestCreateEntityEvent>(data_ptr);
    }

    //
    // EntityCreatedEvent
    //

    const EventType EntityCreatedEvent::type = 0xa7d61b3c;

    IEventDataPtr EntityCreatedEvent::copy() const {
        return IEventDataPtr(zero_new EntityCreatedEvent(_entity_id));
    }

    EntityCreatedEvent::ptr EntityCreatedEvent::create(const EntityId& id) {
        return EntityCreatedEvent::ptr(zero_new EntityCreatedEvent(id));
    }

    EntityCreatedEvent::ptr EntityCreatedEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == EntityCreatedEvent::type);
        return std::static_pointer_cast<EntityCreatedEvent>(data_ptr);
    }

    //
    // MoveEntityEvent
    //

    const EventType MoveEntityEvent::type = 0x8b2e7298;

    IEventDataPtr MoveEntityEvent::copy() const {
        return IEventDataPtr(zero_new MoveEntityEvent(_entity_id, _new_location));
    }

    MoveEntityEvent::ptr MoveEntityEvent::create(const EntityId id, const Point<float> new_location) {
        return MoveEntityEvent::ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::ptr MoveEntityEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == MoveEntityEvent::type);
        return std::static_pointer_cast<MoveEntityEvent>(data_ptr);
    }

    //
    // AttachProcessEvent
    //

    const EventType AttachProcessEvent::type = 0xa241c4db;

    IEventDataPtr AttachProcessEvent::copy() const {
        return IEventDataPtr(zero_new AttachProcessEvent(_process));
    }

    AttachProcessEvent::ptr AttachProcessEvent::create(Process::ptr process) {
        return AttachProcessEvent::ptr(zero_new AttachProcessEvent(process));
    }

    AttachProcessEvent::ptr AttachProcessEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->is_type(type));
        return std::static_pointer_cast<AttachProcessEvent>(data_ptr);
    }
}

