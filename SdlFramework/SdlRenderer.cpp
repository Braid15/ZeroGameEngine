#include "stdafx.h"
#include "SdlRenderer.h"
#include "SdlTexture.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2_ttf.lib")

namespace ZeroSdlFramework {

    using namespace ZeroEngine;

    SdlRenderer::SdlRenderer(SDL_Window* window) {
        _sdl_window = window;
        set_background_color(Colors::black());
        _sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!_sdl_renderer) {
            std::cout << "SDL_Error: " << SDL_GetError() << "\n";
        }
        set_primitive_renderer(zero_new SdlPrimitiveRenderer(this));
    }

    SdlRenderer::~SdlRenderer() {
        // Do not destroy _sdl_window!!
        if (_sdl_renderer) {
            SDL_DestroyRenderer(_sdl_renderer);
            _sdl_renderer = nullptr;
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

    ITexture* SdlRenderer::create_texture(const char* file_path) {
        return zero_new SdlTexture(_sdl_renderer, _sdl_window, file_path);
    }

    void SdlRenderer::draw_line(const Point<Int32>& from, const Point<Int32>& to, const Color& color) {
        SDL_SetRenderDrawColor(_sdl_renderer, color.get_red(), color.get_green(), color.get_blue(),
                               color.get_alpha());
        SDL_RenderDrawLine(_sdl_renderer, from.get_x(), from.get_y(), to.get_x(), to.get_y());
    }

    void SdlRenderer::render_present() {
        SDL_RenderPresent(_sdl_renderer);
    }

    // -----------------------------------
    // SdlPrimitiveRenderer Public Members
    // -----------------------------------


    void SdlPrimitiveRenderer::draw_line(const Vector2& start, const Vector2& end, 
                                         const Color& color) {
        set_color(color);
        SDL_RenderDrawLine(&_renderer->get_sdl_renderer(), static_cast<int>(start.get_x()),
                           static_cast<int>(start.get_y()), static_cast<int>(end.get_x()), static_cast<int>(end.get_y()));
    }

    void SdlPrimitiveRenderer::draw_point(const Point<Int32>& point, const Color& color) {
        set_color(color);
        SDL_RenderDrawPoint(&_renderer->get_sdl_renderer(), point.get_x(), point.get_y());
    }

    void SdlPrimitiveRenderer::draw_triangle(const Point<Int32>& v1, const Point<Int32>& v2,
                                             const Point<Int32>&v3, const Color& color) {
        set_color(color);
        LOG_UNIMPLEMENTED();
    }

    void SdlPrimitiveRenderer::draw_circle(const Point<Int32>& center, const Float32& radius,
                                           const Color& color) {
        set_color(color);
        LOG_UNIMPLEMENTED();
    }

    void SdlPrimitiveRenderer::draw_rect(const Rect& rect, const Color& color) {
        set_color(color);
        SDL_Rect sdl_rect = { 
            static_cast<int>(rect.get_x()), 
            static_cast<int>(rect.get_y()), 
            static_cast<int>(rect.get_width()), 
            static_cast<int>(rect.get_height())
        };

        SDL_RenderDrawRect(&_renderer->get_sdl_renderer(), &sdl_rect);
    }

    void SdlPrimitiveRenderer::draw_vertices(Vector2 vertices[], Int32 count, const Color& color) {
        LOG_TODO("SdlPrimitiveRenderer", "REFACTOR!");
        set_color(color);
        if (vertices) {
            for (int i = 0; i < count; i++) {
                if (i + 1 != count) {
                    SDL_RenderDrawLine(&_renderer->get_sdl_renderer(), static_cast<int>(vertices[i].get_x()), static_cast<int>(vertices[i].get_y()),
                                       static_cast<int>(vertices[i+1].get_x()), static_cast<int>(vertices[i+1].get_y()));
                } else {
                    SDL_RenderDrawLine(&_renderer->get_sdl_renderer(), static_cast<int>(vertices[i].get_x()), static_cast<int>(vertices[i].get_y()),
                                       static_cast<int>(vertices[0].get_x()), static_cast<int>(vertices[0].get_y()));
                }
            }
        }
    }

    void SdlPrimitiveRenderer::draw_text(const std::string& text, const Rect& canvas, const Color& color) {
        LOG_UNIMPLEMENTED();
    }

    // ------------------------------------
    // SdlPrimitiveRenderer Private Members
    // ------------------------------------

    void SdlPrimitiveRenderer::set_color(const Color& color) {
        SDL_SetRenderDrawColor(&_renderer->get_sdl_renderer(), color.get_red(),
                               color.get_green(), color.get_blue(), color.get_alpha());
    }




}