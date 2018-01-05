#include "MathTypes.h"

namespace ZeroEngine {

    // ----
    // Axis
    // ----

    namespace Axis {

        constexpr AxisIndex x = 0;
        constexpr AxisIndex y = 1;
        constexpr AxisIndex z = 2;
        constexpr AxisIndex w = 3;

        std::string to_string(AxisIndex axis) {
            switch (axis) {
                case 0:
                    return std::string("Axis::x");
                case 1:
                    return std::string("Axis::y");
                case 2:
                    return std::string("Axis::z");
                case 3:
                    return std::string("Axis::w");
                default:
                    return std::string("Unknown Axis");
            }
        }
    }

    // -------
    // Vector2
    // -------

    constexpr Vector2& Vector2::zero() {
        static Vector2 zero_vector = Vector2(0.0f, 0.0f);
        return zero_vector;
    }

    constexpr Vector2& Vector2::unit_i() {
        static Vector2 i_vector = Vector2(1.0f, 0.0f);
        return i_vector;
    }

    constexpr Vector2& Vector2::unit_j() {
        static Vector2 j_vector = Vector2(0.0f, 1.0f);
        return j_vector;
    }

    Vector2::Vector2() {
        _vec[Axis::x] = 0.0f;
        _vec[Axis::y] = 0.0f;
    }

    Vector2::Vector2(const Float32 value) {
        _vec[Axis::x] = value;
        _vec[Axis::y] = value;
    }

    Vector2::Vector2(const Vector2& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
    }

    Vector2::Vector2(const Vector3& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
    }

    Vector2::Vector2(const Vector4& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
    }

    Vector2& Vector2::operator=(const Vector2& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        return *this;
    }

    Vector2& Vector2::operator+=(const Vector2& other) {
        _vec[Axis::x] += other[Axis::x];
        _vec[Axis::y] += other[Axis::y];
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other) {
        _vec[Axis::x] -= other[Axis::x];
        _vec[Axis::y] -= other[Axis::y];
        return *this;
    }

