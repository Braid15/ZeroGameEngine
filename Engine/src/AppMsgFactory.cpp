#include "AppMsgFactory.h"

namespace ZeroEngine {

    AppMsgFactory::AppMsgFactory() {
        AppMsg::init_memory_pool();
        _creation_map = zero_new std::map<AppMsgType, app_msg_creation_delegate>();
        register_app_messages();
        _current_message = get_app_message(NullMsg::type);
    }

    AppMsgFactory::~AppMsgFactory() {
        // @@TODO: Move delete into AppMsg class and make it so that the
        // static create methods in derived class can only be called by AppMsgFactory
        delete _current_message;
        _current_message = nullptr;
        zero_delete(_creation_map);
        AppMsg::destroy_memory_pool();
    }

    AppMsgPtr AppMsgFactory::create_message(AppMsgType msg_type) {
        delete _current_message;
        _current_message = get_app_message(msg_type);
        return _current_message;
    }

    AppMsgPtr AppMsgFactory::create_message(AppMsgType msg_type, AppMsgArgs args) {
        create_message(msg_type);
        _current_message->set_args(args);
        return _current_message;
    }

    AppMsgPtr AppMsgFactory::get_app_message(AppMsgType msg_type) {
        assert(_creation_map != nullptr);
        std::map<AppMsgType, app_msg_creation_delegate>::iterator iter;
        iter = _creation_map->find(msg_type);
        if (iter == _creation_map->end()) {
            std::cout << "ERROR. AppMsgFactory create_message() failed.\n";
            // create NullMsg on error
            assert( msg_type != NullMsg::type);
            iter = _creation_map->find(NullMsg::type);
        }
        app_msg_creation_delegate delegate = iter->second;
        return delegate(AppMsgArgs::empty);
    }

    void AppMsgFactory::register_app_messages() {
        assert(_creation_map != nullptr);
        _creation_map->insert(std::make_pair(NullMsg::type, NullMsg::create));
        _creation_map->insert(std::make_pair(MouseMsg::type, MouseMsg::create)); 
        _creation_map->insert(std::make_pair(QuitMsg::type, QuitMsg::create));
        _creation_map->insert(std::make_pair(UnhandledMsg::type, UnhandledMsg::create));
    }
}