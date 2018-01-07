#pragma once

#include "../ZeroEngineStd.h"
#include "Math.h"

//
// These classes are based off of Graphics Gems IV. p.534
//

// @TODO: Maybe cache magnitudes for vector classes so they only 
// need to be calculated when necessary

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

    /* Vec2 decl */

    class Vector2 : public virtual IZeroObject {
    private:
        Float32 _vec[2];
    public:
        static const Vector2& zero();
        static const Vector2& unit_i(); // x-axis unit vector
        static const Vector2& unit_j(); // y-axis unit vector
        static Vector2 lerp(const Vector2&, const Vector2&, const Float32);

        Vector2();
        explicit Vector2(const Float32);
        explicit Vector2(const Float64);
        explicit Vector2(const Int32);
        Vector2(const Float32 x, const Float32 y);
        Vector2(const Float64 x, const Float64 y);
        Vector2(const Int32 x, const Int32 y);
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
        friend Vector2 operator-(const Vector2&, const Vector2&);

        friend Vector2 operator+(const Vector2&, const Vector2&);

        friend Vector2 operator*(const Vector2&, const Float32);
        friend Vector2 operator*(const Float32, const Vector2&);

        friend Vector2 operator/(const Vector2&, const Float32);

        friend bool operator==(const Vector2&, const Vector2&);
        friend bool operator!=(const Vector2&, const Vector2&);

        friend std::ostream& operator<<(std::ostream&, const Vector2&);

        Vector2& normalize();
        Vector2 get_normalized() const;
        bool is_normalized() const;

        bool has_opposite_direction_to(const Vector2&) const;

        bool has_same_direction_as(const Vector2&) const;

        bool is_collinear_to(const Vector2&) const;

        bool is_collinear_opposite_to(const Vector2&) const;

        bool is_perpendicular_to(const Vector2&) const;

        Float32 get_magnitude() const;
        Float32 get_magnitude_squared() const;

        Float32 get_scalar_projection(const Vector2&) const;
        Vector2 get_vector_projection(const Vector2&) const;
        Vector2& project_onto(const Vector2&);

        Float32 get_dot_product(const Vector2&) const;
        Vector3 get_cross_product(const Vector2&) const;

        Vector2& scalar_multiply(const Float32);
        Vector2 get_scalar_product(const Float32);

        Vector2& euler_integrate(const Vector2&, const Float32);
        Vector2 get_euler_integration(const Vector2&, const Float32) const;

        Float32 distance_between(const Vector2&) const;
        Float32 distance_between_squared(const Vector2&) const;

        Radian radians_between(const Vector2&) const;
        Degree degrees_between(const Vector2&) const;

        // @TODO for all vector classes:
        // Vector2 get_reverse() const;
        // 
        // returns positive if other is clockwise to
        // this and negative if counter clockwise.
        // I want different name than sign()
        // Int8 sign(const Vector2& other) const;

        Vector2& truncate(const Float32 max);
        Vector2 get_truncated(const Float32 max) const;

        inline Vector2& make_zero() { *this = Vector2::zero(); return *this; }
        inline bool is_zero() const { return *this == Vector2::zero(); }

        inline Vector2& set(const Float32 val) { _vec[Axis::x] = val; _vec[Axis::y] = val; return *this; }
        inline Vector2& set(const Float32 x, const Float32 y) { _vec[Axis::x] = x; _vec[Axis::y] = y; return *this; }
        inline Vector2& set(const Vector2& other) { _vec[Axis::x] = other[Axis::x]; _vec[Axis::y] = other[Axis::y]; return *this; }

        inline Float32 get_x() const { return _vec[Axis::x]; }
        inline Vector2& set_x(const Float32 x) { _vec[Axis::x] = x; return *this; }

        inline Float32 get_y() const { return _vec[Axis::y]; }
        inline Vector2& set_y(const Float32 y) { _vec[Axis::y] = y; return *this; }

        inline Vector2& negate() { _vec[Axis::x] *= -1; _vec[Axis::y] *= -1; return *this; }

        inline StringRepr to_string() const override { return "Vector2"; }

        #ifdef _DEBUG
        static void run_unit_test();
        #endif
    };

    // -------
    // Vector3
    // -------

    /* Vec3 decl */

    class Vector3 : public virtual IZeroObject {
    private:
        Float32 _vec[3];
    public:
        static const Vector3& zero();
        static const Vector3& unit_i(); // x-axis unit vector
        static const Vector3& unit_j(); // y-axis unit vector
        static const Vector3& unit_k(); // z-axis unit vector
        static Vector3 lerp(const Vector3&, const Vector3&, const Float32);

        Vector3();
        explicit Vector3(const Float32);
        explicit Vector3(const Float64);
        explicit Vector3(const Int32);
        Vector3(const Float32 x, const Float32 y, const Float32 z);
        Vector3(const Float64 x, const Float64 y, const Float64 z);
        Vector3(const Int32 x, const Int32 y, const Int32 z);
        Vector3(const Vector3&);
        Vector3(const Vector2&);
        Vector3(const Vector2&, const Float32 z);
        Vector3(const Vector2&, const Float64 z);
        Vector3(const Vector2&, const Int32 z);
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

        friend Vector3 operator/(const Vector3&, const Float32);

        friend bool operator==(const Vector3&, const Vector3&);
        friend bool operator!=(const Vector3&, const Vector3&);

        friend std::ostream& operator<<(std::ostream&, const Vector3&);

        Vector3& normalize();
        Vector3 get_normalized() const;
        bool is_normalized() const;

        bool has_opposite_direction_to(const Vector3&) const;

        bool has_same_direction_as(const Vector3&) const;

        bool is_collinear_to(const Vector3&) const;

        bool is_collinear_opposite_to(const Vector3&) const;

        bool is_perpendicular_to(const Vector3&) const;

        Float32 get_magnitude() const;
        Float32 get_magnitude_squared() const;

        Float32 get_scalar_projection(const Vector3&) const;
        Vector3 get_vector_projection(const Vector3&) const;
        Vector3& project_onto(const Vector3&);

        Float32 get_dot_product(const Vector3&) const;
        Vector3 get_cross_product(const Vector3&) const;

        Vector3& scalar_multiply(const Float32);
        Vector3 get_scalar_product(const Float32) const;

        Vector3& euler_integrate(const Vector3&, const Float32);
        Vector3 get_euler_integration(const Vector3&, const Float32) const;

        Float32 distance_between(const Vector3&) const;
        Float32 distance_between_squared(const Vector3&) const;

        Vector3& truncate(const Float32);
        Vector3 get_truncated(const Float32) const;

        Radian radians_between(const Vector3&) const;
        Degree degrees_between(const Vector3&) const;

        // row-major transformation
        Vector3& transform_by_matrix(const Matrix3x3);
        Vector3 get_matrix_transform(const Matrix3x3&) const;

        inline Vector3& set(const Float32 scalar) {
            _vec[Axis::x] = scalar;
            _vec[Axis::y] = scalar;
            _vec[Axis::z] = scalar;
            return *this;
        }

        inline Vector3& set(const Float32 x, const Float32 y, const Float32 z) {
            _vec[Axis::x] = x;
            _vec[Axis::y] = y;
            _vec[Axis::z] = z;
            return *this;
        }

        inline Vector3& set(const Vector3& other) {
            _vec[Axis::x] = other[Axis::x];
            _vec[Axis::y] = other[Axis::y];
            _vec[Axis::z] = other[Axis::z];
            return *this;
        }

        inline Float32 get_x() const { return _vec[Axis::x]; }
        inline Vector3& set_x(const Float32 x) { _vec[Axis::x] = x; return *this; }

        inline Float32 get_y() const { return _vec[Axis::y]; }
        inline Vector3& set_y(const Float32 y) { _vec[Axis::y] = y; return *this;}

        inline Float32 get_z() const { return _vec[Axis::z]; }
        inline Vector3& set_z(const Float32 z) { _vec[Axis::z] = z; return *this; }

        inline Vector3& negate() { _vec[Axis::x] *= -1; _vec[Axis::y] *= -1; _vec[Axis::z] *= -1; return *this; }

        inline Vector3& make_zero() { *this = Vector3::zero(); return *this; }
        inline bool is_zero() const { return *this == Vector3::zero(); }

        inline StringRepr to_string() const override { return "Vector3"; }

        #ifdef _DEBUG
        static void run_unit_test();
        #endif
    };



    // -------
    // Vector4
    // -------

    /* Vec4 decl */

    class Vector4 : public virtual IZeroObject {
    private:
        Float32 _vec[4];
    public:
        static const Vector4& zero();
        static const Vector4& unit_i(); // x-axis unit vector
        static const Vector4& unit_j(); // y-axis unit vector
        static const Vector4& unit_k(); // z-axis unit vector
        static Vector4 lerp(const Vector4&, const Vector4&, const Float32);

        Vector4();
        explicit Vector4(const Float32);
        explicit Vector4(const Float64);
        explicit Vector4(const Int32);
        Vector4(const Float32 x, const Float32 y, const Float32 z, const Float32 w);
        Vector4(const Float64 x, const Float64 y, const Float64 z, const Float64 w);
        Vector4(const Int32 x, const Int32 y, const Int32 z, const Int32 w);
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
        friend Vector4 operator-(const Vector4&, const Vector4&);

        friend Vector4 operator+(const Vector4&, const Vector4&);

        friend Vector4 operator*(const Vector4&, const Float32);
        friend Vector4 operator*(const Float32, const Vector4&);

        friend Vector4 operator/(const Vector4&, const Float32);

        friend bool operator==(const Vector4&, const Vector4&);
        friend bool operator!=(const Vector4&, const Vector4&);

        friend std::ostream& operator<<(std::ostream&, const Vector4&);

        Vector4& normalize();
        Vector4 get_normalized() const;
        bool is_normalized() const;

        bool has_opposite_direction_to(const Vector4&) const;

        bool has_same_direction_as(const Vector4&) const;

        bool is_collinear_to(const Vector4&) const;

        bool is_collinear_opposite_to(const Vector4&) const;

        bool is_perpendicular_to(const Vector4&) const;

        Float32 get_magnitude() const;
        Float32 get_magnitude_squared() const;

        Float32 get_scalar_projection(const Vector4&) const;
        Vector4 get_vector_projection(const Vector4&) const;
        Vector4& project_onto(const Vector4&);

        Float32 get_dot_product(const Vector4&) const;

        Vector4& scalar_multiply(const Float32);
        Vector4 get_scalar_product(const Float32) const;

        Vector4& euler_integrate(const Vector4&, const Float32);
        Vector4 get_euler_integration(const Vector4&, const Float32) const;

        Float32 distance_between(const Vector4&) const;
        Float32 distance_between_squared(const Vector4&) const;

        Vector4& truncate(const Float32);
        Vector4 get_truncated(const Float32) const;

        Radian radians_between(const Vector4&) const;
        Degree degrees_between(const Vector4&) const;

        Vector4& transform_by_matrix(const Matrix4x4&);
        Vector4 get_matrix_transform(const Matrix4x4&) const;

        inline Vector4& set(const Float32 scalar) {
            _vec[Axis::x] = scalar;
            _vec[Axis::y] = scalar;
            _vec[Axis::z] = scalar;
            _vec[Axis::w] = scalar;
            return *this;
        }

        inline Vector4& set(const Float32 x, const Float32 y, const Float32 z, const Float32 w) {
            _vec[Axis::x] = x;
            _vec[Axis::y] = y;
            _vec[Axis::z] = z;
            _vec[Axis::w] = w;
            return *this;
        }

        inline Vector4& set(const Vector4& other) {
            _vec[Axis::x] = other[Axis::x];
            _vec[Axis::y] = other[Axis::y];
            _vec[Axis::z] = other[Axis::z];
            _vec[Axis::w] = other[Axis::w];
            return *this;
        }

        inline Float32 get_x() const { return _vec[Axis::x]; }
        inline Vector4& set_x(const Float32 x) { _vec[Axis::x] = x; return *this; }

        inline Float32 get_y() const { return _vec[Axis::y]; }
        inline Vector4& set_y(const Float32 y) { _vec[Axis::y] = y; return *this; }

        inline Float32 get_z() const { return _vec[Axis::z]; }
        inline Vector4& set_z(const Float32 z) { _vec[Axis::z] = z; return *this; }

        inline Float32 get_w() const { return _vec[Axis::w]; }
        inline Vector4& set_w(const Float32 w) { _vec[Axis::w] = w; return *this; }

        inline Vector4& negate() { 
            _vec[Axis::x] *= -1; 
            _vec[Axis::y] *= -1; 
            _vec[Axis::z] *= -1; 
            _vec[Axis::w] *= -1; 
            return *this;
        }

        inline Vector4& make_zero() { *this = Vector4::zero(); return *this; }
        inline bool is_zero() const { return *this == Vector4::zero(); }

        inline StringRepr to_string() const override { return "Vector4"; }

        #ifdef _DEBUG
        static void run_unit_test();
        #endif
    };

    // ---------
    // Matrix3x3
    // ---------

    class Matrix3x3 : public virtual IZeroObject {
    private:
        Vector3 _matrix[3];
    public:
        static const Matrix3x3& identity();
        static Matrix3x3 get_translation_2D(const Vector2&);
        static Matrix3x3 get_rotation_2D(const Vector2& center, const Degree angle);
        static Matrix3x3 get_scaling_2D(const Vector2&);

    public:
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

        friend std::ostream& operator<<(std::ostream&, const Matrix3x3&);

        Matrix3x3& transpose();
        Matrix3x3 get_transposition() const;

        Matrix3x3& inverse();
        Matrix3x3 get_inverse() const;

        // @TODO: Test translate ange get_translation_2D()
        Matrix3x3& translate(const Vector2&);

        Matrix3x3& rotate(const Vector2& center, const Degree angle);

        Matrix3x3& rotate_x(const Degree);
        Matrix3x3 get_rotation_x(const Degree) const;

        Matrix3x3& rotate_y(const Degree);
        Matrix3x3 get_rotation_y(const Degree) const;

        Matrix3x3& scale(const Vector2&);

        inline StringRepr to_string() const override { return "Matrix3x3"; }

        #ifdef _DEBUG
        static void run_unit_test();
        #endif
    };

    // ---------
    // Matrix4x4
    // ---------

    /* mat4 decl */

    class Matrix4x4 : public virtual IZeroObject {
    private:
        Vector4 _matrix[4];
    public:
        static const Matrix4x4 identity();
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

        friend std::ostream& operator<<(std::ostream&, const Matrix4x4&);

        Matrix4x4& transpose();
        Matrix4x4 get_transposition() const;

        Matrix4x4& inverse();
        Matrix4x4 get_inverse() const;

        Matrix4x4& translate(const Vector3&);

        Matrix4x4& rotate(const Vector3& axis, const Degree angle);

        Matrix4x4& rotate_x(const Degree);
        Matrix4x4 get_rotation_x(const Degree) const;

        Matrix4x4& rotate_y(const Degree);
        Matrix4x4 get_rotation_y(const Degree) const;

        Matrix4x4& rotate_z(const Degree);
        Matrix4x4 get_rotation_z(const Degree) const;

        Matrix4x4& scale(const Vector3&);

        inline StringRepr to_string() const override { return "Matrix4x4"; }

        #ifdef _DEBUG
        static void run_unit_test();
        #endif
    };

    #ifdef _DEBUG
    namespace MathTypes {
        extern void run_all_unit_tests();
    }
    #endif
}
