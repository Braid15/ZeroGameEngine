#pragma once

#include "../../ZeroEngineStd.h"
#include "../IRenderer.h"
#include "SdlFramework.h"

namespace ZeroEngine {

    class SdlRenderer : public BaseRenderer {
    private:
        SDL_Renderer* _sdl_renderer;
    public:
        // @TEMP: SHould be created with SdlWindow
        SdlRenderer(SDL_Window* window);
        void shutdown() override;
        bool on_restore() override;
        bool pre_render() override;
        bool post_render() override;
        void render_present() override;
        void draw_line(const Point<int32_t>& from, const Point<int32_t>& to, const Color& color) override;
        inline StringRepr to_string() const { return "SdlRenderer"; }
    private:
        inline SdlRenderer(const SdlRenderer&) {}
    };
}
