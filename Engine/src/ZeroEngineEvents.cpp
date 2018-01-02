#include "ZeroEngineEvents.h"
#include "Utils/StringId.h"

namespace ZeroEngine {
    
    // -------------------------
    // RequestDestroyEntityEvent
    // -------------------------

    DEFINE_EVENT_METHODS(RequestDestroyEntityEvent);

    RequestDestroyEntityEvent::s_ptr RequestDestroyEntityEvent::create(const EntityId& id) {
        return RequestDestroyEntityEvent::s_ptr(zero_new RequestDestroyEntityEvent(id));
    }

    RequestDestroyEntityEvent::RequestDestroyEntityEvent(const RequestDestroyEntityEvent& other) {
        _controlled_entity_id = other.get_entity_id();
    }

    // --------------------
    // EntityDestroyedEvent
    // --------------------

    DEFINE_EVENT_METHODS(EntityDestroyedEvent);

    EntityDestroyedEvent::s_ptr EntityDestroyedEvent::create(const EntityId& id) {
        return EntityDestroyedEvent::s_ptr(zero_new EntityDestroyedEvent(id));
    }

    EntityDestroyedEvent::EntityDestroyedEvent(const EntityDestroyedEvent& other) {
        _controlled_entity_id = other.get_entity_id();
    }

    // ------------------------
    // RequestCreateEntityEvent
    // ------------------------

    DEFINE_EVENT_METHODS(RequestCreateEntityEvent);

    RequestCreateEntityEvent::s_ptr RequestCreateEntityEvent::create() {
        return RequestCreateEntityEvent::s_ptr(zero_new RequestCreateEntityEvent());
    }

    RequestCreateEntityEvent::s_ptr RequestCreateEntityEvent::create(const char* path) {
        return RequestCreateEntityEvent::s_ptr(zero_new RequestCreateEntityEvent(path));
    }

    RequestCreateEntityEvent::RequestCreateEntityEvent(const RequestCreateEntityEvent& other) {
        _resource_path = other.get_resource_path();
    }

    // ------------------
    // EntityCreatedEvent
    // ------------------

    DEFINE_EVENT_METHODS(EntityCreatedEvent);

    EntityCreatedEvent::s_ptr EntityCreatedEvent::create(const EntityId& id) {
        return EntityCreatedEvent::s_ptr(zero_new EntityCreatedEvent(id));
    }

    EntityCreatedEvent::EntityCreatedEvent(const EntityCreatedEvent& other) {
        _controlled_entity_id = other.get_entity_id();
    }

    // ---------------
    // MoveEntityEvent
    // ---------------

    DEFINE_EVENT_METHODS(MoveEntityEvent);

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

    MoveEntityEvent::s_ptr MoveEntityEvent::create(const EntityId id, const Vector2 new_location) {
        return MoveEntityEvent::s_ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::s_ptr MoveEntityEvent::create(const EntityId id, const Vector3 new_location) {
        return MoveEntityEvent::s_ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::s_ptr MoveEntityEvent::create(const EntityId id, const Vector4 new_location) {
        return MoveEntityEvent::s_ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::MoveEntityEvent(const MoveEntityEvent& other) {
        _controlled_entity_id = other.get_entity_id();
        _position_type = other.get_position_type();
        switch (_position_type) {
            case VEC2:
                _position.vec2 = other.get_vec2_position();
                break;
            case VEC3:
                _position.vec3 = other.get_vec3_position();
                break;
            case VEC4:
                _position.vec4 = other.get_vec4_position();
                break;
            default:
                LOG_DEBUG("MoveEntityEvent", "Error: Unknown position type");
                break;
        }
    }

    // ------------------
    // AttachProcessEvent
    // ------------------

    DEFINE_EVENT_METHODS(AttachProcessEvent);

    AttachProcessEvent::s_ptr AttachProcessEvent::create(Process::ptr process) {
        return AttachProcessEvent::s_ptr(zero_new AttachProcessEvent(process));
    }

    AttachProcessEvent::AttachProcessEvent(const AttachProcessEvent& other) {
        _process = other.get_process();
    }

    // ---------------------------------
    // ScreenElementRendererCreatedEvent
    // ---------------------------------

    DEFINE_EVENT_METHODS(ScreenElementRenderComponentCreatedEvent);

    ScreenElementRenderComponentCreatedEvent::s_ptr ScreenElementRenderComponentCreatedEvent::create(std::shared_ptr<IScreenElement> element) {
        return ScreenElementRenderComponentCreatedEvent::s_ptr(zero_new ScreenElementRenderComponentCreatedEvent(element));
    }

    ScreenElementRenderComponentCreatedEvent::ScreenElementRenderComponentCreatedEvent(const ScreenElementRenderComponentCreatedEvent& other) {
        _screen_element = other.get_screen_element();
    }

    // ------------------------------------------
    // ScreenElementRenderComponentDestroyedEvent
    // ------------------------------------------

    const EventType ScreenElementRenderComponentDestroyedEvent::type = STRING_ID("ScreenElementRenderComponentDestroyedEvent");

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

    const EventType DrawLineEvent::type = STRING_ID("DrawLineEvent");

    IEventDataPtr DrawLineEvent::copy() const {
        return IEventDataPtr(zero_new DrawLineEvent(_from, _to, _color));
    }

    DrawLineEvent::ptr DrawLineEvent::create(Point<int32> from, Point<int32> to, Color color) {
        return DrawLineEvent::ptr(zero_new DrawLineEvent(from, to, color));
    }

    DrawLineEvent::ptr DrawLineEvent::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->is_type(type));
        return std::static_pointer_cast<DrawLineEvent>(data_ptr);
    }
}

