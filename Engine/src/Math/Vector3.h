#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class Vector3 : public IZeroObject {
    private:
        float32 _x;
        float32 _y;
        float32 _z;
    public:
        inline Vector3() : _x(0.0), _y(0.0), _z(0.0) {}
        inline Vector3(float32 x, float32 y, float32 z) : _x(x), _y(y), _z(z) {}

        inline void set_x(const float32 x) { _x = x; }
        inline float32 get_x() const { return _x; }

        inline void set_y(const float32 y) { _y = y; }
        inline float32 get_y() const { return _y; }

        inline void set_z(const float32 z) { _z = z; }
        inline float32 get_z() const { return _z; }

        static const Vector3 zero;

        inline StringRepr to_string() const { return "Vector3"; }
    };

}