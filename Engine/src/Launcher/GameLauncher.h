#pragma once

#include "../ZeroEngineStd.h"
#include "../Framework/Framework.h"
#include "../AppLayer/GameOptions.h"
#include "../AppLayer/GameApp.h"
#include "../AppLayer/Game.h"
#include "../Utils/StringId.h"
namespace ZeroEngine {

    // @TODO: Should make different launchers for different platforms
    class GameLauncher {
    private:
        GameApp* _game;
    public:
        GameLauncher(GameApp* game, AFramework* framework) : _game(game) {
            _game = game;
            _game->set_framework(framework);
            Game::set(_game);
        }

        ~GameLauncher() {
            _game->shutdown();
            zero_delete(_game);

            StringIdManager::shutdown();

            // Make sure Logger is the last thing to be disposed of
            Logger::shutdown();
        }

        inline bool launch() {
            bool success = false;
            if (_game->initialize()) {
                _game->load_game();
                _game->run();
                success = true;
            } else {
                LOG_DEBUG("GameLauncher", "Error running game.");
            }
            return success;
        }

    private:
        GameLauncher() { _game = nullptr; }
        GameLauncher(const GameLauncher& other) { _game = nullptr; }
    };
}