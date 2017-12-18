#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Color.h"

namespace ZeroEngine {

    // --------------------------------------------------------
    // Packets with data to be rendererd by IPrimitiveRenderer.
    // Provides abstraction between higher lever layers of the
    // system and the rendering layer.
    // --------------------------------------------------------

    class IPrimitiveRenderer;

    class IRenderPacket : public IZeroObject {
    public:
        virtual void on_render(IPrimitiveRenderer&) = 0;
        virtual StringRepr to_string() const = 0;
        inline virtual ~IRenderPacket() {}
        typedef std::tr1::shared_ptr<IRenderPacket> s_ptr;
    };

    class BaseRenderPacket : public IRenderPacket {
    private:
        Color _color;
    public:
        BaseRenderPacket(Color color) : _color(color) {}
        inline virtual ~BaseRenderPacket() {}
        virtual void on_render(IPrimitiveRenderer&) = 0;
        inline const Color& get_color() const { return _color; }
        inline void set_color(const Color& color) { _color = color; }
        virtual StringRepr to_string() const = 0;
        typedef std::tr1::shared_ptr<BaseRenderPacket> s_ptr;
    };
}