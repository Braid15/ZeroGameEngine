#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Graphics.h"

namespace ZeroEngine {

    class IRenderer {
    public:
        virtual void set_background_color(uint32_t red,
                                          uint32_t green, 
                                          uint32_t blue, 
                                          uint32_t alpha
        ) = 0;
        virtual void set_background_color(const Color& color) = 0;
        virtual bool pre_render() = 0;
        virtual bool post_render() = 0;
        virtual void shutdown() = 0;
        virtual bool on_restore() = 0;
        virtual void draw_line(const Point<float_t>& from, const Point<float_t>& to, const Color& color) = 0;
        typedef std::shared_ptr<IRenderer> ptr;
    };

    class NullRenderer : public IRenderer, public IZeroObject {
    public:
        inline virtual void set_background_color(uint32_t red,
                                                 uint32_t green,
                                                 uint32_t blue,
                                                 uint32_t alpha
        ) override {}
        inline virtual void set_background_color(const Color& color) override {}
        inline virtual void shutdown() override {}
        inline virtual bool on_restore() override { return true; }
        inline virtual bool pre_render() override { return true; }
        inline virtual bool post_render() override { return true; }
        inline virtual void draw_line(const Point<float_t>& from, const Point<float_t>& to, const Color& color) override {}
        inline StringRepr to_string() const { return "NullRenderer"; }
    };
}