#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef uint32_t EventGuid;

    class IEventType : public IZeroObject {
    public:
        virtual StringRepr to_string() const = 0;
        virtual const EventGuid& guid() const = 0;
        virtual bool equals(const IEventType&) const = 0;
    };
}