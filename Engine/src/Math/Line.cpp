#include "Line.h"

namespace ZeroEngine {

    Line::Line(const Point<float32>& start, const Point<float32>& end) {
        _start = Vector2(start.get_x(), start.get_y());
        _end = Vector2(end.get_x(), end.get_y());
    }

    Line::Line(const float32& x1, const float32& y1, const float32& x2, const float32& y2) {
        _start = Vector2(x1, y1);
        _end = Vector2(x2, y2);
    }
}