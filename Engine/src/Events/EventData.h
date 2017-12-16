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
        virtual bool is_type(const EventType&) const = 0;
        virtual StringRepr to_string() const = 0;
        virtual const Tick& get_timestamp() const = 0;
        // @TODO: Make own stream class
        virtual void serialize(IEventDataStream out) const = 0;
        virtual IEventDataPtr copy() const = 0;
    };

    class BaseEventData : public IEventData {
    private:
        const Tick _timestamp;
    public:
        inline virtual ~BaseEventData() {};
        virtual const EventType& get_event_type() const = 0;
        inline bool is_type(const EventType& type) const { return get_event_type() == type; }
        virtual StringRepr to_string() const = 0;
        virtual IEventDataPtr copy() const = 0;
        inline virtual void serialize(IEventDataStream out) const override {}
        inline const Tick& get_timestamp() const override { return _timestamp; }
    protected:
        inline explicit BaseEventData(const Tick timestamp=ZeroFramework::get_ticks()) : _timestamp(timestamp) {};
    };
}