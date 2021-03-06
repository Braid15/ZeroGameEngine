#include "AFramework.h"

namespace ZeroEngine {

    AFramework::AFramework() {
        _msg_translator = nullptr; 
        _is_running = false;
        _window = nullptr;
        _renderer = BaseRenderer::s_ptr(zero_new NullRenderer());
    }

    AFramework::~AFramework() {
        //zero_delete(_msg_translator);
        _window = nullptr;
        _renderer = nullptr;
    }

    // @@TODO: Experimenting with main_loop design
    // Game Programming Patterns Pg.123. + references at end of chapter.
    void AFramework::run_main_loop() {
        Tick update_limit = 0.10;
        Tick previous_time = get_current_time();
        Tick lag = 0.0;
        while (_is_running) {
            Tick current_time = get_current_time();
            Tick delta_time = current_time - previous_time;
            previous_time = current_time;
            lag += delta_time;

            process_input();

            // @@TODO: passing delta_time as function arg might not work
            // in this implementation
            // while (lag >= update_limit) {
            //     lag -= update_limit;
            //     _update_callback(delta_time);
            // }
            _update_callback(delta_time);

            _render_callback(delta_time);

            _renderer->render_present();
        }
    }

    void AFramework::dispatch_message() {
        const AppMsg* const msg = _msg_translator->get_translated_message();
        // @@TEMP: _is_running should be switched via EventMaanager registered function
        _is_running = !msg->is_type(QuitMsg::type);

        // @TODO: I don'd know if I want these here or not, but regardless,
        // I want a better way to update these without public methods
        if (msg->is_type(KeyboardMsg::type)) {
            Keyboard::set(KeyboardMsg::cast(msg));
        }
        if (msg->is_type(MouseMotionMsg::type)) {
            Mouse::set(MouseMotionMsg::cast(msg));
        }
        if (msg->is_type(MouseButtonMsg::type)) {
            Mouse::set(MouseButtonMsg::cast(msg));
        }
        if (msg->is_type(MouseWheelMsg::type)) {
            Mouse::set(MouseWheelMsg::cast(msg));
        }

        _app_msg_callback(msg);
    }

    bool AFramework::initialize() {
        _is_running = on_init() && (_msg_factory != nullptr) && (_msg_translator != nullptr);
        return _is_running;
    }

    bool AFramework::initialize_window_and_renderer(std::string title, Point<Int32> size) {
        _window = create_window(title, size);
        _renderer = create_renderer();
        return (_window != nullptr && _renderer != nullptr);
    }

    bool AFramework::shutdown() {
        _is_running = false;
        _renderer->shutdown();
        _window->shutdown();
        return on_shutdown();
    }

    // @@TODO: Use shared_ptr
    void AFramework::set_app_msg_translator(IMsgTranslator* msg_translator) {
        _msg_translator = msg_translator;
    }
}