#include "AFramework.h"

namespace ZeroEngine {

    AFramework::AFramework() {
        _msg_translator = nullptr; 
        _is_running = false;
    }

    AFramework::~AFramework() {
        //zero_delete(_msg_translator);
    }

    // @@TODO: Experimenting with main_loop design
    // Game Programming Patterns Pg.123. + references at end of chapter.
    void AFramework::run_main_loop() {
        Time update_limit = 0.10;
        Time previous_time = get_current_time();
        Time lag = 0.0;
        while (_is_running) {
            Time current_time = get_current_time();
            Time delta_time = current_time - previous_time;
            previous_time = current_time;
            lag += delta_time;

            process_input();

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

    void AFramework::dispatch_message() {
        const AppMsg* const msg = _msg_translator->get_translated_message();
        // @@TEMP: _is_running should be switched via EventMaanager registered function
        _is_running = msg->get_type() != AppMsg::quit;

        // @TODO: I don'd know if I want these here or not, but regardless,
        // I want a better way to update these without public methods
        if (msg->get_type() == AppMsg::keyboard) {
            Keyboard::set(KeyboardMsg::cast(msg));
        }
        if (msg->get_type() == AppMsg::mouse_motion) {
            Mouse::set(MouseMotionMsg::cast(msg));
        }
        if (msg->get_type() == AppMsg::mouse_button) {
            Mouse::set(MouseButtonMsg::cast(msg));
        }
        if (msg->get_type() == AppMsg::mouse_wheel) {
            Mouse::set(MouseWheelMsg::cast(msg));
        }

        _app_msg_callback(msg);
    }

    bool AFramework::initialize() {
        _is_running = on_init() && (_msg_factory != nullptr) && (_msg_translator != nullptr);
        return _is_running;
    }

    bool AFramework::shutdown() {
        _is_running = false;
        return on_shutdown();
    }

    // @@TODO: Use shared_ptr
    void AFramework::set_app_msg_translator(IMsgTranslator* msg_translator) {
        _msg_translator = msg_translator;
    }
}