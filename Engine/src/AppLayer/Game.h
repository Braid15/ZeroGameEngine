#pragma once

// #include "GameApp.h"
#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Framework/IRenderer.h"


namespace ZeroEngine {

    class GameApp;

    //
    // Provides a global way to access certain methods from GameApp.
    //

    class Game {
    private:
        static GameApp* _app_instance;
    public:
        static Tick get_ticks();
        static IRenderer::ptr get_renderer();
        static void set(GameApp* app);
    };
}
