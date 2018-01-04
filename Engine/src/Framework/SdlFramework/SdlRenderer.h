#pragma once

#include "../../ZeroEngineStd.h"
#include "../IRenderer.h"
#include "../../Rendering/IPrimitiveRenderer.h"
#include "SdlFramework.h"
#include "../../Math/Vector2.h"

namespace ZeroEngine {

    // -----------
    // SdlRenderer
    // -----------

    class SdlRenderer : public BaseRenderer {
    private:
        friend class SdlPrimitiveRenderer;
        friend class SdlTextureImpl;
        SDL_Renderer* _sdl_renderer;
        SDL_Window* _sdl_window;
    public:
        // @TEMP: SHould be created with SdlWindow
        SdlRenderer(SDL_Window* window);
        ~SdlRenderer();
        void shutdown() override;
        bool on_restore() override;
        bool pre_render() override;
        bool post_render() override;
        void render_present() override;
        void draw_line(const Point<Int32>& from, const Point<Int32>& to, const Color& color) override;
        const SDL_Window* get_sdl_window() const { return _sdl_window; }
        ITexture* create_texture(const char* file_path) override;
        inline StringRepr to_string() const { return "SdlRenderer"; }
    private:
        inline SdlRenderer() { _sdl_renderer = nullptr; }
        inline SdlRenderer(const SdlRenderer&) { _sdl_renderer = nullptr; }

        // Only to be used by SdlPrimitiveRenderer
        SDL_Renderer& get_sdl_renderer() const { return *_sdl_renderer; }
    };

    // --------------------
    // SdlPrimitiveRenderer
    // --------------------

    class SdlPrimitiveRenderer final : public IPrimitiveRenderer {
    private:
        const SdlRenderer* _renderer;
    public:
        SdlPrimitiveRenderer(const SdlRenderer* renderer) : _renderer(renderer) {}
        // Should not delete SdlRenderer
        inline ~SdlPrimitiveRenderer() {}
        void draw_line(const Vector2& start, const Vector2& end, const Color& color) override;
        void draw_point(const Point<Int32>& point, const Color& color) override;
        void draw_triangle(const Point<Int32>& v1, const Point<Int32>& v2,
                          const Point<Int32>& v3, const Color& color) override;
        void draw_circle(const Point<Int32>& center, const Float32& radius, const Color& color) override;
        void draw_rect(const Rect& rect, const Color& color) override;
        void draw_text(const std::string& text, const Rect& canvas, const Color& color) override;
    private:
        inline SdlPrimitiveRenderer() { _renderer = nullptr; }
        inline SdlPrimitiveRenderer(const SdlPrimitiveRenderer&) { _renderer = nullptr; }
        void set_color(const Color& color);
    };
}
