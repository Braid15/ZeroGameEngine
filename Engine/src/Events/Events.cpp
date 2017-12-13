#include "Events.h"

namespace ZeroEngine {

    //
    // QuitEventData
    //

    const EventType QuitEventData::type = 0x9e100aeb;

    IEventDataPtr QuitEventData::copy() const {
        return IEventDataPtr(zero_new QuitEventData());
    }

    std::shared_ptr<QuitEventData> QuitEventData::create() {
        std::shared_ptr<QuitEventData> ret_data(zero_new QuitEventData());
        return ret_data;
    }
}


