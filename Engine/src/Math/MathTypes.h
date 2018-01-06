#pragma once

#include "../ZeroEngineStd.h"
#include "Math.h"

//
// These classes are based off of Graphics Gems IV. p.534
//

// @TODO: Get rid of some of the more complicated operator overloads and put
// that functionality into functions.

namespace ZeroEngine {

    // ----
    // Axis
    // ----

    typedef Uint8 AxisIndex;

    namespace Axis {

        constexpr AxisIndex x = 0;
        constexpr AxisIndex y = 1;
        constexpr AxisIndex z = 2;
        constexpr AxisIndex w = 3;

        extern std::string to_string(AxisIndex);
    }

    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix3x3;
    class Matrix4x4;

    // -------
    // Vector2
    // -------

    class Vector2 : public virtual IZeroObject {
    private:
        Float32 _vec[2];
    public:
        static const Vector2& zero();
        static const Vector2& unit_i(); // x-axis unit vector
        static const Vector2& unit_j(); // y-axis unit vector

        Vector2();
        explicit Vector2(const Float32);
        Vector2(const Float32 x, const Float32 y);
        Vector2(const Vector2&);
        Vector2(const Vector3&);
        Vector2(const Vector4&);

        Vector2& operator=(const Vector2&);
        Vector2& operator+=(const Vector2&);
        Vector2& operator-=(const Vector2&);
        Vector2& operator*=(const Float32);
        Vector2& operator/=(const Float32);
        Float32& operator[](Int32);
        Float32 operator[](Int32) const;

        operator Vector3();
        operator Vector4();

        friend Vector2 operator-(const Vector2&); // for negation
        friend Vector2 operator+(const Vector2&, const Vector2&);
        friend Vector2 operator-(const Vector2&, const Vector2&);
        friend Vector2 operator*(const Vector2&, const Float32);
        friend Vector2 operator*(const Float32, const Vector2&);
        friend Vector2 operator*(const Vector2&, const Matrix3x3&);
        friend Vector2 operator*(const Matrix3x3&, const Vector2&);
        friend Vector2 operator/(const Vector2&, const Float32);
        friend Float32 operator*(const Vector2&, const Vector2&); // dot product
        friend Vector3 operator^(const Vector2&, const Vector2&); // cross product
        friend bool operator==(const Vector2&, const Vector2&);
        friend bool operator!=(const Vector2&, const Vector2&);

        void normalize();
        Vector2 get_normalized() const;
        bool is_normalized() const;

        bool has_opposite_direction_to(const Vector2&) const;

        bool has_same_direction_as(const Vector2&) const;

        bool is_collinear_to(const Vector2&) const;

        bool is_collinear_opposite_to(const Vector2&) const;

        bool is_perpendicular_to(const Vector2&) const;

        // @TODO: set with vector3 and vector4

        Float32 get_magnitude() const;
        Float32 get_magnitude_squared() const;

        Float32 get_projection(const Vector2&) const;

        Float32 get_dot_product(const Vector2&) const;
        Vector3 get_cross_product(const Vector2&) const;

        void scalar_multiply(const Float32);
        Vector2 get_scalar_product(const Float32);

        // @TODO: project_onto(const Vector2&)

        inline void set(const Float32 val) { _vec[Axis::x] = val; _vec[Axis::y] = val; }
        inline void set(const Float32 x, const Float32 y) { _vec[Axis::x] = x; _vec[Axis::y] = y; }
        inline void set(const Vector2& other) { _vec[Axis::x] = other[Axis::x]; _vec[Axis::y] = other[Axis::y]; }

        inline Float32 get_x() const { return _vec[Axis::x]; }
        inline void set_x(const Float32 x) { _vec[Axis::x] = x; }

        inline Float32 get_y() const { return _vec[Axis::y]; }
        inline void set_y(const Float32 y) { _vec[Axis::y] = y; }

        inline void negate() { _vec[Axis::x] *= -1; _vec[Axis::y] *= -1; }

        inline bool is_zero() const { return (_vec[Axis::x] == 0.0f && _vec[Axis::y] == 0.0f); }

        inline StringRepr to_string() const override { return "Vector2"; }
    };

    // -------
    // Vector3
    // -------

