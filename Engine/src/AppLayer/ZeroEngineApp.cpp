#include "ZeroEngineApp.h" 

namespace ZeroEngine {

    ZeroEngineApp::ZeroEngineApp() {
        _game_logic = nullptr;
    }

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
        bool result = false;

        if (ZeroEngineApp::instance()->get_game_logic() != nullptr) {
            BaseGameLogic* game = ZeroEngineApp::instance()->get_game_logic();

            GameViewList list = game->get_game_views();
            for (GameViewList::reverse_iterator iter = list.rbegin(); iter != list.rend(); ++iter) {
                if ((*iter)->msg_proc(msg)) {
                    result = true;
                    break;
                }
            }
        } else {
            std::cout << "Game logic is null! ZeroEngineApp::app_msg_proc\n";
        }

        return result;
    }

    void ZeroEngineApp::update(Tick time) {
        assert(ZeroEngineApp::instance() != nullptr);
        if (ZeroEngineApp::instance()->get_game_logic() != nullptr) {
            ZeroEventManager::update(20);
            ZeroEngineApp::instance()->get_game_logic()->update(time);
        } else {
            std::cout << "Game logic is null! ZeroEngineApp::update()\n";
        }
    }

    void ZeroEngineApp::render(Tick time) {
        assert(ZeroEngineApp::instance() != nullptr);

        if (ZeroEngineApp::instance()->get_game_logic() != nullptr) {
            BaseGameLogic* logic = ZeroEngineApp::instance()->get_game_logic();
            GameViewList list = logic->get_game_views();
            for (GameViewList::iterator iter = list.begin(); iter != list.end(); ++iter) {
                (*iter)->render(time);
            }

            logic->render_diagnostics();
        }
    }

    ZeroEngineApp::~ZeroEngineApp() {
        zero_delete(_game_logic);
    }

    Point<long> ZeroEngineApp::get_screen_size() const {
        return _game_options.get_screen_size();
    }

    bool ZeroEngineApp::initialize() {
        bool success = true;
        register_engine_events();
        register_game_events();
        _game_logic = create_game_and_view();
        set_is_running(true);
        return success;
    }

    bool ZeroEngineApp::load_game() {
        return _game_logic->load_game();
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