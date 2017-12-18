#include "RenderPacketTypes.h"

namespace ZeroEngine {

    LineRenderPacket::LineRenderPacket(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color color) 
            : BaseRenderPacket(color) {

        _start = Point<int32_t>(x1, y1);
        _end = Point<int32_t>(x2, y2);
    }

    LineRenderPacket::LineRenderPacket(const LineRenderPacket& other) 
            : BaseRenderPacket(other.get_color()) {

        _start = other._start;
        _end = other._end;
    }

    void LineRenderPacket::on_render(IPrimitiveRenderer& renderer) {
        renderer.draw_line(_start, _end, get_color());
    }
}