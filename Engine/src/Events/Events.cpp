#include "Events.h"

namespace ZeroEngine {

    const EventType QuitEventData::type = 0x9e100aeb;

    IEventDataPtr QuitEventData::copy() const {
        return IEventDataPtr(zero_new QuitEventData());
    }
}


