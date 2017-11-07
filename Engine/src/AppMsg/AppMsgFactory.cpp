#include "AppMsgFactory.h"

namespace ZeroEngine {

    AppMsgFactory::AppMsgFactory() {
        AppMsg::init_memory_pool();
        _creation_map = zero_new std::map<AppMsgType, app_msg_creation_delegate>();
        register_app_messages();
        _current_message = get_app_message(AppMsg::null);
    }

    AppMsgFactory::~AppMsgFactory() {
        // @@TODO: Move delete into AppMsg class and make it so that the
        // static create methods in derived class can only be called by AppMsgFactory
        delete _current_message;
        _current_message = nullptr;
        zero_delete(_creation_map);
        AppMsg::destroy_memory_pool();
    }

    AppMsg* AppMsgFactory::create_message(AppMsgType msg_type) {
        delete _current_message;
        _current_message = get_app_message(msg_type);
        return _current_message;
    }

    AppMsg* AppMsgFactory::create_message(AppMsgType msg_type, AppMsgArgs* args) {
        create_message(msg_type);
        _current_message->set_args(args);
        return _current_message;
    }

    AppMsg* AppMsgFactory::get_app_message(AppMsgType msg_type) {
        assert(_creation_map != nullptr);
        std::map<AppMsgType, app_msg_creation_delegate>::iterator iter;
        iter = _creation_map->find(msg_type);
        if (iter == _creation_map->end()) {
            std::cout << "ERROR. AppMsgFactory create_message() failed.\n";
            // create NullMsg on error
            assert( msg_type != AppMsg::null);
            iter = _creation_map->find(AppMsg::null);
        }
        app_msg_creation_delegate delegate = iter->second;
        // TOOD:
        // MsgArgs takes in time. Make Time class so I can call Time::zero or something
        return delegate(zero_new EmptyMsgArgs(0));
    }

    void AppMsgFactory::register_app_messages() {
        assert(_creation_map != nullptr);
        _creation_map->insert(std::make_pair(AppMsg::null, NullMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::mouse_motion, MouseMotionMsg::create)); 
        _creation_map->insert(std::make_pair(AppMsg::quit, QuitMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::unhandled, UnhandledMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::window, WindowMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::system, SystemMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::keydown, KeyDownMsg::create));
        _creation_map->insert(std::make_pair(AppMsg::keyup, KeyUpMsg::create));
    }
}