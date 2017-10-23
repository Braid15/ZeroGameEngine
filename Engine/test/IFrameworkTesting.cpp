#ifdef _DEBUG

#include "IFrameworkTesting.h"

namespace IFrameworkTesting {

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
        _update_callback( 0 );

    }

    void MockFramework::frame_render( Time delta_time ) {
        _render_callback( 0 );
        SDL_UpdateWindowSurface( _window );
    }
}

#endif