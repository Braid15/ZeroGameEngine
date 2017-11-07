#include "AFramework.h"

namespace ZeroEngine {

    AFramework::AFramework() {
        _message_factory = zero_new AppMsgFactory();;
        _message_translator = nullptr; 
        _current_message = 0;
        _is_running = false;
    }

    AFramework::~AFramework() {
        zero_delete(_message_factory);
        zero_delete(_message_translator);
    }

    // @@TODO: Experimenting with main_loop design
    // Game Programming Patterns Pg.123. + references at end of chapter.
    void AFramework::main_loop() {
        Time update_limit = 0.10;
        Time previous_time = get_current_time();
        Time lag = 0.0;
        while (_is_running) {
            Time current_time = get_current_time();
            Time delta_time = current_time - previous_time;
            previous_time = current_time;
            lag += delta_time;
            poll_message();

            // @@TODO: passing delta_time as function arg might not work
            // in this implementation
            while (lag >= update_limit) {
                lag -= update_limit;
                _update_callback(delta_time);
            }

            frame_render_begin(delta_time);
            frame_render_present(delta_time);
            frame_render_end(delta_time);
        }
    }


    void AFramework::dispatch_message(FrameworkMsgId msg_id) {
        AppMsgType msg_type = _message_translator->translate_message(msg_id);
        // TEMP
        _is_running = msg_type != QUIT_MSG;
        _app_msg_callback(*_message_factory->create_message(msg_type));
    }

    bool AFramework::initialize() {
        _is_running = on_init() && (_message_factory != nullptr) && (_message_translator != nullptr);
        return _is_running;
    }

    bool AFramework::shutdown() {
        _is_running = false;
        return on_shutdown();
    }

    void AFramework::set_app_msg_translator(IMsgTranslator* msg_translator) {
        _message_translator = msg_translator;
    }
}