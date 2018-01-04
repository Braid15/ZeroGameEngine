#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class Vector3 : public IZeroObject {
    private:
        Float32 _x;
        Float32 _y;
        Float32 _z;
    public:
        inline Vector3() : _x(0.0), _y(0.0), _z(0.0) {}
        inline Vector3(Float32 x, Float32 y, Float32 z) : _x(x), _y(y), _z(z) {}

        inline void set_x(const Float32 x) { _x = x; }
        inline Float32 get_x() const { return _x; }

        inline void set_y(const Float32 y) { _y = y; }
        inline Float32 get_y() const { return _y; }

        inline void set_z(const Float32 z) { _z = z; }
        inline Float32 get_z() const { return _z; }

        static const Vector3 zero;

        inline StringRepr to_string() const { return "Vector3"; }
    };

}