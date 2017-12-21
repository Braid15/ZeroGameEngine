#include "Line.h"

namespace ZeroEngine {

    Line::Line(const Point<float_t>& start, const Point<float_t>& end) {
        _start = Vector2(start.get_x(), start.get_y());
        _end = Vector2(end.get_x(), end.get_y());
    }

    Line::Line(const float_t& x1, const float_t& y1, const float_t& x2, const float_t& y2) {
        _start = Vector2(x1, y1);
        _end = Vector2(x2, y2);
    }
}