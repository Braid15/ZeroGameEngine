#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Color.h"

namespace ZeroEngine {

    class IRenderer;

    class IRenderPacket : public IZeroObject {
    public:
        virtual void on_render(IRenderer&) = 0;
        virtual StringRepr to_string() const = 0;
        inline virtual ~IRenderPacket() {}
        typedef std::tr1::shared_ptr<IRenderPacket> s_ptr;
    };

    class Color;

    class BaseRenderPacket : public IRenderPacket {
    private:
        Color _color;
    public:
        BaseRenderPacket(Color color) : _color(color) {}
        inline virtual ~BaseRenderPacket() {}
        virtual void on_render(IRenderer&) = 0;
        virtual StringRepr to_string() const = 0;
        typedef std::tr1::shared_ptr<BaseRenderPacket> s_ptr;
    protected:
        const Color& get_color() const { return _color; }
    };
}