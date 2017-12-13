#ifdef _DEBUG

#include "TestApp.h"

namespace ZeroEngineAppTest {

    static EntityFactory entity_factory;
    static bool create = false;

    bool MockZeroEngineApp::on_msg_proc(const AppMsg* const msg) {
        if (msg->get_type() == AppMsg::keyboard) {
            const KeyboardMsg* keyboard = KeyboardMsg::cast(msg);
            if (keyboard->is_key_press(Keys::space)) {
                create = true;
            }
        }
        return true;
    }

    void MockZeroEngineApp::on_update(Ticks time) {
        if (create) {
            std::shared_ptr<Entity> entity = entity_factory.create_entity();
            ZeroEventManager::queue_event(EntityCreatedEventData::create(entity->get_id()));
            create = false;
        }
    }

    void MockZeroEngineApp::entity_created_delegate(IEventDataPtr event_data) {
        std::shared_ptr<EntityCreatedEventData> data = EntityCreatedEventData::cast(event_data);
        std::cout << "Entity created. Id: " << data->get_entity_id() << "\n";
    }

    MockZeroEngineApp::~MockZeroEngineApp() {
        EventListenerDelegate delegate = fastdelegate::MakeDelegate(this, &MockZeroEngineApp::entity_created_delegate);
        ZeroEventManager::unregister_listener(delegate, EntityCreatedEventData::type);
    }

    void MockZeroEngineApp::register_game_events() {
        EventListenerDelegate delegate = fastdelegate::MakeDelegate(this, &MockZeroEngineApp::entity_created_delegate);
        ZeroEventManager::register_listener(delegate, EntityCreatedEventData::type);
    }
}

#endif