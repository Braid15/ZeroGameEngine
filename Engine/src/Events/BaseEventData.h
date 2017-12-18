#pragma once

#include "../ZeroEngineStd.h"
#include "EventData.h"
#include "../AppLayer/Game.h"

namespace ZeroEngine {

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
        inline explicit BaseEventData(const Tick timestamp=Game::get_ticks()) : _timestamp(timestamp) {};
    };
}