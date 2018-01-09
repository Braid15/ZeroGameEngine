#include "Game.h"
#include "GameApp.h"
#include "../Entity/Entity.h"

namespace ZeroEngine {

    GameApp* Game::_app_instance = nullptr;

    Tick Game::get_ticks() {
        assert(_app_instance);
        return _app_instance->get_ticks();
    }

    IRenderer::s_ptr Game::get_renderer() {
        assert(_app_instance);
        LOG_TODO("Game", "Provide different interface for client code to interact with renderer");
        return _app_instance->get_renderer();
    }

    void Game::set(GameApp* app) {
        if (_app_instance == nullptr) {
            _app_instance = app;
        } else {
            LOG_DEBUG("Game", "Attempting to set multiple app instances");
        }
    }

    std::shared_ptr<IPhysics> Game::get_physics() {
        assert(_app_instance);
        return _app_instance->get_game_logic()->get_physics();
    }

    Uint32 Game::get_entity_count() {
        assert(_app_instance);
        return _app_instance->get_game_logic()->get_entity_count();
    }

    std::weak_ptr<Entity> Game::get_entity(const EntityId& id) {
        assert(_app_instance);
        return _app_instance->get_game_logic()->get_entity(id);
    }

    Uint32 Game::get_screen_width() {
        assert(_app_instance);
        return _app_instance->get_screen_size().get_x();
    }

    Uint32 Game::get_screen_height() {
        assert(_app_instance);
        return _app_instance->get_screen_size().get_y();
    }
}