    class Vector3 : public virtual IZeroObject {
    private:
        Float32 _vec[3];
    public:
        static const Vector3& zero();
        static const Vector3& unit_i(); // x-axis unit vector
        static const Vector3& unit_j(); // y-axis unit vector
        static const Vector3& unit_k(); // z-axis unit vector

        Vector3();
        explicit Vector3(const Float32);
        Vector3(const Float32 x, const Float32 y, const Float32 z);
        Vector3(const Vector3&);
        Vector3(const Vector2&);
        Vector3(const Vector2&, const Float32 z);
        Vector3(const Vector4&);

        Vector3& operator=(const Vector3&);
        Vector3& operator+=(const Vector3&);
        Vector3& operator-=(const Vector3&);
        Vector3& operator*=(const Float32);
        Vector3& operator/=(const Float32);
        Float32& operator[](Int32);
        Float32 operator[](Int32) const;

        operator Vector2();
        operator Vector4();

        friend Vector3 operator-(const Vector3&); // for negation
        friend Vector3 operator+(const Vector3&, const Vector3&);
        friend Vector3 operator-(const Vector3&, const Vector3&);

        friend Vector3 operator*(const Vector3&, const Float32);
        friend Vector3 operator*(const Float32, const Vector3&);

        friend Vector3 operator*(const Vector3&, const Matrix4x4&);
        friend Vector3 operator*(const Matrix4x4&, const Vector3&);

        friend Vector3 operator/(const Vector3&, const Float32);

        friend Float32 operator*(const Vector3&, const Vector3&); // dot product

        friend Vector3 operator^(const Vector3&, const Vector3&); // cross product

        friend bool operator==(const Vector3&, const Vector3&);
        friend bool operator!=(const Vector3&, const Vector3&);

        void normalize();
        Vector3 get_normalized() const;
        bool is_normalized() const;

        bool has_opposite_direction_to(const Vector3&) const;

        bool has_same_direction_as(const Vector3&) const;

        bool is_collinear_to(const Vector3&) const;

        bool is_collinear_opposite_to(const Vector3&) const;

        bool is_perpendicular_to(const Vector3&) const;

        // @TODO: set with vector3 and vector4

        Float32 get_magnitude() const;
        Float32 get_magnitude_squared() const;

        Float32 get_projection(const Vector3&) const;

        Float32 get_dot_product(const Vector3&) const;
        Vector3 get_cross_product(const Vector3&) const;

        void scalar_multiply(const Float32);
        Vector3 get_scalar_product(const Float32) const;

        // @TODO: project_onto(const Vector2&)

        inline void set(const Float32 scalar) {
            _vec[Axis::x] = scalar;
            _vec[Axis::y] = scalar;
            _vec[Axis::z] = scalar;
        }

        inline void set(const Float32 x, const Float32 y, const Float32 z) {
            _vec[Axis::x] = x;
            _vec[Axis::y] = y;
            _vec[Axis::z] = z;
        }

        inline void set(const Vector3& other) {
            _vec[Axis::x] = other[Axis::x];
            _vec[Axis::y] = other[Axis::y];
            _vec[Axis::z] = other[Axis::z];
        }

        inline Float32 get_x() const { return _vec[Axis::x]; }
        inline void set_x(const Float32 x) { _vec[Axis::x] = x; }

        inline Float32 get_y() const { return _vec[Axis::y]; }
        inline void set_y(const Float32 y) { _vec[Axis::y] = y; }

        inline Float32 get_z() const { return _vec[Axis::z]; }
        inline void set_z(const Float32 z) { _vec[Axis::z] = z; }

        inline void negate() { _vec[Axis::x] *= -1; _vec[Axis::y] *= -1; _vec[Axis::z] *= -1; }

        inline bool is_zero() const { return (_vec[Axis::x] == 0.0f && _vec[Axis::y] == 0.0f && _vec[Axis::z] == 0.0f); }

        inline StringRepr to_string() const override { return "Vector3"; }
    };

    // -------
    // Vector4
    // -------

    class Vector4 : public virtual IZeroObject {
    private:
        Float32 _vec[4];
    public:
        static const Vector4& zero();
        static const Vector4& unit_i(); // x-axis unit vector
        static const Vector4& unit_j(); // y-axis unit vector
        static const Vector4& unit_k(); // z-axis unit vector

