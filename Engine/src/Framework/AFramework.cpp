#include "AFramework.h"

namespace ZeroEngine {

    AFramework::AFramework() {
        _message_factory = zero_new AppMsgFactory();
        _current_message = 0;
        _message_translator = nullptr;
        _is_running = true;
    }

    AFramework::~AFramework() {
        zero_delete(_message_factory);
        zero_delete(_message_translator);
        _is_running = false;
    }

    void AFramework::main_loop() {
        Time time = 0;
        while (_is_running) {
            dispatch_message();
            frame_begin( time );
            frame_render( time );
            frame_end( time );
        }
    }
}