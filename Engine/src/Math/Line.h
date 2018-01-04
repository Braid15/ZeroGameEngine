#pragma once 

#include "../ZeroEngineStd.h"
#include "Vector2.h"
#include "../Graphics/Point.h"

namespace ZeroEngine {

    class Line : public IZeroObject {
    private:
        Vector2 _start;
        Vector2 _end;
    public:
        Line(const Vector2& start, const Vector2& end) : _start(start), _end(end) {}
        Line(const Point<Float32>& start, const Point<Float32>& end);
        Line(const Line& other) : _start(other.get_start()), _end(other.get_end()) {}
        Line(const Float32& x1, const Float32& y1, const Float32& x2, const Float32& y2);
        ~Line() {}

        inline const Vector2& get_start() const { return _start; }
        inline const Vector2& get_end() const { return _end; }
        inline void set_start(const Vector2 start) { _start = start; }
        inline void set_end(const Vector2 end) { _end = end; }

        inline StringRepr to_string() const { return "Line"; }
    };
}