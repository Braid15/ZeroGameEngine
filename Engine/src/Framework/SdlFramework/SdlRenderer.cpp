#include "SdlRenderer.h"

namespace ZeroEngine {

    SdlRenderer::SdlRenderer(SDL_Window* window) {
        set_background_color(Colors::black());
        _sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!_sdl_renderer) {
            std::cout << "SDL_Error: " << SDL_GetError() << "\n";
        }
    }

    void SdlRenderer::shutdown() {
        SDL_DestroyRenderer(_sdl_renderer);
        _sdl_renderer = nullptr;
    }

    bool SdlRenderer::on_restore() {
        bool success = true;
        return success;
    }

    bool SdlRenderer::pre_render() {
        bool success = true;
        SDL_SetRenderDrawColor(_sdl_renderer, get_background_color().get_red(),
                               get_background_color().get_green(), get_background_color().get_blue(),
                               get_background_color().get_alpha());
        SDL_RenderClear(_sdl_renderer);
        return success;
    }

    bool SdlRenderer::post_render() {
        bool success = true;
        // @TEMP
        return success;
    }

    void SdlRenderer::draw_line(const Point<int32_t>& from, const Point<int32_t>& to, const Color& color) {
        SDL_SetRenderDrawColor(_sdl_renderer, color.get_red(), color.get_green(), color.get_blue(),
                               color.get_alpha());
        SDL_RenderDrawLine(_sdl_renderer, from.get_x(), from.get_y(), to.get_x(), to.get_y());
    }

    void SdlRenderer::render_present() {
        SDL_RenderPresent(_sdl_renderer);
    }

}