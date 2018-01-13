#include "ZeroEngineEvents.h"
#include "Utils/StringId.h"

namespace ZeroEngine {
    
    // @TODO: Get rid of macros. THey make things more complicated by hiding things.

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


    MoveEntityEvent::MoveEntityEvent(const MoveEntityEvent& other) {
        _transform = other._transform;
        _controlled_entity_id = other._controlled_entity_id;
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

    // -----------------------
    // NewRenderComponentEvent
    // -----------------------

    DEFINE_EVENT_METHODS(NewRenderComponentEvent);

    NewRenderComponentEvent::NewRenderComponentEvent(const NewRenderComponentEvent& other) {
        _entity_id = other._entity_id;
        _scene_node = other._scene_node;
    }

    // -----------------------------
    // ModifiedRenderComponentsEvent
    // -----------------------------

    DEFINE_EVENT_METHODS(ModifiedRenderComponentEvent);

    ModifiedRenderComponentEvent::ModifiedRenderComponentEvent(const ModifiedRenderComponentEvent& other) {
        _entity_id = other._entity_id;
    }
}

