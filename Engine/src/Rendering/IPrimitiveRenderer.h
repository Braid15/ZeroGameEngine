#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // ----------------------------------------------------------------------
    // Provides an interface for rendering primitives like lines, text, etc..
    // ----------------------------------------------------------------------

    template <class T = int32_t>
    class Point;

    class Color;
    class Rect;

    class IPrimitiveRenderer {
    public:
        virtual void draw_line(const Point<int32_t>& start, const Point<int32_t>& end, const Color& color) = 0;
        virtual void draw_point(const Point<int32_t>& point, const Color& color) = 0;
        virtual void draw_triangle(const Point<int32_t>& p1, const Point<int32_t>& p2, 
                                   const Point<int32_t>& p3, const Color& color) = 0;
        virtual void draw_circle(const Point<int32_t>& center, const int32_t& radius, const Color& color) = 0;
        virtual void draw_rect(const Rect& rect, const Color& color) = 0;
        virtual void draw_text(const std::string& text, const Rect& canvas, const Color& color) = 0;
    };
}