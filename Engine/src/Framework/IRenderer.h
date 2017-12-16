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
        virtual void draw_line(const Point<int32_t>& from, const Point<int32_t>& to, const Color& color) = 0;
        inline virtual ~IRenderer() {}
        typedef std::shared_ptr<IRenderer> ptr;
    };

    // IRenderer implementations need to subclass this class because it exposes
    // a different interface which is necessary for AFramework to access
    class BaseRenderer : public IRenderer, public IZeroObject {
    private:
        Color _background_color;
    public:
        virtual ~BaseRenderer() {}
        virtual void set_background_color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) override;
        virtual void set_background_color(const Color& color) override;
        virtual bool pre_render() = 0;
        virtual bool post_render() = 0;
        virtual void shutdown() = 0;
        virtual bool on_restore() = 0;
        virtual void draw_line(const Point<int32_t>& from, const Point<int32_t>& to, const Color& color) = 0;
        virtual void render_present() = 0;
        virtual StringRepr to_string() const = 0;
        typedef std::shared_ptr<BaseRenderer> ptr;
    protected:
        const Color& get_background_color() const { return _background_color; }
    };

    class NullRenderer : public BaseRenderer {
    public:
        inline virtual void shutdown() override {}
        inline virtual bool on_restore() override { return true; }
        inline virtual bool pre_render() override { return true; }
        inline virtual bool post_render() override { return true; }
        inline virtual void draw_line(const Point<int32_t>& from, const Point<int32_t>& to, const Color& color) override {}
        inline virtual void render_present() override {}
        inline StringRepr to_string() const override { return "NullRenderer"; }
    };
}