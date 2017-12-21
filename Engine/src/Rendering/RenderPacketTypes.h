#pragma once

#include "IRenderPacket.h"
#include "IPrimitiveRenderer.h"
#include "../Graphics/Graphics.h"
#include "../Math/Vector2.h"
#include "../Math/Line.h"

namespace ZeroEngine {

    // As of right now I am hoping that inheriting will be unnecessary
    class LineRenderPacket final : public BaseRenderPacket {
    private:
        Vector2 _start;
        Vector2 _end;
    public:
        LineRenderPacket(Vector2& start, Vector2& end, Color color) 
            : BaseRenderPacket(color), _start(start), _end(end) {}
        LineRenderPacket(float_t x1, float_t y1, float_t x2, float_t y2, Color color);
        LineRenderPacket(Line line, Color color) : BaseRenderPacket(color),
            _start(line.get_start()), _end(line.get_end()) {}
        LineRenderPacket(const LineRenderPacket&);
        LineRenderPacket(Point<int32_t> start, Point<int32_t> end, Color color);


        void on_render(IPrimitiveRenderer&) override;
        inline StringRepr to_string() const override { return "LineRenderPacket"; }
        typedef std::shared_ptr<LineRenderPacket> s_ptr;
    };

}