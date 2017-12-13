#pragma once 

#include "EventData.h"
#include "EventListener.h"
#include "EventType.h"
#include "EventManager.h"

namespace ZeroEngine {

    //
    // Quit Event
    //

    class QuitEventData final : public BaseEventData {
    public:
        static const EventType type;
    public:
        inline QuitEventData() {}
        inline const EventType& get_event_type() const override { return type; }
        inline StringRepr to_string() const override { return "QuitEventData"; }
        IEventDataPtr copy() const;
    };
}
