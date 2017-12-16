#pragma once 

#include "../ZeroEngineStd.h"
#include "EventType.h"
#include "EventListener.h"
#include "../Time.h"

namespace ZeroEngine {

    typedef std::ostrstream& IEventDataStream;

    class IEventData : public IZeroObject {
    public:
        virtual const EventType& get_event_type() const = 0;
        virtual bool is_type(const EventType&) const = 0;
        virtual StringRepr to_string() const = 0;
        virtual const Tick& get_timestamp() const = 0;
        // @TODO: Make own stream class
        virtual void serialize(IEventDataStream out) const = 0;
        virtual IEventDataPtr copy() const = 0;
    };
}