#include "Line.h"

namespace ZeroEngine {

    Line::Line(const Point<Float32>& start, const Point<Float32>& end) {
        _start = Vector2(start.get_x(), start.get_y());
        _end = Vector2(end.get_x(), end.get_y());
    }

    Line::Line(const Float32& x1, const Float32& y1, const Float32& x2, const Float32& y2) {
        _start = Vector2(x1, y1);
        _end = Vector2(x2, y2);
    }
}