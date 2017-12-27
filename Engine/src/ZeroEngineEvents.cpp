#include "ZeroEngineEvents.h"

namespace ZeroEngine {
    
    // -------------------------
    // RequestDestroyEntityEvent
    // -------------------------

    const EventType RequestDestroyEntityEvent::type = 0x6cf99d0;

    IEventDataPtr RequestDestroyEntityEvent::copy() const {
        return IEventDataPtr(zero_new RequestDestroyEntityEvent(_controlled_entity_id));
    }

    RequestDestroyEntityEvent::ptr RequestDestroyEntityEvent::create(const EntityId& id) {
        return RequestDestroyEntityEvent::ptr(zero_new RequestDestroyEntityEvent(id));
    }

    RequestDestroyEntityEvent::ptr RequestDestroyEntityEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == RequestDestroyEntityEvent::type);
        return std::static_pointer_cast<RequestDestroyEntityEvent>(data_ptr);
    }

    // --------------------
    // EntityDestroyedEvent
    // --------------------

    const EventType EntityDestroyedEvent::type = 0x616cced;

    IEventDataPtr EntityDestroyedEvent::copy() const {
        return IEventDataPtr(zero_new EntityDestroyedEvent(_controlled_entity_id));
    }

    EntityDestroyedEvent::ptr EntityDestroyedEvent::create(const EntityId& id) {
        return EntityDestroyedEvent::ptr(zero_new EntityDestroyedEvent(id));
    }

    EntityDestroyedEvent::ptr EntityDestroyedEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == EntityDestroyedEvent::type);
        return std::static_pointer_cast<EntityDestroyedEvent>(data_ptr);
    }

    // ------------------------
    // RequestCreateEntityEvent
    // ------------------------

    const EventType RequestCreateEntityEvent::type = 0x817a4c4e;

    IEventDataPtr RequestCreateEntityEvent::copy() const {
        return IEventDataPtr(zero_new RequestCreateEntityEvent(_resource_path));
    }

    RequestCreateEntityEvent::ptr RequestCreateEntityEvent::create() {
        return RequestCreateEntityEvent::ptr(zero_new RequestCreateEntityEvent());
    }

    RequestCreateEntityEvent::ptr RequestCreateEntityEvent::create(const char* path) {
        return RequestCreateEntityEvent::ptr(zero_new RequestCreateEntityEvent(path));
    }

    RequestCreateEntityEvent::ptr RequestCreateEntityEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == RequestCreateEntityEvent::type);
        return std::static_pointer_cast<RequestCreateEntityEvent>(data_ptr);
    }

    // ------------------
    // EntityCreatedEvent
    // ------------------

    const EventType EntityCreatedEvent::type = 0xa7d61b3c;

    IEventDataPtr EntityCreatedEvent::copy() const {
        return IEventDataPtr(zero_new EntityCreatedEvent(_controlled_entity_id));
    }

    EntityCreatedEvent::ptr EntityCreatedEvent::create(const EntityId& id) {
        return EntityCreatedEvent::ptr(zero_new EntityCreatedEvent(id));
    }

    EntityCreatedEvent::ptr EntityCreatedEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == EntityCreatedEvent::type);
        return std::static_pointer_cast<EntityCreatedEvent>(data_ptr);
    }

    // ---------------
    // MoveEntityEvent
    // ---------------

    const EventType MoveEntityEvent::type = 0x8b2e7298;

    MoveEntityEvent::MoveEntityEvent(const EntityId id, const Vector2 new_position) {
        _controlled_entity_id = id;
        _position_type = VEC2;
        _position.vec2 = new_position;
    }

    MoveEntityEvent::MoveEntityEvent(const EntityId id, const Vector3 new_position) {
         _controlled_entity_id = id;
        _position_type = VEC3;
        _position.vec3 = new_position;       
    }

    MoveEntityEvent::MoveEntityEvent(const EntityId id, const Vector4 new_position) {
        _controlled_entity_id = id;
        _position_type = VEC4;
        _position.vec4 = new_position;
    }

    IEventDataPtr MoveEntityEvent::copy() const {
        switch (_position_type) {
            case VEC2:
                return IEventDataPtr(zero_new MoveEntityEvent(_controlled_entity_id, _position.vec2));
            case VEC3:
                return IEventDataPtr(zero_new MoveEntityEvent(_controlled_entity_id, _position.vec3));
            case VEC4:
                return IEventDataPtr(zero_new MoveEntityEvent(_controlled_entity_id, _position.vec4));
        }
        return IEventDataPtr();
    }

    MoveEntityEvent::ptr MoveEntityEvent::create(const EntityId id, const Vector2 new_location) {
        return MoveEntityEvent::ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::ptr MoveEntityEvent::create(const EntityId id, const Vector3 new_location) {
        return MoveEntityEvent::ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::ptr MoveEntityEvent::create(const EntityId id, const Vector4 new_location) {
        return MoveEntityEvent::ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::ptr MoveEntityEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == MoveEntityEvent::type);
        return std::static_pointer_cast<MoveEntityEvent>(data_ptr);
    }

    // ------------------
    // AttachProcessEvent
    // ------------------

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

    // ---------------------------------
    // ScreenElementRendererCreatedEvent
    // ---------------------------------

    const EventType ScreenElementRenderComponentCreatedEvent::type = 0xbdfc323e;

    IEventDataPtr ScreenElementRenderComponentCreatedEvent::copy() const {
        return IEventDataPtr(zero_new ScreenElementRenderComponentCreatedEvent(_screen_element));
    }

    ScreenElementRenderComponentCreatedEvent::s_ptr ScreenElementRenderComponentCreatedEvent::create(std::shared_ptr<IScreenElement> element) {
        return ScreenElementRenderComponentCreatedEvent::s_ptr(zero_new ScreenElementRenderComponentCreatedEvent(element));
    }

    ScreenElementRenderComponentCreatedEvent::s_ptr ScreenElementRenderComponentCreatedEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->is_type(type));
        return std::static_pointer_cast<ScreenElementRenderComponentCreatedEvent>(data_ptr);
    }

    // ------------------------------------------
    // ScreenElementRenderComponentDestroyedEvent
    // ------------------------------------------

    const EventType ScreenElementRenderComponentDestroyedEvent::type = 0x3e5bd852;

    IEventDataPtr ScreenElementRenderComponentDestroyedEvent::copy() const {
        return IEventDataPtr(zero_new ScreenElementRenderComponentDestroyedEvent(_screen_element));
    }

    ScreenElementRenderComponentDestroyedEvent::s_ptr ScreenElementRenderComponentDestroyedEvent::create(std::shared_ptr<IScreenElement> element) {
        return ScreenElementRenderComponentDestroyedEvent::s_ptr(zero_new ScreenElementRenderComponentDestroyedEvent(element));
    }

    ScreenElementRenderComponentDestroyedEvent::s_ptr ScreenElementRenderComponentDestroyedEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->is_type(type));
        return std::static_pointer_cast<ScreenElementRenderComponentDestroyedEvent>(data_ptr);
    }

    // -------------
    // DrawLineEvent
    // -------------

    const EventType DrawLineEvent::type = 0xd78aad3d;

    IEventDataPtr DrawLineEvent::copy() const {
        return IEventDataPtr(zero_new DrawLineEvent(_from, _to, _color));
    }

    DrawLineEvent::ptr DrawLineEvent::create(Point<int32_t> from, Point<int32_t> to, Color color) {
        return DrawLineEvent::ptr(zero_new DrawLineEvent(from, to, color));
    }

    DrawLineEvent::ptr DrawLineEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->is_type(type));
        return std::static_pointer_cast<DrawLineEvent>(data_ptr);
    }
}

