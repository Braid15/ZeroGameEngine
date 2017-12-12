#pragma once 

#include "../ZeroEngineStd.h"
#include "EventType.h"
#include "EventListener.h"
#include "../Time.h"

namespace ZeroEngine {

    typedef std::ostrstream& IEventDataStream;

    class IEventData : public IZeroObject {
    public:
        virtual const IEventType& get_event_type() const = 0;
        virtual StringRepr to_string() const = 0;
        virtual const Time& get_timestamp() const = 0;
        // @TODO: Make own stream class
        virtual void serialize(IEventDataStream out) const = 0;
        virtual IEventDataPtr copy() const = 0;
    };

    class BaseEventData : public IEventData {
    private:
        const Time _timestamp;
    public:
        inline virtual ~BaseEventData() {};
        virtual const IEventType& get_event_type() const = 0;
        virtual StringRepr to_string() const = 0;
        virtual IEventDataPtr copy() const = 0;
        inline virtual void serialize(IEventDataStream out) const override {}
        inline const Time& get_timestamp() const override { return _timestamp; }
    protected:
        inline explicit BaseEventData(const Time timestamp=0.0) : _timestamp(timestamp) {};
    };
}