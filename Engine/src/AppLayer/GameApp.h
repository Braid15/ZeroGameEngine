#pragma once

#include "../ZeroEngineStd.h"
#include "../Framework/Framework.h"
#include "../Graphics/Graphics.h"
#include "../Time.h"
#include "../AppMsg/AppMsg.h"
#include "../Input/Keys.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"
#include "GameOptions.h"
#include "../GameLogic/GameLogicInclude.h"
// #include "../GameLogic/BaseGameLogic.h"
#include "../GameView/GameViewInclude.h"

namespace ZeroEngine {

    class BaseGameLogic;

    class GameApp : public IZeroObject {
    private:
        static GameApp* _app;
        static void set_instance(GameApp* app);
        bool _is_running;
        std::string _save_game_directory;
        BaseGameLogic* _game_logic;
        AFramework* _framework;

    protected:
        GameOptions _game_options;

    public:
        GameApp();
        virtual ~GameApp();
        virtual const std::string get_game_title() = 0;
        virtual const std::string get_game_app_directory() = 0;

        static bool app_msg_proc(AppMsg::ptr msg);
        static void update(Tick time);
        static void render(Tick time);
        static GameApp* const instance();

        virtual bool load_game();
        void run();
        inline BaseGameLogic* get_game_logic() const { return _game_logic; }
        HumanView::ptr get_human_view(uint32 player_number=INVALID_PLAYER_NUMBER);

        IRenderer::s_ptr get_renderer() const;
        Tick get_ticks() const;
        inline void set_framework(AFramework* framework) { _framework = framework; }


        bool initialize();
        void shutdown();
        inline bool is_running() const { return _is_running; }
        Point<int32> get_screen_size() const;
        virtual StringRepr to_string() const override { return "ZeroEngineApp"; }

    protected:
        GameApp(GameOptions&);

        virtual BaseGameLogic* create_game_and_view() = 0;
        inline virtual void register_game_events() {};

        void set_is_running(bool running);
        void set_save_game_directory(std::string dir);
    private:
        void register_engine_events();
    };
}
