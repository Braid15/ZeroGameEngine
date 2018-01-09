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

    RequestCreateEntityEvent::s_ptr RequestCreateEntityEvent::create(const char* path, Vector3 pos) {
        return RequestCreateEntityEvent::s_ptr(zero_new RequestCreateEntityEvent(path, pos));
    }

    RequestCreateEntityEvent::RequestCreateEntityEvent(const RequestCreateEntityEvent& other) {
        _resource_path = other.get_resource_path();
        _position = other.get_initial_position();
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

    MoveEntityEvent::MoveEntityEvent(const EntityId id, const Matrix3x3 new_position) {
        _controlled_entity_id = id;
        _transform_type = MAT3;
        _transform.mat3 = new_position;
    }

    MoveEntityEvent::MoveEntityEvent(const EntityId id, const Matrix4x4 new_position) {
         _controlled_entity_id = id;
        _transform_type = MAT4;
        _transform.mat4 = new_position;       
    }

    MoveEntityEvent::s_ptr MoveEntityEvent::create(const EntityId id, const Matrix3x3 new_location) {
        return MoveEntityEvent::s_ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::s_ptr MoveEntityEvent::create(const EntityId id, const Matrix4x4 new_location) {
        return MoveEntityEvent::s_ptr(zero_new MoveEntityEvent(id, new_location));
    }

    MoveEntityEvent::MoveEntityEvent(const MoveEntityEvent& other) {
        _controlled_entity_id = other.get_entity_id();
        _transform_type = other.get_transform_type();
        switch (_transform_type) {
            case MAT3:
                _transform.mat3 = other.get_transform_2D();
                break;
            case MAT4:
                _transform.mat4 = other.get_transform_3D();
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

    DEFINE_EVENT_METHODS(ScreenElementRenderComponentDestroyedEvent);

    ScreenElementRenderComponentDestroyedEvent::s_ptr ScreenElementRenderComponentDestroyedEvent::create(std::shared_ptr<IScreenElement> element) {
        return ScreenElementRenderComponentDestroyedEvent::s_ptr(zero_new ScreenElementRenderComponentDestroyedEvent(element));
    }

    ScreenElementRenderComponentDestroyedEvent::ScreenElementRenderComponentDestroyedEvent(const ScreenElementRenderComponentDestroyedEvent& other) {
        _screen_element = other.get_screen_element();
    }
}

