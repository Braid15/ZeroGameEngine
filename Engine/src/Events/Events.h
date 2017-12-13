#pragma once 

#include "EventData.h"
#include "EventListener.h"
#include "EventType.h"
#include "EventManager.h"
#include "../Entity/Entity.h"

namespace ZeroEngine {

    // @TODO: Move these to ZeroEngineEvents.h




    //
    // Quit Event
    //

    class QuitEventData final : public BaseEventData {
    public:
        static const EventType type;
    public:
        static std::shared_ptr<QuitEventData> create();
        static std::shared_ptr<QuitEventData> cast(IEventDataPtr);
        inline QuitEventData() {}
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "QuitEventData"; }
        IEventDataPtr copy() const override;
    };

    //
    // EntityCreatedEventData
    //

    class EntityCreatedEventData final : public BaseEventData {
    private:
        const EntityId _entity_id;
    public:
        static const EventType type;
    public:
        static std::shared_ptr<EntityCreatedEventData> create(const EntityId&);
        static std::shared_ptr<EntityCreatedEventData> cast(IEventDataPtr);
        IEventDataPtr copy() const override;
        inline EntityCreatedEventData(const EntityId& entity_id) : _entity_id(entity_id) {}
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "EntityCreatedEventData"; }
        inline const EntityId& get_entity_id() const { return _entity_id; }
    };
}
