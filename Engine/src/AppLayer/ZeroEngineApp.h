#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Graphics.h"
#include "../Time.h"
#include "../AppMsg/AppMsg.h"
#include "GameOptions.h"

namespace ZeroEngine {


    class ZeroEngineApp : public IZeroObject {
        bool _is_running;
        std::string _save_game_directory;
        static ZeroEngineApp* _app;

    /* abstract interface */
    public:
        virtual const std::string get_game_title() = 0;
        virtual const std::string get_game_app_directory() = 0;
        virtual bool load_game() = 0;

    protected:
        virtual void register_game_events_() = 0;

    public:
        // @@TODO: THis might cause problems. How will derived class override?
        static bool on_app_msg( AppMsg& msg );
        static void on_update( Time time );
        static void on_render( Time time );

        // TODO: 10/4/17 - using this instead of global pointer for now.
        // we will see how it works
        static ZeroEngineApp* const instance();
        static void set_app( ZeroEngineApp* app );

    public:
        virtual ~ZeroEngineApp();

    /* methods */
    public:
        bool initialize();
        void shutdown();

    /* getters/setters */
    public:
        Point<long> get_screen_size() const;
        bool is_running() const;
        
    protected:
        GameOptions _game_options;
        ZeroEngineApp( GameOptions& );

    /* Protected Methods */
    protected:
        void set_is_running( bool running );
        void set_save_game_directory( std::string dir );

    private:
        inline ZeroEngineApp() {}
        void register_engine_events();


    /* IZeroObject */
    public:
        virtual StringRepr to_string() const override { return "ZeroEngineApp"; }
    };

}
