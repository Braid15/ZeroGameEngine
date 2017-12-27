#include "GameApp.h" 
#include "../Events/Events.h"

namespace ZeroEngine {

    GameApp::GameApp() {
        _game_logic = nullptr;
        _framework = nullptr;
        ZeroEventManager::initialize();
    }

    GameApp::~GameApp() {

    }

    GameApp* GameApp::_app = nullptr;

    GameApp* const GameApp::instance() {
        return GameApp::_app;
    }

    void GameApp::set_instance(GameApp* app) {
        if (_app == nullptr) {
            _app = app;
        } else {
            LOG_DEBUG("GameApp", "Attempting to set multiple GameApp instances");
        }
    }

    bool GameApp::app_msg_proc(AppMsg::ptr msg) {
        assert(GameApp::instance() != nullptr);
        bool result = false;

        if (GameApp::instance()->get_game_logic() != nullptr) {
            BaseGameLogic* game = GameApp::instance()->get_game_logic();

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

    void GameApp::update(Tick time) {
        assert(GameApp::instance() != nullptr);
        if (GameApp::instance()->get_game_logic() != nullptr) {
            ZeroEventManager::update(20);
            GameApp::instance()->get_game_logic()->update(time);
        } else {
            std::cout << "Game logic is null! ZeroEngineApp::update()\n";
        }
    }

    void GameApp::render(Tick time) {
        assert(GameApp::instance() != nullptr);

        if (GameApp::instance()->get_game_logic() != nullptr) {
            BaseGameLogic* logic = GameApp::instance()->get_game_logic();
            GameViewList list = logic->get_game_views();
            for (GameViewList::iterator iter = list.begin(); iter != list.end(); ++iter) {
                (*iter)->render(time);
            }

            // @TODO: Don't know when this should happen, but I'll put it here for now
            GameApp::instance()->get_renderer()->render_packets();

            logic->render_diagnostics();
        }
    }


    // @TODO: Should return weak pointer??
    IRenderer::s_ptr GameApp::get_renderer() const {
        assert(_framework);
        return _framework->get_renderer();
    }

    Tick GameApp::get_ticks() const {
        return _framework->get_current_time();
    }

    Point<int32_t> GameApp::get_screen_size() const {
        return _game_options.get_screen_size();
    }

    HumanView::ptr GameApp::get_human_view(uint32_t player_number) {
        HumanView::ptr ret_view = HumanView::ptr();
        GameViewList views = _game_logic->get_game_views();

        for (GameViewList::iterator iter = views.begin(); iter != views.end(); ++iter) {
            if ((*iter)->get_type() == GameViewType::human) {
                HumanView::ptr human_view = std::static_pointer_cast<HumanView>((*iter));
                if (human_view->get_player_number() == player_number) {
                    ret_view = human_view;
                    break;
                }
            }
        }

        return ret_view;
    }

    bool GameApp::initialize() {
        bool success = false;
        assert(_framework != nullptr);
        if (_framework->initialize()) {
            if (_framework->initialize_window_and_renderer(get_game_title(), get_screen_size())) {
                _framework->set_app_msg_callback(GameApp::app_msg_proc);
                _framework->set_update_callback(GameApp::update);
                _framework->set_render_callback(GameApp::render);

                register_engine_events();
                register_game_events();

                _game_logic = create_game_and_view();
                set_is_running(true);
                GameApp::set_instance(this);
                success = true;
            }
        }
        return success;
    }

    bool GameApp::load_game() {
        return _game_logic->load_game();
    }

    void GameApp::shutdown() {
        set_is_running(false);
        zero_delete(_game_logic);

        _framework->shutdown();
        zero_delete(_framework);
        ZeroEventManager::shutdown();
    }

    void GameApp::run() {
        assert(_framework != nullptr);
        _framework->run_main_loop();
    }

    GameApp::GameApp(GameOptions& options) {
        ZeroEventManager::initialize();
        _is_running = false;
        _save_game_directory = std::string();
        _game_options = options;
    }

    void GameApp::set_is_running( bool running ) {
        _is_running = running;
    }

    void GameApp::set_save_game_directory( std::string dir ) {
        _save_game_directory = dir;
    }

    /* private methods */

    void GameApp::register_engine_events() {
    }
}