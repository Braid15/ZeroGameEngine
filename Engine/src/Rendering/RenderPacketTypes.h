#pragma once

#include "IRenderPacket.h"
#include "../Framework/IRenderer.h"
#include "../Graphics/Graphics.h"

namespace ZeroEngine {

    // As of right now I am hoping that inheriting will be unnecessary
    class LineRenderPacket final : public BaseRenderPacket {
    private:
        Point<int32_t> _start;
        Point<int32_t> _end;
    public:
        inline LineRenderPacket(Point<int32_t> start, Point<int32_t> end, Color color)
            : BaseRenderPacket(color), _start(start), _end(end) {}
        LineRenderPacket(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color);
        LineRenderPacket(const LineRenderPacket&);
        void on_render(IRenderer&) override;
        inline StringRepr to_string() const override { return "LineRenderPacket"; }
        typedef std::tr1::shared_ptr<LineRenderPacket> s_ptr;
    };

}