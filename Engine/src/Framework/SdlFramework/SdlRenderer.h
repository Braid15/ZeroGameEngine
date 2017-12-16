#pragma once

#include "../../ZeroEngineStd.h"
#include "../IRenderer.h"
#include "SdlFramework.h"

namespace ZeroEngine {

    class SdlRenderer : public IRenderer, public IZeroObject {
    private:
        SDL_Renderer* _sdl_renderer;
        Color _background_color;
    public:
        // @TEMP: SHould be created with SdlWindow
        SdlRenderer(SDL_Window* window);
        void set_background_color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) override;
        void set_background_color(const Color& color) override;
        void shutdown() override;
        bool on_restore() override;
        bool pre_render() override;
        bool post_render() override;
        void draw_line(const Point<float_t>& from, const Point<float_t>& to, const Color& color) override;
        inline StringRepr to_string() const { return "SdlRenderer"; }
    private:
        inline SdlRenderer(const SdlRenderer&) {}
    };
}
