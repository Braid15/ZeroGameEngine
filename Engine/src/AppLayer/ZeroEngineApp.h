#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class EventManager;
    class HumanView;
    class GameOptions;

    class ZeroEngineApp : public IType {

    /* abstract interface */
    public:
        virtual const std::string get_game_title() = 0;
        virtual const std::string get_game_app_directory() = 0;
        // TODO: 10/4/17 - implement BaseGameLogic
        // virtual BaseGameLogic* create_game_and_view() = 0;
        virtual bool load_game() = 0;

    /* static interface */
    public:
        // TODO: 10/4/17 - need to get this platform independent
        //static LRESULT CALLBACK msg_proc()

        // TODO: 10/4/17 - using this instead of global pointer for now.
        // we will see how it works
        static ZeroEngineApp* const get_app();
        static void set_app( ZeroEngineApp* app );

    public:
        virtual ~ZeroEngineApp();

    /* methods */
    public:
        bool load_strings();
        bool load_strings( std::string language );
        std::wstring get_string( std::wstring id );
        int get_hotkey_for_string( std::wstring id );
        unsigned int map_char_to_key_code( const char hotkey );
        void abort_game();
        void on_close();


    /* getters/setters */
    public:
        const Point<long>& get_screen_size() const;
        const Rect& get_desktop_size() const;
        bool is_editor_running() const;
        HumanView* get_human_view();
        // TODO: 10/4/17 - implement BaseGameLogic
        // BaseGameLogic* get_game_logic() const;
        int get_exit_code() const;
        bool is_running() const;
        void set_quitting( bool quitting );
        
    protected:
        virtual void register_game_events();

    protected:
        ZeroEngineApp();
        // TODO: 10/1/17
        // This is windows specific. Need to change it out
        HINSTANCE instance_;
        bool is_running_;
        bool quit_requested_;
        bool is_quitting_;
        bool is_editor_running_;
        Point<long> screen_size_;
        Rect desktop_size_;
        std::map<std::wstring, std::wstring> text_resource_;
        std::map<std::wstring, unsigned int> hotkeys_;
        // TODO: 10/4/17 - implement GameOptions
        GameOptions* game_options_;
        std::string save_game_directory_;
        int exit_code_;
        // TODO: 10/4/17 - implement BaseGameLogic
        // BaseGameLogic* game_logic_;

    private:
        void register_engine_events();
        static ZeroEngineApp* _app;


    /* IType interface */
    public:
        virtual TypeName get_type() const override { return "ZeroEngineApp"; }
    };

}
