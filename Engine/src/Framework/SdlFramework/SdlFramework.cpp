#include "SdlFramework.h"

namespace ZeroEngine {

    bool SdlFramework::initialize() {
        _message_translator = zero_new SdlMessageTranslator();

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

        return success;
    }

    bool SdlFramework::shutdown() {
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

    bool SdlFramework::dispatch_message() {
        while (SDL_PollEvent(&_event) != 0) {
            // TEMP
            _is_running = _event.type != SDL_QUIT ? true : false;
            _current_message =  static_cast<FrameworkMessageId>(_event.type);
            AppMsgType msg_type = _message_translator->translate_message(_current_message);
            _app_msg_callback(*_message_factory->create_message(msg_type));
        }
        return true;
    }

    void SdlFramework::frame_begin(Time delta_time) {
        _update_callback(delta_time);
    }

    // @@TODO: Need pre-render and post-render
    void SdlFramework::frame_render(Time delta_time) {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        SDL_RenderClear(_renderer);
        _render_callback(delta_time);
        SDL_RenderPresent(_renderer);
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