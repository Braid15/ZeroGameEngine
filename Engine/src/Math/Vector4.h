#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class Vector4 : public IZeroObject {
    private:
        float32 _x;
        float32 _y;
        float32 _z;
        float32 _w;
    public:
        inline Vector4() : _x(0.0), _y(0.0), _z(0.0), _w(0.0) {}
        inline Vector4(float32 x, float32 y, float32 z, float32 w) 
            : _x(x), _y(y), _z(z), _w(w) {}

        inline void set_x(const float32 x) { _x = x; }
        inline float32 get_x() const { return _x; }

        inline void set_y(const float32 y) { _y = y; }
        inline float32 get_y() const { return _y; }

        inline void set_z(const float32 z) { _z = z; }
        inline float32 get_z() const { return _z; }

        inline void set_w(const float32 w) { _w = w; }
        inline float32 get_w() const { return _w; }

        static const Vector4 zero;

        inline StringRepr to_string() const { return "Vector4"; }
    };
}