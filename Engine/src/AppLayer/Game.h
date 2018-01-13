#pragma once

// #include "GameApp.h"
#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Framework/IRenderer.h"
#include "../Entity/Entity.h"


namespace ZeroEngine {

    class Entity;
    class GameApp;
    class IPhysics;

    //
    // Provides a global way to access certain methods from GameApp.
    //

    class Game {
    private:
        static GameApp* _app_instance;
    public:
        static std::shared_ptr<IPhysics> get_physics();
        static Tick get_ticks();
        static IRenderer::s_ptr get_renderer();
        static void set(GameApp* app);
        static Uint32 get_entity_count();
        static std::weak_ptr<Entity> get_entity(const EntityId& id);
        static Uint32 get_screen_width();
        static Uint32 get_screen_height();
    };
}
