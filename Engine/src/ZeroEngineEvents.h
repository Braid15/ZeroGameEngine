#pragma once 

#include "ZeroEngineStd.h"
#include "Events/Events.h"
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Process\Process.h"
#include "Events/BaseEventData.h"
#include "Math/MathTypes.h"
#include "Entity\Transform.h"
#include "GameView\SceneNode.h"

namespace ZeroEngine {

    // -------------------------
    // RequestDestroyEntityEvent
    // -------------------------

    class RequestDestroyEntityEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(RequestDestroyEntityEvent)

    private:
        EntityId _controlled_entity_id;
    public:
        explicit RequestDestroyEntityEvent(const EntityId& id) : _controlled_entity_id(id) {}
        inline EntityId get_entity_id() const { return _controlled_entity_id; }
        static RequestDestroyEntityEvent::s_ptr create(const EntityId& id);
    private:
        RequestDestroyEntityEvent() {}
    };

    // --------------------
    // EntityDestroyedEvent
    // --------------------

    class EntityDestroyedEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(EntityDestroyedEvent)

    private:
        EntityId _controlled_entity_id;
    public:
        explicit EntityDestroyedEvent(const EntityId& id) : _controlled_entity_id(id) {}
        inline EntityId get_entity_id() const { return _controlled_entity_id; }
        static EntityDestroyedEvent::s_ptr create(const EntityId& id);
    private:
        EntityDestroyedEvent() {}
    };

    // ------------------------
    // RequestCreateEntityEvent
    // ------------------------

    class RequestCreateEntityEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(RequestCreateEntityEvent)

    private:
        std::string _resource_path;
        Vector3 _position;
    public:
        RequestCreateEntityEvent() : _resource_path(""), _position(Vector3(0)) { }
        explicit RequestCreateEntityEvent(const char* path) : _resource_path(std::string(path)),
            _position(Vector3(0)) {}
        RequestCreateEntityEvent(const char* path, Vector3 pos) : _resource_path(std::string(path)),
            _position(Vector3(pos)) {}

        inline std::string get_resource_path() const { return _resource_path; }
        inline const Vector3& get_initial_position() const { return _position; }

        static RequestCreateEntityEvent::s_ptr create();
        static RequestCreateEntityEvent::s_ptr create(const char* path);
        static RequestCreateEntityEvent::s_ptr create(const char* path, Vector3 pos);
    };

    // ------------------
    // EntityCreatedEvent
    // ------------------

    class EntityCreatedEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(EntityCreatedEvent)

    private:
        EntityId _controlled_entity_id;
    public:
        explicit EntityCreatedEvent(const EntityId& entity_id) : _controlled_entity_id(entity_id) {}
        inline EntityId get_entity_id() const { return _controlled_entity_id; }
        static EntityCreatedEvent::s_ptr create(const EntityId& id);
    private:
        EntityCreatedEvent() {}
    };


    // ---------------
    // MoveEntityEvent
    // ---------------

    class MoveEntityEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(MoveEntityEvent)

    private:
        Transform _transform;
        EntityId _controlled_entity_id;

    public:
        MoveEntityEvent(const EntityId& id, Transform transform) : 
            _controlled_entity_id(id), _transform(transform) {}

        inline EntityId get_entity_id() const { return _controlled_entity_id; }
        inline Transform get_transform() const { return _transform; }
    private:
        MoveEntityEvent() {}
    };



    // ------------------
    // AttachProcessEvent
    // ------------------

    // Used for sending a process to be attached to the game logic from the game view
    class AttachProcessEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(AttachProcessEvent)

    private:
        Process::ptr _process;
    public:
        explicit AttachProcessEvent(Process::ptr process) : _process(process) {}
        static AttachProcessEvent::s_ptr create(Process::ptr process);
        inline Process::ptr get_process() const { return _process; }
    private:
        inline AttachProcessEvent() {}
    };

    // ----------------------------------------
    // ScreenElementRenderComponentCreatedEvent
    // ----------------------------------------

    class IScreenElement;

    // @TODO: Change name to RenderComponentCreatedEvent

    class ScreenElementRenderComponentCreatedEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(ScreenElementRenderComponentCreatedEvent)

    private:
        std::shared_ptr<IScreenElement> _screen_element;
    public:
        explicit ScreenElementRenderComponentCreatedEvent(std::shared_ptr<IScreenElement> element) 
            : _screen_element(element) {}

        static ScreenElementRenderComponentCreatedEvent::s_ptr create(std::shared_ptr<IScreenElement>);
        inline std::shared_ptr<IScreenElement> get_screen_element() const { return _screen_element; }
    private:
        ScreenElementRenderComponentCreatedEvent() {}
    };

    // -------------------------------------
    // ScreenElementRenderComponentDestroyed
    // -------------------------------------

    // @TODO: THis is uneeded. Can just use EntityDestroyedEvent and then
    // delete the render component by searching via EntityId

    class ScreenElementRenderComponentDestroyedEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(ScreenElementRenderComponentDestroyedEvent)

    private:
        std::shared_ptr<IScreenElement> _screen_element;
    public:
        explicit ScreenElementRenderComponentDestroyedEvent(std::shared_ptr<IScreenElement> element) 
            : _screen_element(element) {}

        static ScreenElementRenderComponentDestroyedEvent::s_ptr create(std::shared_ptr<IScreenElement>);
        inline std::shared_ptr<IScreenElement> get_screen_element() const { return _screen_element; }
    private:
        ScreenElementRenderComponentDestroyedEvent() {}
    };

    // -----------------------
    // NewRenderComponentEvent
    // -----------------------

    class NewRenderComponentEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(NewRenderComponentEvent)

    private:
        EntityId _entity_id;
        std::shared_ptr<SceneNode> _scene_node;
    public:
        NewRenderComponentEvent() : _entity_id(invalid_entity_id()) {}
        NewRenderComponentEvent(const EntityId& id, std::shared_ptr<SceneNode> node) :
            _entity_id(id), _scene_node(node) {}


        inline EntityId get_entity_id() const { return _entity_id; }
        inline std::shared_ptr<SceneNode> get_scene_node() const { return _scene_node; }
    };

    // ----------------------------
    // ModifiedRenderComponentEvent
    // ----------------------------

    class SceneNode;

    class ModifiedRenderComponentEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(ModifiedRenderComponentEvent)

    private:
        EntityId _entity_id;
    public:
        ModifiedRenderComponentEvent() : _entity_id(invalid_entity_id()) {}
        ModifiedRenderComponentEvent(const EntityId& id) : _entity_id(id) {}

        inline EntityId get_entity_id() const { return _entity_id; }
    };
}