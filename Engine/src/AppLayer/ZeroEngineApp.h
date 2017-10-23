#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Graphics.h"

namespace ZeroEngine {


    class ZeroEngineApp : public IZeroObject {

    /* abstract interface */
    public:
        virtual const std::string get_game_title() = 0;
        virtual const std::string get_game_app_directory() = 0;
        virtual bool load_game() = 0;

    protected:
        virtual void register_game_events_() = 0;

    /* static interface */
    public:
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
        const Point<long>& get_screen_size() const;
        bool is_running() const;
        
    protected:
        ZeroEngineApp();

    /* Protected Methods */
    protected:
        void set_is_running( bool running );
        void set_save_game_directory( std::string dir );
        void set_screen_size( Point<long> point );

    private:
        void register_engine_events();
        Point<long> _screen_size;
        bool _is_running;
        std::string _save_game_directory;
        static ZeroEngineApp* _app;

    /* IZeroObject */
    public:
        virtual StringRepr to_string() const override { return "ZeroEngineApp"; }
    };

}
