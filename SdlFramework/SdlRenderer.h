#pragma once

#include "../Engine/src/ZeroEngineStd.h"
#include "../Engine/src/Framework/IRenderer.h"
#include "../Engine/src/Rendering/IPrimitiveRenderer.h"
#include "SdlFramework.h"
#include "../Engine/src/Math/MathTypes.h"

namespace ZeroSdlFramework {

    // -----------
    // SdlRenderer
    // -----------

    class SdlRenderer : public ZeroEngine::BaseRenderer {
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
        void draw_line(const ZeroEngine::Point<ZeroEngine::Int32>& from, const ZeroEngine::Point<ZeroEngine::Int32>& to, const ZeroEngine::Color& color) override;
        const SDL_Window* get_sdl_window() const { return _sdl_window; }
        ZeroEngine::ITexture* create_texture(const char* file_path) override;
        inline ZeroEngine::StringRepr to_string() const { return "SdlRenderer"; }
    private:
        inline SdlRenderer() { _sdl_renderer = nullptr; }
        inline SdlRenderer(const SdlRenderer&) { _sdl_renderer = nullptr; }

        // Only to be used by SdlPrimitiveRenderer
        SDL_Renderer& get_sdl_renderer() const { return *_sdl_renderer; }
    };

    // --------------------
    // SdlPrimitiveRenderer
    // --------------------

    class SdlPrimitiveRenderer final : public ZeroEngine::IPrimitiveRenderer {
    private:
        const SdlRenderer* _renderer;
    public:
        SdlPrimitiveRenderer(const SdlRenderer* renderer) : _renderer(renderer) {}
        // Should not delete SdlRenderer
        inline ~SdlPrimitiveRenderer() {}
        void draw_line(const ZeroEngine::Vector2& start, const ZeroEngine::Vector2& end, const ZeroEngine::Color& color) override;
        void draw_point(const ZeroEngine::Point<ZeroEngine::Int32>& point, const ZeroEngine::Color& color) override;
        void draw_triangle(const ZeroEngine::Point<ZeroEngine::Int32>& v1, const ZeroEngine::Point<ZeroEngine::Int32>& v2,
                          const ZeroEngine::Point<ZeroEngine::Int32>& v3, const ZeroEngine::Color& color) override;
        void draw_circle(const ZeroEngine::Point<ZeroEngine::Int32>& center, const ZeroEngine::Float32& radius, const ZeroEngine::Color& color) override;
        void draw_rect(const ZeroEngine::Rect& rect, const ZeroEngine::Color& color) override;
        void draw_text(const std::string& text, const ZeroEngine::Rect& canvas, const ZeroEngine::Color& color) override;
        void draw_vertices(ZeroEngine::Vector2 vertices[], ZeroEngine::Int32 count, const ZeroEngine::Color& color) override;
    private:
        inline SdlPrimitiveRenderer() { _renderer = nullptr; }
        inline SdlPrimitiveRenderer(const SdlPrimitiveRenderer&) { _renderer = nullptr; }
        void set_color(const ZeroEngine::Color& color);
    };
}
