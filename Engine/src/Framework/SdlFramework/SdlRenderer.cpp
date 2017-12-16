#include "SdlRenderer.h"

namespace ZeroEngine {

    SdlRenderer::SdlRenderer(SDL_Window* window) {
        _background_color = Colors::black();
        _sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!_sdl_renderer) {
            std::cout << "SDL_Error: " << SDL_GetError() << "\n";
        }
    }

    void SdlRenderer::set_background_color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {
        _background_color.set_red(red);
        _background_color.set_green(green);
        _background_color.set_blue(blue);
        _background_color.set_alpha(alpha);
    }

    void SdlRenderer::set_background_color(const Color& color) {
        _background_color.set_red(color.get_red());
        _background_color.set_green(color.get_green());
        _background_color.set_blue(color.get_blue());
        _background_color.set_alpha(color.get_alpha());
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
        SDL_SetRenderDrawColor(_sdl_renderer, _background_color.get_red(),
                               _background_color.get_green(), _background_color.get_blue(),
                               _background_color.get_alpha());
        SDL_RenderClear(_sdl_renderer);
        return success;
    }

    bool SdlRenderer::post_render() {
        bool success = true;
        // @TEMP
        SDL_RenderPresent(_sdl_renderer);
        return success;
    }

    void SdlRenderer::draw_line(const Point<float_t>& from, const Point<float_t>& to, const Color& color) {

    }

}