#pragma once 

#include "../ZeroEngineStd.h"
#include "EventType.h"
#include "EventListener.h"
#include "../Time.h"
#include "../Framework/Framework.h"

namespace ZeroEngine {

    typedef std::ostrstream& IEventDataStream;

    class IEventData : public IZeroObject {
    public:
        virtual const EventType& get_event_type() const = 0;
        virtual StringRepr to_string() const = 0;
        virtual const Ticks& get_timestamp() const = 0;
        // @TODO: Make own stream class
        virtual void serialize(IEventDataStream out) const = 0;
        virtual IEventDataPtr copy() const = 0;
    };

    class BaseEventData : public IEventData {
    private:
        const Ticks _timestamp;
    public:
        inline virtual ~BaseEventData() {};
        virtual const EventType& get_event_type() const = 0;
        virtual StringRepr to_string() const = 0;
        virtual IEventDataPtr copy() const = 0;
        inline virtual void serialize(IEventDataStream out) const override {}
        inline const Ticks& get_timestamp() const override { return _timestamp; }
    protected:
        inline explicit BaseEventData(const Ticks timestamp=ZeroFramework::get_ticks()) : _timestamp(timestamp) {};
    };
}