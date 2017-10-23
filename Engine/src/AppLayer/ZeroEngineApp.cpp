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

    bool ZeroEngineApp::on_app_msg( AppMsg& msg ) {
        std::cout << msg.to_string() << std::endl;
        return true;
    }

    void ZeroEngineApp::on_update( Time time ) {
        // std::cout << "ZeroEngineApp::on_update()" << std::endl;
    }

    void ZeroEngineApp::on_render( Time time ) {
        // std::cout << "ZeroEngineApp::on_render()" << std::endl;
    }





    /* Public */

    ZeroEngineApp::~ZeroEngineApp() {
        if ( ZeroEngineApp::_app ) {
            delete ZeroEngineApp::_app;
        }
    }

    bool ZeroEngineApp::is_running() const {
        return _is_running;
    }

    const Point<long>& ZeroEngineApp::get_screen_size() const {
        return _screen_size;
    }

    bool ZeroEngineApp::initialize() {
        bool success = true;
        register_engine_events();
        set_is_running( true );
        set_screen_size( Point<long>( 640, 480 ) );
        return success;
    }

    void ZeroEngineApp::shutdown() {
        set_is_running( false );
    }


    /* Protected */

    ZeroEngineApp::ZeroEngineApp() {
        ZeroEngineApp::_app = nullptr;
        _is_running = false;
        _screen_size = Point<long>();
        _save_game_directory = std::string(); 
    }

    void ZeroEngineApp::set_screen_size( Point<long> point ) {
        _screen_size = point; 
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