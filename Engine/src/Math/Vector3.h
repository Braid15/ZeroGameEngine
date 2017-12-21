#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class Vector3 : public IZeroObject {
    private:
        float_t _x;
        float_t _y;
        float_t _z;
    public:
        inline Vector3() : _x(0.0), _y(0.0), _z(0.0) {}
        inline Vector3(float_t x, float_t y, float_t z) : _x(x), _y(y), _z(z) {}

        inline void set_x(const float_t x) { _x = x; }
        inline float_t get_x() const { return _x; }

        inline void set_y(const float_t y) { _y = y; }
        inline float_t get_y() const { return _y; }

        inline void set_z(const float_t z) { _z = z; }
        inline float_t get_z() const { return _z; }

        static const Vector3 zero;

        inline StringRepr to_string() const { return "Vector3"; }
    };

}