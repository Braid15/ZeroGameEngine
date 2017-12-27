#pragma once 

#include "ZeroEngineStd.h"
#include "Events/Events.h"
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Process\Process.h"
#include "Events/BaseEventData.h"

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

    //
    // DrawPrimitiveEvent
    //

    // @TEMP:
    // I don't really want to have to make an event just to draw a line
    // Used to draw primitive points.

    // @TODO: Change to CreateScreenElementEvent
    class DrawLineEvent : public BaseEventData {
    private:
        Point<int32_t> _from;
        Point<int32_t> _to;
        Color _color;
    public:
        typedef std::shared_ptr<DrawLineEvent> ptr;
        static const EventType type;
    public:
        inline explicit DrawLineEvent(Point<int32_t> from, Point<int32_t> to, Color color) : 
            _from(from), _to(to), _color(color) {}
        IEventDataPtr copy() const override;
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "DrawLineEvent"; }
        static DrawLineEvent::ptr create(Point<int32_t> from, Point<int32_t>, Color color);
        static DrawLineEvent::ptr cast(IEventDataPtr);
        inline Point<int32_t> get_from_point() const { return _from; }
        inline Point<int32_t> get_to_point() const { return _to; }
        inline Color get_color() const { return _color; }
    private:
        inline DrawLineEvent() {}
        inline DrawLineEvent(const DrawLineEvent&) {}
    };

}