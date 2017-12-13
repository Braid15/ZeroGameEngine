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

    //
    // EntityCreatedEventData
    //

    const EventType EntityCreatedEventData::type = 0xa7d61b3c;

    IEventDataPtr EntityCreatedEventData::copy() const {
        return IEventDataPtr(zero_new EntityCreatedEventData(_entity_id));
    }

    std::shared_ptr<EntityCreatedEventData> EntityCreatedEventData::create(const EntityId& entity_id) {
        return std::shared_ptr<EntityCreatedEventData>(zero_new EntityCreatedEventData(entity_id));
    }

    std::shared_ptr<EntityCreatedEventData> EntityCreatedEventData::cast(IEventDataPtr data_ptr) {
        assert(data_ptr->get_event_type() == EntityCreatedEventData::type);
        return std::static_pointer_cast<EntityCreatedEventData>(data_ptr);
    }
}


