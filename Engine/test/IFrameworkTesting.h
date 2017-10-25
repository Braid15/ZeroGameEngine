#ifdef _DEBUG

#include "../src/ZeroEngine.h"
#include "../src/3rdParty/SDL/SDL.h"
#include "../src/3rdParty/SDL/SDL_syswm.h"

using namespace ZeroEngine;

namespace IFrameworkTesting {

    class MockFramework : public AFramework {
        SDL_Window* _window;
        SDL_Surface* _surface;

    public:
        inline MockFramework(): 
            _window( nullptr ),
            _surface( nullptr )
        {}

    public:
        inline IRenderer* create_renderer() { return nullptr; }
        inline IWindow* create_window() { return nullptr; }
        bool initialize();
        bool shutdown();
        bool get_app_msg() override;
        void frame_begin( Time delta_time ) override;
        void frame_render( Time delta_time ) override;
        inline StringRepr to_string() const { return "MockFramework"; }
    };


    //
    // MockFrameworkTwo
    class MockFrameworkTwo : public AFramework {
        static MockFrameworkTwo* _instance;
        static MSG _msg;
        HWND _window;
        WNDCLASS _wnd_class;
        HINSTANCE _h_instance;
        TCHAR _class_name;
        LONG_PTR _original_wnd_proc;
        int _show_cmd;
        SDL_Window* _sdl_window;
        SDL_Surface* _surface;


    public:
        static MockFrameworkTwo* instance();
        static LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

        void main_loop() override;
        inline IRenderer* create_renderer() { return nullptr; }
        inline IWindow* create_window() { return nullptr; }
        bool initialize();
        bool shutdown();
        bool get_app_msg() override;
        void frame_begin( Time delta_time ) override;
        void frame_render( Time delta_time ) override;
        inline void set_h_instance( HINSTANCE h_instance ) { _h_instance = h_instance; }
        inline void set_show_cmd( int show_cmd ) { _show_cmd = show_cmd; }
        inline void set_class_name( TCHAR class_name ) { _class_name = class_name; }
        inline void set_h_wnd( HWND window ) { _window = window; }
        inline StringRepr to_string() const { return "MockFrameworkTwo"; }

    private:
        inline MockFrameworkTwo() {};
        inline void delete_current_message() { delete _current_message; }
        inline void set_current_message( AppMsg* msg ) { _current_message = msg; }
    };
}

#endif