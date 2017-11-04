#include "AppMsgFactory.h"

namespace ZeroEngine {

    AppMsgFactory::AppMsgFactory() {
        AppMsg::init_memory_pool();
        _current_message = new NullMsg(0);
    }

    AppMsgFactory::~AppMsgFactory() {
        delete _current_message;
        _current_message = nullptr;
        AppMsg::destroy_memory_pool();
    }

    AppMsgPtr AppMsgFactory::create_message(AppMsgType msg_type) {
        delete _current_message;
        switch (msg_type) {
            case QUIT_MSG:
                _current_message = new QuitMsg(0);
                break;
            case MOUSE_MSG:
                _current_message = new MouseMsg(0);
                break;
            case NULL_MSG:
            default:
                _current_message = new NullMsg(0);
                break;
        }
        return _current_message;
    }
}