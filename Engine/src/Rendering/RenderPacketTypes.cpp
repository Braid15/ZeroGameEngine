#include "RenderPacketTypes.h"

namespace ZeroEngine {

    LineRenderPacket::LineRenderPacket(Float32 x1, Float32 y1, Float32 x2, Float32 y2, Color color) 
            : BaseRenderPacket(color) {

        _start = Vector2(x1, y1);
        _end = Vector2(x2, y2);
    }

    LineRenderPacket::LineRenderPacket(const LineRenderPacket& other) 
            : BaseRenderPacket(other.get_color()) {

        _start = other._start;
        _end = other._end;
    }

    LineRenderPacket::LineRenderPacket(Point<Int32> start, Point<Int32> end, Color color)
        : BaseRenderPacket(color) {

        _start = Vector2(static_cast<Float32>(start.get_x()), static_cast<Float32>(start.get_y()));
        _end = Vector2(static_cast<Float32>(end.get_x()), static_cast<Float32>(end.get_y()));
    }

    void LineRenderPacket::on_render(IPrimitiveRenderer& renderer) {
        renderer.draw_line(_start, _end, get_color());
    }


    void RectRenderPacket::on_render(IPrimitiveRenderer& renderer) {
        renderer.draw_rect(_rect, get_color());
    }

    void VertexRenderPacket::on_render(IPrimitiveRenderer& renderer) {
        renderer.draw_vertices(_vertices, _size, get_color());
    }
}