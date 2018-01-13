#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // ----------------------------------------------------------------------
    // Provides an interface for rendering primitives like lines, text, etc..
    // ----------------------------------------------------------------------

    template <class T = Int32>
    class Point;

    class Color;
    class Rect;

    class Vector2;

    // @TODO: Change Point to use Vector2

    class IPrimitiveRenderer {
    public:
        virtual void draw_line(const Vector2& start, const Vector2& end, const Color& color) = 0;


        virtual void draw_point(const Point<Int32>& point, const Color& color) = 0;
        virtual void draw_triangle(const Point<Int32>& p1, const Point<Int32>& p2, 
                                   const Point<Int32>& p3, const Color& color) = 0;
        virtual void draw_circle(const Point<Int32>& center, const Float32& radius, const Color& color) = 0;
        virtual void draw_rect(const Rect& rect, const Color& color) = 0;
        virtual void draw_text(const std::string& text, const Rect& canvas, const Color& color) = 0;
        virtual void draw_vertices(Vector2 vertices[], Int32 count, const Color& color) = 0;
    };
}