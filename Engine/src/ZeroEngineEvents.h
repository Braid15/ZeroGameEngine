#pragma once 

#include "ZeroEngineStd.h"
#include "Events/Events.h"
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Process\Process.h"
#include "Events/BaseEventData.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

namespace ZeroEngine {

    // -------------------------
    // RequestDestroyEntityEvent
    // -------------------------

    class RequestDestroyEntityEvent : public BaseEventData {
    DECLARE_EVENT_METHODS(RequestDestroyEntityEvent)

    private:
        EntityId _controlled_entity_id;
    public:
        RequestDestroyEntityEvent(const EntityId& id) : _controlled_entity_id(id) {}
        inline const EntityId& get_entity_id() const { return _controlled_entity_id; }
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
        EntityDestroyedEvent(const EntityId& id) : _controlled_entity_id(id) {}
        inline const EntityId& get_entity_id() const { return _controlled_entity_id; }
        static EntityDestroyedEvent::s_ptr create(const EntityId& id);
    private:
        EntityDestroyedEvent() {}
    };

    //
    // RequestCreateEntityEvent
    //

    class RequestCreateEntityEvent : public BaseEventData {
    public:
        typedef std::shared_ptr<RequestCreateEntityEvent> ptr;
        static const EventType type;
        const char* _resource_path;
    public:
        inline RequestCreateEntityEvent() : _resource_path(nullptr) { }
        inline RequestCreateEntityEvent(const char* path) : _resource_path(path) {}

        inline std::string get_resource_path() const { return std::string(_resource_path); }

        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "RequestCreateEntityEvent"; }
        static RequestCreateEntityEvent::ptr create();
        static RequestCreateEntityEvent::ptr create(const char* path);
        static RequestCreateEntityEvent::ptr cast(IEventDataPtr);
    };

    //
    // EntityCreatedEvent
    //

    class EntityCreatedEvent : public BaseEventData {
    private:
        const EntityId _controlled_entity_id;
    public:
        typedef std::shared_ptr<EntityCreatedEvent> ptr;
        static const EventType type;
    public:
        inline EntityCreatedEvent(const EntityId& entity_id) : _controlled_entity_id(entity_id) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "EntityCreatedEvent"; }
        inline const EntityId& get_entity_id() const { return _controlled_entity_id; }
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
    public:
        enum PositionType { VEC2, VEC3, VEC4 };
    private:
        PositionType _position_type;

        union Position {
            Vector2 vec2;
            Vector3 vec3;
            Vector4 vec4;

            Position() {}
        } _position;

        EntityId _controlled_entity_id;
    public:
        typedef std::shared_ptr<MoveEntityEvent> ptr;
        static const EventType type;
    public:
        MoveEntityEvent(const EntityId id, const Vector2 new_position);
        MoveEntityEvent(const EntityId id, const Vector3 new_position);
        MoveEntityEvent(const EntityId id, const Vector4 new_position);

        static MoveEntityEvent::ptr create(const EntityId id, const Vector2 new_pos);
        static MoveEntityEvent::ptr create(const EntityId id, const Vector3 new_pos);
        static MoveEntityEvent::ptr create(const EntityId id, const Vector4 new_pos);
        static MoveEntityEvent::ptr cast(IEventDataPtr);
        IEventDataPtr copy() const override;

        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "MoveEntityEvent"; }

        inline PositionType get_position_type() const { return _position_type; }

        inline Vector2 get_vec2_position() const { 
            if (_position_type != VEC2) return Vector2();
            return _position.vec2;
        }

        inline Vector3 get_vec3_position() const {
            if (_position_type != VEC3) return Vector3();
            return _position.vec3;
        }

        inline Vector4 get_vec4_position() const {
            if (_position_type != VEC4) return Vector4();
            return _position.vec4;
        }

        inline const EntityId& get_entity_id() const { return _controlled_entity_id; }
        ~MoveEntityEvent() {}
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

    // ----------------------------------------
    // ScreenElementRenderComponentCreatedEvent
    // ----------------------------------------

    class IScreenElement;

    class ScreenElementRenderComponentCreatedEvent : public BaseEventData {
    private:
        std::shared_ptr<IScreenElement> _screen_element;
    public:
        typedef std::shared_ptr<ScreenElementRenderComponentCreatedEvent> s_ptr;
        static const EventType type;
        static ScreenElementRenderComponentCreatedEvent::s_ptr create(std::shared_ptr<IScreenElement>);
        static ScreenElementRenderComponentCreatedEvent::s_ptr cast(IEventDataPtr);


        explicit ScreenElementRenderComponentCreatedEvent(std::shared_ptr<IScreenElement> element) 
            : _screen_element(element) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "SpriteRendererCreatedEvent"; }
        inline std::shared_ptr<IScreenElement> get_screen_element() const { return _screen_element; }
    private:
        ScreenElementRenderComponentCreatedEvent() {}
        ScreenElementRenderComponentCreatedEvent(const ScreenElementRenderComponentCreatedEvent&) {}
    };


    // -------------------------------------
    // ScreenElementRenderComponentDestroyed
    // -------------------------------------

    class ScreenElementRenderComponentDestroyedEvent : public BaseEventData {
    private:
        std::shared_ptr<IScreenElement> _screen_element;
    public:
        typedef std::shared_ptr<ScreenElementRenderComponentDestroyedEvent> s_ptr;
        static const EventType type;
        static ScreenElementRenderComponentDestroyedEvent::s_ptr create(std::shared_ptr<IScreenElement>);
        static ScreenElementRenderComponentDestroyedEvent::s_ptr cast(IEventDataPtr);


        explicit ScreenElementRenderComponentDestroyedEvent(std::shared_ptr<IScreenElement> element) 
            : _screen_element(element) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "SpriteRendererDestroyedEvent"; }
        inline std::shared_ptr<IScreenElement> get_screen_element() const { return _screen_element; }
    private:
        ScreenElementRenderComponentDestroyedEvent() {}
        ScreenElementRenderComponentDestroyedEvent(const ScreenElementRenderComponentDestroyedEvent&) {}
    };

    //
    // DrawPrimitiveEvent
    //

    // @TEMP:
    // I don't really want to have to make an event just to draw a line
    // Used to draw primitive points.

    // @TODO: Change to CreateScreenElementEvent
    class DrawLineEvent : public BaseEventData {
    private:
        Point<int32> _from;
        Point<int32> _to;
        Color _color;
    public:
        typedef std::shared_ptr<DrawLineEvent> ptr;
        static const EventType type;
    public:
        inline explicit DrawLineEvent(Point<int32> from, Point<int32> to, Color color) : 
            _from(from), _to(to), _color(color) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "DrawLineEvent"; }
        static DrawLineEvent::ptr create(Point<int32> from, Point<int32>, Color color);
        static DrawLineEvent::ptr cast(IEventDataPtr);
        inline Point<int32> get_from_point() const { return _from; }
        inline Point<int32> get_to_point() const { return _to; }
        inline Color get_color() const { return _color; }
    private:
        inline DrawLineEvent() {}
        inline DrawLineEvent(const DrawLineEvent&) {}
    };
}