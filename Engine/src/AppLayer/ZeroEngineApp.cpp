#include "ZeroEngineApp.h" 

namespace ZeroEngine {

    /* Static */

    ZeroEngineApp* ZeroEngineApp::_app = nullptr;

    ZeroEngineApp* const ZeroEngineApp::instance() {
        return ZeroEngineApp::_app;
    }

    void ZeroEngineApp::set_app( ZeroEngineApp* app ) {
        if ( _app == nullptr ) {
            _app = app;
        }
    }

    bool ZeroEngineApp::app_msg_proc(const AppMsg* const msg) {
        assert(ZeroEngineApp::instance() != nullptr);
        return ZeroEngineApp::instance()->on_msg_proc(msg);
    }

    void ZeroEngineApp::update(Ticks time) {
        assert(ZeroEngineApp::instance() != nullptr);
        ZeroEventManager::update();
        ZeroEngineApp::instance()->on_update(time);
    }

    void ZeroEngineApp::render(Ticks time) {
        assert(ZeroEngineApp::instance() != nullptr);
        ZeroEngineApp::instance()->on_render(time);
    }

    ZeroEngineApp::~ZeroEngineApp() {
    }

    bool ZeroEngineApp::is_running() const {
        return _is_running;
    }

    Point<long> ZeroEngineApp::get_screen_size() const {
        return _game_options.get_screen_size();
    }

    bool ZeroEngineApp::initialize() {
        bool success = true;
        register_engine_events();
        register_game_events();
        set_is_running( true );
        return success;
    }

    void ZeroEngineApp::shutdown() {
        set_is_running(false);
    }


    ZeroEngineApp::ZeroEngineApp( GameOptions& options ) {
        _is_running = false;
        _save_game_directory = std::string();
        _game_options = options;
    }

    void ZeroEngineApp::set_is_running( bool running ) {
        _is_running = running;
    }

    void ZeroEngineApp::set_save_game_directory( std::string dir ) {
        _save_game_directory = dir;
    }

    /* private methods */

    void ZeroEngineApp::register_engine_events() {
    }
}