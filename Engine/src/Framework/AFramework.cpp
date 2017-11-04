#include "AFramework.h"

namespace ZeroEngine {

    AFramework::AFramework() {
        _current_message = nullptr;
        _message_factory = zero_new AppMsgFactory();
        _is_running = true;
    }

    AFramework::~AFramework() {
        zero_delete(_current_message);
        zero_delete(_message_factory);
        _is_running = false;
    }

    void AFramework::main_loop() {
        Time time = 0;
        while (_is_running) {
            get_app_msg();
            frame_begin( time );
            frame_render( time );
            frame_end( time );
        }
    }
}