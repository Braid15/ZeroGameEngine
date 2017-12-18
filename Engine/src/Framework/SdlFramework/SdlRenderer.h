#pragma once

#include "../../ZeroEngineStd.h"
#include "../IRenderer.h"
#include "../../Rendering/IPrimitiveRenderer.h"
#include "SdlFramework.h"

namespace ZeroEngine {

    class SdlRenderer : public BaseRenderer {
    private:
        friend class SdlPrimitiveRenderer;
        SDL_Renderer* _sdl_renderer;
    public:
        // @TEMP: SHould be created with SdlWindow
        SdlRenderer(SDL_Window* window);
        ~SdlRenderer();
        void shutdown() override;
        bool on_restore() override;
        bool pre_render() override;
        bool post_render() override;
        void render_present() override;
        void draw_line(const Point<int32_t>& from, const Point<int32_t>& to, const Color& color) override;
        inline StringRepr to_string() const { return "SdlRenderer"; }
    private:
        inline SdlRenderer() { _sdl_renderer = nullptr; }
        inline SdlRenderer(const SdlRenderer&) { _sdl_renderer = nullptr; }

        // Only to be used by SdlPrimitiveRenderer
        SDL_Renderer& get_sdl_renderer() const { return *_sdl_renderer; }
    };

    class SdlPrimitiveRenderer final : public IPrimitiveRenderer {
    private:
        const SdlRenderer* _renderer;
    public:
        SdlPrimitiveRenderer(const SdlRenderer* renderer) : _renderer(renderer) {}
        // Should not delete SdlRenderer
        inline ~SdlPrimitiveRenderer() {}
        void draw_line(const Point<int32_t>& start, const Point<int32_t>& end, const Color& color) override;
        void draw_point(const Point<int32_t>& point, const Color& color) override;
        void draw_triangle(const Point<int32_t>& v1, const Point<int32_t>& v2,
                          const Point<int32_t>& v3, const Color& color) override;
        void draw_circle(const Point<int32_t>& center, const int32_t& radius, const Color& color) override;
        void draw_rect(const Rect& rect, const Color& color) override;
        void draw_text(const std::string& text, const Rect& canvas, const Color& color) override;
    private:
        inline SdlPrimitiveRenderer() { _renderer = nullptr; }
        inline SdlPrimitiveRenderer(const SdlPrimitiveRenderer&) { _renderer = nullptr; }
        void set_color(const Color& color);
    };
}
