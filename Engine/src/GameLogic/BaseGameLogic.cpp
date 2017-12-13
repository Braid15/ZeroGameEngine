#include "BaseGameLogic.h"

namespace ZeroEngine {

    BaseGameLogic::BaseGameLogic() {
        _physics = IPhysicsPtr(zero_new NullPhysics());
        _lifetime = 0;
        _entity_manager = zero_new EntityManager();
        _current_state = BaseGameState::invalid;
        _render_diagnostics = false;
        _is_proxy = false;
        _human_players_attached = 0;
        _ai_players_attached = 0;
        _human_games_loaded = 0;
    }

    BaseGameLogic::~BaseGameLogic() {
        while (!_game_views.empty()) {
            _game_views.pop_front();
        }
        zero_delete(_entity_manager);
        _current_state = BaseGameState::invalid;
    }

    bool BaseGameLogic::initialize() {
        bool success = true;
        // register delegates
        return success;
    }

    bool BaseGameLogic::shutdown() {
        bool success = true;
        _entity_manager->shutdown();
        // unregister delegates
        return success;
    }
}