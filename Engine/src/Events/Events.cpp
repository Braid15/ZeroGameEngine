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
        return std::shared_ptr<QuitEventData>(zero_new QuitEventData());
    }

    std::shared_ptr<QuitEventData> QuitEventData::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == QuitEventData::type);
        return std::static_pointer_cast<QuitEventData>(data_ptr);
    }
}


