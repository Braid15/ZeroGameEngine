#include "AppMsgFactory.h"

namespace ZeroEngine {

    AppMsgFactory::AppMsgFactory() {
        _current_message = nullptr;
        _memory_pool = zero_new MemoryPool();
        _memory_pool->initialize(sizeof(AppMsg), 1, "AppMsgFactory");
    }

    AppMsgFactory::~AppMsgFactory() {
        free_current_message();
        zero_delete(_memory_pool);
    }

    AppMsgPtr AppMsgFactory::create_message(AppMsgType msg_type) {
        free_current_message();
        switch (msg_type) {
            case QUIT_MSG:
                _current_message = (QuitMsg*)_memory_pool->allocate();
                break;
            case MOUSE_MSG:
                _current_message = (MouseMsg*)_memory_pool->allocate();
                break;
            case NULL_MSG:
            default:
                _current_message = (NullMsg*)_memory_pool->allocate();
                break;
        }
        std::cout << _current_message->to_string() << std::endl;
        return _current_message;
    }

    void AppMsgFactory::free_current_message() {
        assert(_memory_pool != nullptr);
        if (_current_message) {
            _memory_pool->free_memory(_current_message);
        }
    }
}