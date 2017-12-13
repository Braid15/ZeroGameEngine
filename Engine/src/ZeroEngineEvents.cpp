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

    //
    // MoveEntityEvent
    //

    const EventType MoveEntityEvent::type = 0x8b2e7298;

    IEventDataPtr MoveEntityEvent::copy() const {
        return IEventDataPtr(zero_new MoveEntityEvent(_new_location));
    }

    MoveEntityEvent::ptr MoveEntityEvent::create(const Point<float> new_location) {
        return MoveEntityEvent::ptr(zero_new MoveEntityEvent(new_location));
    }

    MoveEntityEvent::ptr MoveEntityEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == MoveEntityEvent::type);
        return std::static_pointer_cast<MoveEntityEvent>(data_ptr);
    }

}

