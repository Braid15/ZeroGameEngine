#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class Vector4 : public IZeroObject {
    private:
        float_t _x;
        float_t _y;
        float_t _z;
        float_t _w;
    public:
        inline Vector4() : _x(0.0), _y(0.0), _z(0.0), _w(0.0) {}
        inline Vector4(float_t x, float_t y, float_t z, float_t w) 
            : _x(x), _y(y), _z(z), _w(w) {}

        inline void set_x(const float_t x) { _x = x; }
        inline float_t get_x() const { return _x; }

        inline void set_y(const float_t y) { _y = y; }
        inline float_t get_y() const { return _y; }

        inline void set_z(const float_t z) { _z = z; }
        inline float_t get_z() const { return _z; }

        inline void set_w(const float_t w) { _w = w; }
        inline float_t get_w() const { return _w; }

        static const Vector4 zero;

        inline StringRepr to_string() const { return "Vector4"; }
    };
}