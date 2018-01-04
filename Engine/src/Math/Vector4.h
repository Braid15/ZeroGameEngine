#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class Vector4 : public IZeroObject {
    private:
        Float32 _x;
        Float32 _y;
        Float32 _z;
        Float32 _w;
    public:
        inline Vector4() : _x(0.0), _y(0.0), _z(0.0), _w(0.0) {}
        inline Vector4(Float32 x, Float32 y, Float32 z, Float32 w) 
            : _x(x), _y(y), _z(z), _w(w) {}

        inline void set_x(const Float32 x) { _x = x; }
        inline Float32 get_x() const { return _x; }

        inline void set_y(const Float32 y) { _y = y; }
        inline Float32 get_y() const { return _y; }

        inline void set_z(const Float32 z) { _z = z; }
        inline Float32 get_z() const { return _z; }

        inline void set_w(const Float32 w) { _w = w; }
        inline Float32 get_w() const { return _w; }

        static const Vector4 zero;

        inline StringRepr to_string() const { return "Vector4"; }
    };
}