        Vector4();
        explicit Vector4(const Float32);
        Vector4(const Float32 x, const Float32 y, const Float32 z, const Float32 w);
        Vector4(const Vector4&);
        Vector4(const Vector3&);
        Vector4(const Vector3&, const Float32 w);
        Vector4(const Vector2&);

        Vector4& operator=(const Vector4&);
        Vector4& operator+=(const Vector4&);
        Vector4& operator-=(const Vector4&);
        Vector4& operator*=(const Float32);
        Vector4& operator/=(const Float32);
        Float32& operator[](Int32);
        Float32 operator[](Int32) const;

        operator Vector2();
        operator Vector3();

        friend Vector4 operator-(const Vector4&); // for negation
        friend Vector4 operator+(const Vector4&, const Vector4&);
        friend Vector4 operator-(const Vector4&, const Vector4&);
        friend Vector4 operator*(const Vector4&, const Float32);
        friend Vector4 operator*(const Float32, const Vector4&);
        friend Vector4 operator*(const Vector4&, const Matrix4x4&);
        friend Vector4 operator*(const Matrix4x4&, const Vector4&);
        friend Float32 operator*(const Vector4&, const Vector4&); // dot product
        friend Vector4 operator/(const Vector4&, const Float32);
        friend bool operator==(const Vector4&, const Vector4&);
        friend bool operator!=(const Vector4&, const Vector4&);

        // friend Vector3 operator*(const Matrix4x4, const Vector3); // linear transform
        // friend Matrix4x4 operator*(const Matrix4x4, const Matrix4x4); // Matrix 4x4 product

        void normalize();
        Vector4 get_normalized() const;
        bool is_normalized() const;

        bool has_opposite_direction_to(const Vector4&) const;

        bool has_same_direction_as(const Vector4&) const;

        bool is_collinear_to(const Vector4&) const;

        bool is_collinear_opposite_to(const Vector4&) const;

        bool is_perpendicular_to(const Vector4&) const;

        // @TODO: set with vector3 and vector4

        Float32 get_magnitude() const;
        Float32 get_magnitude_squared() const;

        Float32 get_projection(const Vector4&) const;

        Float32 get_dot_product(const Vector4&) const;

        void scalar_multiply(const Float32);

        Vector4 get_scalar_product(const Float32) const;


        inline void set(const Float32 scalar) {
            _vec[Axis::x] = scalar;
            _vec[Axis::y] = scalar;
            _vec[Axis::z] = scalar;
            _vec[Axis::w] = scalar;
        }

        inline void set(const Float32 x, const Float32 y, const Float32 z, const Float32 w) {
            _vec[Axis::x] = x;
            _vec[Axis::y] = y;
            _vec[Axis::z] = z;
            _vec[Axis::w] = w;
        }

        inline void set(const Vector4& other) {
            _vec[Axis::x] = other[Axis::x];
            _vec[Axis::y] = other[Axis::y];
            _vec[Axis::z] = other[Axis::z];
            _vec[Axis::w] = other[Axis::w];
        }

        inline Float32 get_x() const { return _vec[Axis::x]; }
        inline void set_x(const Float32 x) { _vec[Axis::x] = x; }

        inline Float32 get_y() const { return _vec[Axis::y]; }
        inline void set_y(const Float32 y) { _vec[Axis::y] = y; }

        inline Float32 get_z() const { return _vec[Axis::z]; }
        inline void set_z(const Float32 z) { _vec[Axis::z] = z; }

        inline Float32 get_w() const { return _vec[Axis::w]; }
        inline void set_w(const Float32 w) { _vec[Axis::w] = w; }

        inline void negate() { _vec[Axis::x] *= -1; _vec[Axis::y] *= -1; _vec[Axis::z] *= -1; _vec[Axis::w] *= -1; }

        inline bool is_zero() const { return (_vec[Axis::x] == 0.0f && _vec[Axis::y] == 0.0f && _vec[Axis::z] == 0.0f && _vec[Axis::w] == 0.0f); }

        inline StringRepr to_string() const override { return "Vector4"; }
    };

    // ---------
    // Matrix3x3
    // ---------

    class Matrix3x3 : public virtual IZeroObject {
    private:
        Vector3 _matrix[3];
    public:

        static const Matrix3x3& identity2D();

