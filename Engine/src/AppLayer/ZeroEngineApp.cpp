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
        if (msg->get_type() == AppMsg::quit) {
            ZeroEventManager::queue_event(QuitEventData::create());
        }
        return true;
    }

    void ZeroEngineApp::on_update(Time time) {
        // std::cout << "ZeroEngineApp::on_update()" << std::endl;
        ZeroEventManager::update();
    }

    void ZeroEngineApp::on_render(Time time) {
        // std::cout << "ZeroEngineApp::on_render()" << std::endl;
    }

    ZeroEngineApp::~ZeroEngineApp() {
        EventListenerDelegate delegate = fastdelegate::MakeDelegate(this, &ZeroEngineApp::quit_event_delegate);
        ZeroEventManager::unregister_listener(delegate, QuitEventData::type);
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

    void ZeroEngineApp::quit_event_delegate(IEventDataPtr event_data) {
        std::shared_ptr<QuitEventData> quit_event = std::static_pointer_cast<QuitEventData>(event_data);
        std::cout << "ZeroEngineApp::quit_event_delegate() - " << std::to_string(quit_event->get_timestamp()) << "\n";
    }

    /* private methods */

    void ZeroEngineApp::register_engine_events() {
        EventListenerDelegate delegate = fastdelegate::MakeDelegate(this, &ZeroEngineApp::quit_event_delegate);
        ZeroEventManager::register_listener(delegate, QuitEventData::type);
    }
}