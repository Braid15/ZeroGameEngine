#include "SdlFramework.h"

namespace ZeroEngine {

    bool SdlFramework::on_init() {
        bool success = true;
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }

        int image_flags = IMG_INIT_PNG;
        if (!(IMG_Init(image_flags) & image_flags)) {
            std::cout << "SDL_Error: " << IMG_GetError() << std::endl;
            success = false;
        }

        if (TTF_Init() == -1) {
            std::cout << "SDL_Error: " << TTF_GetError() << std::endl;
            success = false;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cout << "SDL_Error: " << Mix_GetError() << std::endl;
            success = false;
        }

        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "SDL Linear texture filtering not enabled" << std::endl;
        }

        // @@TODO: Use shared_ptr for translator so deletion isn't an issue
        _msg_translator = zero_new SdlMsgTranslator();
        set_app_msg_translator(_msg_translator);

        return success;
    }

    bool SdlFramework::on_shutdown() {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        _renderer = nullptr;
        _window = nullptr;
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return true;
    }

    void SdlFramework::process_input() {
        while (SDL_PollEvent(&_event) != 0) {
            _msg_translator->set_sdl_event_to_translate(_event);
            dispatch_message();
            // @@TODO:
            // 1) Need way to pass args to message_translator 
            // 2) fix confusion responsiblilities of derived vs base class
            // 3) fix confusion between AppMsgType, FrameworkMsgId, AppMsg
        }
    }

    void SdlFramework::frame_render_present(Time delta_time) {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
        _render_callback(delta_time);
        SDL_RenderPresent(_renderer);
    }

    // @@TODO: May change this to protected get_current_framework_time() 
    // and have AFramework have a public get_current_time() so that I have
    // more control over the time
    Time SdlFramework::get_current_time() const {
        return SDL_GetTicks();
    }

    IWindow* SdlFramework::create_window(std::string title, Point<long> size) {
        IWindow* ret_window = nullptr;
        _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, size.get_x(), 
                                   size.get_y(), SDL_WINDOW_SHOWN
        );
        if (!_window) {
            std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
        }
        return ret_window;
    }

    // @@TODO: Set vsync based off game options
    IRenderer* SdlFramework::create_renderer() {
        IRenderer* ret_renderer = nullptr;
        if (_window) {
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED
                                           | SDL_RENDERER_PRESENTVSYNC 
            );
            if (!_renderer) {
                std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
            }
        } else {
            std::cout << "Cannot create renderer without a window." << std::endl;
        }
        return ret_renderer;
    }
}