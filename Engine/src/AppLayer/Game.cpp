#include "Game.h"
#include "GameApp.h"

namespace ZeroEngine {

    GameApp* Game::_app_instance = nullptr;

    Tick Game::get_ticks() {
        return _app_instance->get_ticks();
    }

    IRenderer::s_ptr Game::get_renderer() {
        return _app_instance->get_renderer();
    }

    void Game::set(GameApp* app) {
        if (_app_instance == nullptr) {
            _app_instance = app;
        } else {
            LOG_DEBUG("Game", "Attempting to set multiple app instances");
        }
    }

    uint32_t Game::get_entity_count() {
        return _app_instance->get_game_logic()->get_entity_count();
    }
}