#ifdef _DEBUG

#include "IFrameworkTesting.h"

namespace IFrameworkTesting {


    void SDL_WindowsMessageHook( void* userdata, void* hWnd, unsigned int message,
                                 Uint64 wParam, Sint64 lParam ) {
        switch ( message ) {
            case WM_MOUSEMOVE:
                break;
        }
    }

    bool MockFramework::initialize() {

        bool success = false;
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
            std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            _window = SDL_CreateWindow( ZeroEngineApp::instance()->get_game_title().c_str(),
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       ZeroEngineApp::instance()->get_screen_size().get_x(),
                                       ZeroEngineApp::instance()->get_screen_size().get_y(),
                                       SDL_WINDOW_SHOWN 
            );
            if ( !_window ) {
                std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
            } else {
                _surface = SDL_GetWindowSurface( _window );
                SDL_SetWindowsMessageHook( SDL_WindowsMessageHook, NULL );
                success = true;
            }
        }
        return success;
    }

    bool MockFramework::shutdown() {
        SDL_FreeSurface( _surface );
        _surface = nullptr;
        SDL_DestroyWindow( _window );
        _window = nullptr;
        SDL_Quit();
        return true;
    }

    bool MockFramework::get_app_msg() {
        static SDL_Event event;
        while ( SDL_PollEvent( &event ) != 0 ) {
            std::cout << "SDL_PollEvent\n";
            switch ( event.type ) {
                case SDL_QUIT:
                    delete _current_message;
                    _current_message = new QuitMsg( event.common.timestamp );
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEWHEEL:
                    delete _current_message;
                    _current_message = new MouseMsg( event.common.timestamp );
                    break;
            }
            _app_msg_callback( *_current_message );
        }
        return true;
    }

    void MockFramework::frame_begin( Time delta_time ) {
        _update_callback( delta_time );
    }

    void MockFramework::frame_render( Time delta_time ) {
        _render_callback( delta_time );
        SDL_UpdateWindowSurface( _window );
    }



    //
    // MockFrameworkTwo
    //

    MockFrameworkTwo* MockFrameworkTwo::_instance = nullptr;
    MSG MockFrameworkTwo::_msg;

    MockFrameworkTwo* MockFrameworkTwo::instance() {
        if ( _instance == nullptr ) {
            _instance = new MockFrameworkTwo();
        }
        return _instance;
    }

    LRESULT CALLBACK MockFrameworkTwo::WndProc( HWND hwnd, UINT message,
                                                WPARAM wParam, LPARAM lParam ) {
        switch ( message ) {
            case WM_MOUSEMOVE:
                MockFrameworkTwo::instance()->delete_current_message();
                MockFrameworkTwo::instance()->set_current_message( 
                    new MouseMsg( _msg.time ) );
                break;
            case WM_DESTROY:
                PostQuitMessage( 0 );
                break;
        }
        MockFrameworkTwo::instance()->get_app_msg();
        return DefWindowProc( hwnd, message, wParam, lParam );
    }

    void MockFrameworkTwo::main_loop() {
        _msg.message = WM_NULL;
        while ( _msg.message != WM_QUIT ) {
            if ( PeekMessage( &_msg, NULL, 0U, 0U, PM_REMOVE ) ) {
                TranslateMessage( &_msg );
                DispatchMessage( &_msg );
            } else {
                frame_begin( _msg.time );
                frame_render( _msg.time );
            }
        }
    }

    bool MockFrameworkTwo::initialize() {
        bool success = false;

        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
            std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            _sdl_window = SDL_CreateWindow( ZeroEngineApp::instance()->get_game_title().c_str(),
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        ZeroEngineApp::instance()->get_screen_size().get_x(),
                                        ZeroEngineApp::instance()->get_screen_size().get_y(),
                                        SDL_WINDOW_SHOWN
            );
            if ( !_sdl_window ) {
                std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
            } else {
                SDL_SysWMinfo info;
                SDL_VERSION( &info.version );
                SDL_GetWindowWMInfo( _sdl_window, &info );
                char cls_name[ 256 ];
                if ( GetClassName( info.info.win.window, cls_name, 256 ) > 0 ) {
                    set_class_name( *cls_name );
                    set_show_cmd( 1 );
                    set_h_wnd( info.info.win.window );
                    GetClassInfo( GetModuleHandle( NULL ), &_class_name, &_wnd_class );
                    set_h_instance( _wnd_class.hInstance );
                    _original_wnd_proc = SetWindowLongPtr( 
                        _window, GWLP_WNDPROC, (LONG_PTR)MockFrameworkTwo::WndProc );
                    success = true;
                } else {
                    std::cout << GetLastError() << "\n";
                }
            }
        }

        return success;
    }

    bool MockFrameworkTwo::shutdown() {

        std::cout << "hWnd: " <<_window << "\n";
        std::cout << "SDL: " << _sdl_window << "\n";

        DestroyWindow( _window );
        _window = nullptr;
        SDL_DestroyWindow( _sdl_window );
        _sdl_window = nullptr;
        SDL_Quit();
        return true;
    }

    bool MockFrameworkTwo::get_app_msg() {
        return _app_msg_callback( *_current_message );
    }

    void MockFrameworkTwo::frame_begin( Time delta_time ) {
        _update_callback( delta_time );
    }

    void MockFrameworkTwo::frame_render( Time delta_time ) {
        _render_callback( delta_time );
        UpdateWindow( _window );
    }
}

#endif