    Vector2& Vector2::operator*=(const Float32 scalar) {
        _vec[Axis::x] *= scalar;
        _vec[Axis::y] *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(const Float32 scalar) {
        Float32 reciprocal = 1.0f / scalar;
        _vec[Axis::x] *= reciprocal;
        _vec[Axis::y] *= reciprocal;
        return *this;
    }

    Float32& Vector2::operator[](Int32 index) {
        assert(Axis::x <= index && index <= Axis::y);
        return _vec[index];
    }

    Float32 Vector2::operator[](Int32 index) const {
        assert(Axis::x <= index && index <= Axis::y);
        return _vec[index];
    }

    Vector2::operator Vector3() {
        return Vector3(_vec[Axis::x], _vec[Axis::y], 1.0f);
    }

    Vector2::operator Vector4() {
        return Vector4(_vec[Axis::x], _vec[Axis::y], 1.0f, 1.0f);
    }

    Vector2 operator-(const Vector2& vec) {
        return Vector2(-vec[Axis::x], -vec[Axis::y]);
    }

    Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
        return Vector2(lhs[Axis::x] + rhs[Axis::x], lhs[Axis::y] + rhs[Axis::y]);
    }

    Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
        return Vector2(lhs[Axis::x] - rhs[Axis::x], lhs[Axis::y] - rhs[Axis::y]);
    }

    Vector2 operator*(const Vector2& vec, const Float32 scalar) {
        return Vector2(vec[Axis::x] * scalar, vec[Axis::y] * scalar);
    }

    Vector2 operator*(const Float32 scalar, const Vector2& vec) {
        return Vector2(vec[Axis::x] * scalar, vec[Axis::y] * scalar);
    }

    // @TODO: Test why this can't just call matrix.get_transposition()
    Vector2 operator*(const Matrix3x3& matrix, const Vector2& vec) {
        Vector2 ret_vec;
        ret_vec[Axis::x] = (matrix[0][Axis::x] * vec[Axis::x]) + (matrix[0][Axis::y] * vec[Axis::y]) + matrix[0][Axis::z];
        ret_vec[Axis::y] = (matrix[1][Axis::x] * vec[Axis::x]) + (matrix[1][Axis::y] * vec[Axis::y]) + matrix[1][Axis::z];
        return ret_vec;
    }

    Vector2 operator*(const Vector2& vec, const Matrix3x3& matrix) {
        return matrix.get_transposition() * vec;
    }

    Vector2 operator/(const Vector2& vec, const Float32 scalar) {
        Float32 reciprocal = 1.0f / scalar;
        return Vector2(vec[Axis::x] * reciprocal, vec[Axis::y] * reciprocal); 
    }

    Float32 operator*(const Vector2& lhs, const Vector2& rhs) {
        return (lhs[Axis::x] * rhs[Axis::x]) + (lhs[Axis::y] * rhs[Axis::y]);
    }

    Vector3 operator^(const Vector2& lhs, const Vector2& rhs) {
        return Vector3(0.0f, 0.0f, (lhs[Axis::x] * rhs[Axis::y]) - (rhs[Axis::x] * lhs[Axis::y]));
    }

    bool operator==(const Vector2& lhs, const Vector2& rhs) {
        return (lhs[Axis::x] == rhs[Axis::x]) && (lhs[Axis::y] == rhs[Axis::y]);
    }

    bool operator!=(const Vector2& lhs, const Vector2& rhs) {
        return !(lhs == rhs);
    }

    void Vector2::normalize() {
        *this *= (1 / get_magnitude());
    }

    Vector2 Vector2::get_normalized() const {
        return *this * (1 / get_magnitude());
    }

    bool Vector2::is_normalized() const {
        return get_magnitude() == 1.0f;
    }

    bool Vector2::has_opposite_direction_as(const Vector2& other) const {
        return get_dot_product(other) < 0;
    }

    bool Vector2::has_same_direction_as(const Vector2& other) const {
        return !(has_opposite_direction_as(other));
    }

    bool Vector2::is_collinear_to(const Vector2& other) const {
        return get_dot_product(other) == get_magnitude() * other.get_magnitude();
    }

    bool Vector2::is_collinear_opposite_to(const Vector2& other) const {
        return get_dot_product(other) == -(get_magnitude() * other.get_magnitude());
    }

    bool Vector2::is_perpendicular_to(const Vector2& other) const {
        return get_dot_product(other) == 0;
    }

    Float32 Vector2::get_magnitude() const {
        return Math::square_root(get_magnitude_squared());
    }

    Float32 Vector2::get_magnitude_squared() const {
        return (_vec[Axis::x] * _vec[Axis::x]) + (_vec[Axis::y] * _vec[Axis::y]);
    }

    Float32 Vector2::get_projection(const Vector2& other) const {
        return (other.is_normalized()) ? get_dot_product(other) : get_dot_product(other.get_normalized());
    }

    Float32 Vector2::get_dot_product(const Vector2& other) const {
        return (_vec[Axis::x] * other[Axis::x]) + (_vec[Axis::y] * other[Axis::y]);
    }

    Vector3 Vector2::get_cross_product(const Vector2& other) const {
       return *this ^ other; 
    }

    void Vector2::scalar_multiply(const Float32 scalar) {
        *this *= scalar;
    }

    Vector2 Vector2::get_scalar_product(const Float32 scalar) {
        return *this * scalar;
    }

    // -------
    // Vector3
    // -------

    constexpr Vector3& Vector3::zero() {
        static Vector3 zero_vec = Vector3(0.0f, 0.0f, 0.0f);
        return zero_vec;
    }

    constexpr Vector3& Vector3::unit_i() {
        static Vector3 i_vector = Vector3(1.0f, 0.0f, 0.0f);
        return i_vector;
    }

    constexpr Vector3& Vector3::unit_j() {
        static Vector3 j_vector = Vector3(0.0f, 1.0f, 0.0f);
        return j_vector;
    }

    constexpr Vector3& Vector3::unit_k() {
        static Vector3 k_vector = Vector3(0.0f, 0.0f, 1.0f);
        return k_vector;
    }

    Vector3::Vector3() {
        _vec[Axis::x] = 0.0f;
        _vec[Axis::y] = 0.0f;
        _vec[Axis::z] = 0.0f;
    }

    Vector3::Vector3(const Float32 scalar) {
        _vec[Axis::x] = scalar;
        _vec[Axis::y] = scalar;
        _vec[Axis::z] = scalar;
    }

    Vector3::Vector3(const Float32 x, const Float32 y, const Float32 z) {
        _vec[Axis::x] = x;
        _vec[Axis::y] = y;
        _vec[Axis::z] = z;
    }

    Vector3::Vector3(const Vector3& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = other[Axis::z];
    }

    Vector3::Vector3(const Vector2& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = 1.0f;
    }

    Vector3::Vector3(const Vector2& other, const Float32 z) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = z;
    }

    Vector3::Vector3(const Vector4& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = other[Axis::z];
    }

    Vector3& Vector3::operator=(const Vector3& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = other[Axis::z];
        return *this;
    }

    Vector3& Vector3::operator+=(const Vector3& other) {
        _vec[Axis::x] += other[Axis::x];
        _vec[Axis::y] += other[Axis::y];
        _vec[Axis::z] += other[Axis::z];
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& other) {
        _vec[Axis::x] -= other[Axis::x];
        _vec[Axis::y] -= other[Axis::y];
        _vec[Axis::z] -= other[Axis::z];
        return *this;
    }

    Vector3& Vector3::operator*=(const Float32 scalar) {
        _vec[Axis::x] *= scalar;
        _vec[Axis::y] *= scalar;
        _vec[Axis::z] *= scalar;
        return *this;
    }

    Vector3& Vector3::operator/=(const Float32 scalar) {
        _vec[Axis::x] /= scalar;
        _vec[Axis::y] /= scalar;
        _vec[Axis::z] /= scalar;
        return *this;
    }

    Float32& Vector3::operator[](Int32 index) {
        assert(Axis::x <= index && index <= Axis::z);
        return _vec[index];
    }

    Float32 Vector3::operator[](Int32 index) const {
        assert(Axis::x <= index && index <= Axis::z);
        return _vec[index];
    }

    Vector3::operator Vector2() {
        return Vector2(_vec[Axis::x], _vec[Axis::y]);
    }

    Vector3::operator Vector4() {
        return Vector4(_vec[Axis::x], _vec[Axis::y], _vec[Axis::z], 1.0f);
    }

    Vector3 operator-(const Vector3& vec) {
        return Vector3(-vec.get_x(), -vec.get_y(), -vec.get_z());
    }

    Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
        return Vector3(lhs[Axis::x] + rhs[Axis::x], lhs[Axis::y] + rhs[Axis::y], lhs[Axis::z] + rhs[Axis::z]);
    }

    Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
        return Vector3(lhs[Axis::x] - rhs[Axis::x], lhs[Axis::y] - rhs[Axis::y], lhs[Axis::z] - rhs[Axis::z]);
    }

    Vector3 operator*(const Vector3& vec, const Float32 scalar) {
        return Vector3(vec[Axis::x] * scalar, vec[Axis::y] * scalar, vec[Axis::z] * scalar);
    }

    Vector3 operator*(const Float32 scalar, const Vector3& vec) {
        return vec * scalar;
    }

    Vector3 operator*(const Vector3& vec, const Matrix4x4& matrix) {
        return matrix * Vector4(vec);
    }

    Vector3 operator*(const Matrix4x4& matrix, const Vector3& vec) {
        return matrix.get_transposition() * vec;
    }

    Vector3 operator/(const Vector3& vec, const Float32 scalar) {
        Float32 reciprocal = 1 / scalar;
        return vec * scalar;
    }

    Float32 operator*(const Vector3& lhs, const Vector3& rhs) {
        return (lhs[Axis::x] * rhs[Axis::x]) + (lhs[Axis::y] * rhs[Axis::y]) + (lhs[Axis::z] * rhs[Axis::z]);
    }

    Vector3 operator^(const Vector3& lhs, const Vector3& rhs) {
        return Vector3((lhs[Axis::y] * rhs[Axis::z]) - (lhs[Axis::z] * rhs[Axis::y]),
                       (lhs[Axis::z] * rhs[Axis::x]) - (lhs[Axis::x] * rhs[Axis::z]),
                       (lhs[Axis::x] * rhs[Axis::y]) - (lhs[Axis::y] * rhs[Axis::x]));
    }

    bool operator==(const Vector3& lhs, const Vector3& rhs) {
        return (lhs[Axis::x] == rhs[Axis::x]) && (lhs[Axis::y] == rhs[Axis::y]) && (lhs[Axis::z] == rhs[Axis::z]);
    }

    bool operator!=(const Vector3& lhs, const Vector3& rhs) {
        return !(lhs == rhs);
    }

    void Vector3::normalize() {
        *this *= (1 / get_magnitude());
    }

    Vector3 Vector3::get_normalized() const {
        return *this * (1 / get_magnitude());
    }

    bool Vector3::is_normalized() const {
        return get_magnitude() == 1.0f;
    }

    bool Vector3::has_opposite_direction_to(const Vector3& other) {

    }



    

}