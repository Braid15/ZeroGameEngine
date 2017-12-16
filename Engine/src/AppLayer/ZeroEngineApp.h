#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Graphics.h"
#include "../Time.h"
#include "../AppMsg/AppMsg.h"
#include "../Input/Keys.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"
#include "GameOptions.h"
#include "../Events/Events.h"
#include "../GameLogic/GameLogicInclude.h"
#include "../GameView/GameViewInclude.h"

namespace ZeroEngine {

    // @TODO: Rename this file to GameApp instead of ZeroEngineApp

    class GameApp : public IZeroObject {
    private:
        bool _is_running;
        std::string _save_game_directory;
        static GameApp* _app;
        BaseGameLogic* _game_logic;
    public:
        virtual const std::string get_game_title() = 0;
        virtual const std::string get_game_app_directory() = 0;

        GameApp();
        static bool app_msg_proc(AppMsg::ptr msg);
        static void update(Tick time);
        static void render(Tick time);

        virtual bool load_game();
        inline BaseGameLogic* get_game_logic() const { return _game_logic; }
        HumanView::ptr get_human_view(uint32_t player_number=INVALID_PLAYER_NUMBER);

        // TODO: 10/4/17 - using this instead of global pointer for now.
        // we will see how it works
        static GameApp* const instance();
        static void set_app(GameApp* app);
        virtual StringRepr to_string() const override { return "ZeroEngineApp"; }
        virtual ~GameApp();
        bool initialize();
        void shutdown();
        inline bool is_running() const { return _is_running; }
        Point<int32_t> get_screen_size() const;
    protected:
        virtual BaseGameLogic* create_game_and_view() = 0;

        inline virtual void register_game_events() {};
        GameOptions _game_options;
        GameApp( GameOptions& );
        void set_is_running( bool running );
        void set_save_game_directory( std::string dir );
    private:
        void register_engine_events();
    };

}
