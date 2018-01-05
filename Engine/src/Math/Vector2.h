#pragma once 

#include "../ZeroEngineStd.h"
#include "Math.h"

namespace ZeroEngine {

    // @TODO: Implement squared magnitude becuase sqrt is expensive
    // Will need to know when it is appropritate to use this instead of sqrt.
    // |a|^2 = (ax^2 + ay^2)
    // See Game Engine Architecture p.172

    class Vector2 : public IZeroObject {
    private:
        Float32 _x;
        Float32 _y;
        Float32 _vec[2];
    public:
        Vector2();
        Vector2(const Float32 x, const Float32 y);
        Vector2(const Vector2& other);

        typedef std::shared_ptr<Vector2> s_ptr;
        typedef std::weak_ptr<Vector2> w_ptr;

        static const Vector2 zero;

        // x-axis 
        static const Vector2 unit_i;

        // y-axis
        static const Vector2 unit_j;

        static Vector2 add(const Vector2& v1, const Vector2& v2);
        static Vector2 add(const Vector2* v1, const Vector2* v2);
        static Vector2 add(const Vector2& v1, const Vector2* v2);
        static Vector2 add(const Vector2* v1, const Vector2& v2);

        static Vector2 subtract(const Vector2& v1, const Vector2& v2);
        static Vector2 subtract(const Vector2* v1, const Vector2* v2);
        static Vector2 subtract(const Vector2& v1, const Vector2* v2);
        static Vector2 subtract(const Vector2* v1, const Vector2& v2);

        static Vector2 scalar_multiply(const Vector2& v, const Float32& scalar);
        static Vector2 scalar_multiply(const Vector2* v, const Float32& scalar);

        static Vector2 normalize(const Vector2& v);
        static Vector2 normalize(const Vector2* v);


        static Vector2 euler_integrate(const Vector2& cur_pos,
                                       const Vector2& cur_vel, 
                                       const Float32& delta);

        static Vector2 euler_integrate(const Vector2* cur_pos,
                                       const Vector2* cur_vel,
                                       const Float32& delta);

        static Vector2 euler_integrate(const Vector2* cur_pos,
                                       const Vector2& cur_vel,
                                       const Float32& delta);

        static Vector2 euler_integrate(const Vector2& cur_pos,
                                       const Vector2* cur_vel,
                                       const Float32& delta);

        static Float32 dot_product(const Vector2& v1, const Vector2& v2);
        static Float32 dot_product(const Vector2* v1, const Vector2* v2);
        static Float32 dot_product(const Vector2& v1, const Vector2* v2);
        static Float32 dot_product(const Vector2* v1, const Vector2& v2);

        static bool opposite_directions(const Vector2& v1, const Vector2& v2);
        static bool opposite_directions(const Vector2* v1, const Vector2* v2);
        static bool opposite_directions(const Vector2& v1, const Vector2* v2);
        static bool opposite_directions(const Vector2* v1, const Vector2& v2);

        static bool are_collinear(const Vector2& v1, const Vector2& v2);
        static bool are_collinear(const Vector2* v1, const Vector2* v2);
        static bool are_collinear(const Vector2& v1, const Vector2* v2);
        static bool are_collinear(const Vector2* v1, const Vector2& v2);

        static bool are_collinear_opposites(const Vector2& v1, const Vector2& v2);
        static bool are_collinear_opposites(const Vector2* v1, const Vector2* v2);
        static bool are_collinear_opposites(const Vector2& v1, const Vector2* v2);
        static bool are_collinear_opposites(const Vector2* v1, const Vector2& v2);

        static bool are_perpendicular(const Vector2& v1, const Vector2& v2);
        static bool are_perpendicular(const Vector2* v1, const Vector2* v2);
        static bool are_perpendicular(const Vector2& v1, const Vector2* v2);
        static bool are_perpendicular(const Vector2* v1, const Vector2& v2);

        static bool same_directions(const Vector2& v1, const Vector2& v2);
        static bool same_directions(const Vector2* v1, const Vector2* v2);
        static bool same_directions(const Vector2& v1, const Vector2* v2);
        static bool same_directions(const Vector2* v1, const Vector2& v2);

        bool has_opposite_direction_as(const Vector2& other);
        bool has_opposite_direction_as(const Vector2* other);