        static Matrix3x3 get_translation_2D(const Vector2&);
        static Matrix3x3 get_rotation_2D(const Vector2& center, const Degree angle);
        static Matrix3x3 get_scaling_2D(const Vector2&);

        /* @TODO: Unit matrices
        static Vector4 zero;
        static Vector4 unit_i; // x-axis unit vector
        static Vector4 unit_j; // y-axis unit vector
        static Vector4 unit_k; // z-axis unit vector
        */

        Matrix3x3();
        Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2);
        explicit Matrix3x3(const Float32);
        Matrix3x3(const Matrix3x3&);

        Matrix3x3& operator=(const Matrix3x3&);
        Matrix3x3& operator+=(const Matrix3x3&);
        Matrix3x3& operator-=(const Matrix3x3&);
        Matrix3x3& operator*=(const Float32);
        Matrix3x3& operator/=(const Float32);
        Vector3& operator[](Int32);
        Vector3 operator[](Int32) const;

        friend Matrix3x3 operator-(const Matrix3x3&); // for negation
        friend Matrix3x3 operator+(const Matrix3x3&, const Matrix3x3&);
        friend Matrix3x3 operator-(const Matrix3x3&, const Matrix3x3&);
        friend Matrix3x3 operator/(const Matrix3x3&, const Float32);

        friend Matrix3x3 operator*(const Matrix3x3&, const Float32);
        friend Matrix3x3 operator*(const Float32, const Matrix3x3&);
        friend Matrix3x3 operator*(const Matrix3x3&, const Matrix3x3&);

        friend bool operator==(const Matrix3x3&, const Matrix3x3&);
        friend bool operator!=(const Matrix3x3&, const Matrix3x3&);

        // @TODO: < && >

        Vector2 get_linear_transform(const Vector2&) const;
        Vector3 get_linear_transform(const Vector3&) const;

        void transpose();
        Matrix3x3 get_transposition() const;

        void inverse();
        Matrix3x3 get_inverse() const;

        void translate(const Vector2&);
        void rotate(const Vector2& center, const Degree angle);
        void scale(const Vector2&);

        inline StringRepr to_string() const override { return "Matrix3x3"; }
    };

    // ---------
    // Matrix4x4
    // ---------

    class Matrix4x4 : public virtual IZeroObject {
    private:
        Vector4 _matrix[4];
    public:
        static const Matrix4x4 identity3D();
        static Matrix4x4 get_translation_3D(const Vector3&);
        static Matrix4x4 get_rotation_3D(const Vector3& axis, const Degree angle);
        static Matrix4x4 get_scaling_3D(const Vector3&);
        static Matrix4x4 get_perspective_3D(const Float32);

        Matrix4x4();
        Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);
        explicit Matrix4x4(const Float32);
        Matrix4x4(const Matrix4x4&);

        Matrix4x4& operator=(const Matrix4x4&);
        Matrix4x4& operator+=(const Matrix4x4&);
        Matrix4x4& operator-=(const Matrix4x4&);
        Matrix4x4& operator*=(const Float32);
        Matrix4x4& operator/=(const Float32);
        Vector4& operator[](Int32);
        Vector4 operator[](Int32) const;

        friend Matrix4x4 operator-(const Matrix4x4&); // for negation
        friend Matrix4x4 operator+(const Matrix4x4&, const Matrix4x4&);
        friend Matrix4x4 operator-(const Matrix4x4&, const Matrix4x4&);

        friend Matrix4x4 operator*(const Matrix4x4&, const Float32);
        friend Matrix4x4 operator*(const Float32, const Matrix4x4&);
        friend Matrix4x4 operator*(const Matrix4x4&, const Matrix4x4&);

        friend Matrix4x4 operator/(const Matrix4x4&, const Float32);

        friend bool operator==(const Matrix4x4&, const Matrix4x4&);
        friend bool operator!=(const Matrix4x4&, const Matrix4x4&);

        Vector3 get_linear_transform(const Vector3&) const;
        Vector4 get_linear_transform(const Vector4&) const;

        void transpose();
        Matrix4x4 get_transposition() const;

        void inverse();
        Matrix4x4 get_inverse() const;

        void translate(const Vector3&);
        void rotate(const Vector3& axis, const Degree angle);
        void scale(const Vector3&);

        inline StringRepr to_string() const override { return "Matrix4x4"; }
    };
}
