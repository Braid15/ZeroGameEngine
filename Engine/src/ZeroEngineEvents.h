#pragma once 

#include "ZeroEngineStd.h"
#include "Events/Events.h"
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Process\Process.h"
#include "Events/BaseEventData.h"
#include "Math/MathTypes.h"

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
    public:
        RequestCreateEntityEvent() : _resource_path("") { }
        explicit RequestCreateEntityEvent(const char* path) : _resource_path(std::string(path)) {}

        inline std::string get_resource_path() const { return _resource_path; }

        static RequestCreateEntityEvent::s_ptr create();
        static RequestCreateEntityEvent::s_ptr create(const char* path);
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

    // @TODO: Change to Matrix3x3/Matrix4x4
    class MoveEntityEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(MoveEntityEvent)

    public:
        enum TransformType { MAT3, MAT4 };
    private:
        TransformType _transform_type;

        union Transform {
            Matrix3x3 mat3;
            Matrix4x4 mat4;

            Transform() {}
        } _transform;

        EntityId _controlled_entity_id;
    public:
        MoveEntityEvent(const EntityId id, const Matrix3x3 new_position);
        MoveEntityEvent(const EntityId id, const Matrix4x4 new_position);

        static MoveEntityEvent::s_ptr create(const EntityId id, const Matrix3x3 new_pos);
        static MoveEntityEvent::s_ptr create(const EntityId id, const Matrix4x4 new_pos);

        inline TransformType get_transform_type() const { return _transform_type; }
        inline EntityId get_entity_id() const { return _controlled_entity_id; }

        inline Matrix3x3 get_transform_2D() const { 
            if (_transform_type != MAT3) return Matrix3x3::identity();
            return _transform.mat3;
        }

        inline Matrix4x4 get_transform_3D() const {
            if (_transform_type != MAT4) return Matrix4x4::identity();
            return _transform.mat4;
        }
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
}