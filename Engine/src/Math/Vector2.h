#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // @TODO: dot product, scalar multiplication, etc..

    class Vector2 : public IZeroObject {
    private:
        float_t _x;
        float_t _y;
    public:
        inline Vector2() : _x(0.0), _y(0.0) {}
        inline Vector2(float_t x, float_t y) : _x(x), _y(y) {}
        inline Vector2(const Vector2& other) : _x(other.get_x()), _y(other.get_y()) {}
        inline ~Vector2() {}

        static const Vector2 zero;

        static Vector2 add(const Vector2& v1, const Vector2& v2);
        static Vector2 add(const Vector2* v1, const Vector2* v2);
        static Vector2 add(const Vector2& v1, const Vector2* v2);
        static Vector2 add(const Vector2* v1, const Vector2& v2);

        static Vector2 subtract(const Vector2& v1, const Vector2& v2);
        static Vector2 subtract(const Vector2* v1, const Vector2* v2);
        static Vector2 subtract(const Vector2& v1, const Vector2* v2);
        static Vector2 subtract(const Vector2* v1, const Vector2& v2);

        inline float_t get_x() const { return _x; }
        inline void set_x(float_t x) { _x = x; }

        inline float_t get_y() const { return _y; }
        inline void set_y(float_t y) { _y = y; }

        inline bool is_zero() const { return _x == 0.0 && _y == 0.0; }

        inline Vector2 operator+(const Vector2&);
        inline Vector2 operator-(const Vector2&);

        inline Vector2& operator+=(const Vector2&);
        inline Vector2& operator+=(const Vector2*);

        inline Vector2& operator-=(const Vector2&);
        inline Vector2& operator-=(const Vector2*);

        inline Vector2& operator=(const Vector2&);
        inline Vector2& operator=(const Vector2*);

        inline bool operator==(const Vector2&);
        inline bool operator!=(const Vector2&);

        inline StringRepr to_string() const { return "Vector2"; }
    };

    // @TODO: All ostreams will need to be fixed for serialization or a serialize method will be needed.
    std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
        os << "Vector2: (" << vector.get_x() << ", " << vector.get_y() << ")";
        return os;
    }
}