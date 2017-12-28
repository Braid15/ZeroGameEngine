#include "RenderPacketTypes.h"

namespace ZeroEngine {

    LineRenderPacket::LineRenderPacket(float32 x1, float32 y1, float32 x2, float32 y2, Color color) 
            : BaseRenderPacket(color) {

        _start = Vector2(x1, y1);
        _end = Vector2(x2, y2);
    }

    LineRenderPacket::LineRenderPacket(const LineRenderPacket& other) 
            : BaseRenderPacket(other.get_color()) {

        _start = other._start;
        _end = other._end;
    }

    LineRenderPacket::LineRenderPacket(Point<int32> start, Point<int32> end, Color color)
        : BaseRenderPacket(color) {

        _start = Vector2(start.get_x(), start.get_y());
        _end = Vector2(end.get_x(), end.get_y());
    }

    void LineRenderPacket::on_render(IPrimitiveRenderer& renderer) {
        renderer.draw_line(_start, _end, get_color());
    }
}