        bool is_collinear_to(const Vector2& other);
        bool is_collinear_to(const Vector2* other);

        bool is_collinear_opposite_to(const Vector2& other);
        bool is_collinear_opposite_to(const Vector2* other);

        bool is_perpendicular_to(const Vector2& other);
        bool is_perpendicular_to(const Vector2* other);

        bool has_same_direction_as(const Vector2& other);
        bool has_same_direction_as(const Vector2* other);


        Float32 get_dot_product(const Vector2& other);
        Float32 get_dot_product(const Vector2* other);

        Float32 get_magnitude() const;
        void normalize();
        inline bool is_unit_vector() const { return get_magnitude() == 1.0; }

        Float32 get_projection(const Vector2& other);
        Float32 get_projection(const Vector2* other);

        void project_onto(const Vector2& other);
        void project_onto(const Vector2* other);

        inline Float32 get_x() const { return _x; }
        inline void set_x(Float32 x) { _x = x; }

        inline Float32 get_y() const { return _y; }
        inline void set_y(Float32 y) { _y = y; }

        inline void set(const Vector2& other) { _x = other.get_x(); _y = other.get_y(); }
        inline void set(const Vector2* other) { _x = other->get_x(); _y = other->get_y(); }
        inline void set(const Float32 x, const Float32 y) { _x = x; _y = y; }

        inline bool is_zero() const { return _x == 0.0 && _y == 0.0; }

        inline void flip() { _x *= -1; _y *= -1; }

        inline Vector2 operator+(const Vector2&) const;
        inline Vector2 operator-(const Vector2&) const;

        inline Vector2 operator*(const Float32& scalar) const;

        inline Vector2& operator*=(const Float32& scalar);

        inline Vector2& operator+=(const Vector2&);
        inline Vector2& operator+=(const Vector2*);

        inline Vector2& operator-=(const Vector2&);
        inline Vector2& operator-=(const Vector2*);

        inline Vector2& operator=(const Vector2&);
        inline Vector2& operator=(const Vector2*);

        inline bool operator==(const Vector2&) const;
        inline bool operator!=(const Vector2&) const;

        inline StringRepr to_string() const { return "Vector2"; }
    };

    inline Vector2 Vector2::operator*(const Float32& scalar) const {
        return Vector2(_x * scalar, _y * scalar);
    }

    inline Vector2& Vector2::operator*=(const Float32& scalar) {
        _x *= scalar;
        _y *= scalar;
        return *this;
    }

    inline Vector2 Vector2::operator+(const Vector2& other) const {
        return Vector2(_x + other.get_x(), _y + other.get_y());
    }

    inline Vector2 Vector2::operator-(const Vector2& other) const {
        return Vector2(_x - other.get_x(), _y - other.get_y());
    }

    inline Vector2& Vector2::operator+=(const Vector2& rhs) {
        _x += rhs.get_x();
        _y += rhs.get_y();
        return *this;
    }

    inline Vector2& Vector2::operator+=(const Vector2* rhs) {
        _x += rhs->get_x();
        _y += rhs->get_y();
        return *this;
    }

    inline Vector2& Vector2::operator-=(const Vector2& rhs) {
        _x -= rhs.get_x();
        _y -= rhs.get_y();
        return *this;
    }

    inline Vector2& Vector2::operator-=(const Vector2* rhs) {
        _x -= rhs->get_x();
        _y -= rhs->get_y();
        return *this;
    }

    inline Vector2& Vector2::operator=(const Vector2& rhs) {
        _x = rhs.get_x();
        _y = rhs.get_y();
        return *this;
    }

    inline Vector2& Vector2::operator=(const Vector2* rhs) {
        _x = rhs->get_x();
        _y = rhs->get_y();
        return *this;
    }

    inline bool Vector2::operator==(const Vector2& rhs) const {
        return _x == rhs.get_x() && _y == rhs.get_y(); 
    }

    inline bool Vector2::operator!=(const Vector2& rhs) const {
        return _x != rhs.get_x() || _y != rhs.get_y();
    }

    // @TODO: All ostreams will need to be fixed for serialization or a serialize method will be needed.
    std::ostream& operator<<(std::ostream& os, const Vector2& vector);
}