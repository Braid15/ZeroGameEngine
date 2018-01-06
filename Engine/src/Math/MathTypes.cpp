#include "MathTypes.h"

namespace ZeroEngine {

    // ----
    // Axis
    // ----

    namespace Axis {

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

    const Vector2& Vector2::zero() {
        static Vector2 zero_vec = Vector2(0.0f, 0.0f);
        return zero_vec;
    }

    const Vector2& Vector2::unit_i() {
        static Vector2 i_vec = Vector2(1.0f, 0.0f);
        return i_vec;
    }

    const Vector2& Vector2::unit_j() {
        static Vector2 j_vec = Vector2(0.0f, 1.0f);
        return j_vec;
    }

    Vector2::Vector2() {
        _vec[Axis::x] = 0.0f;
        _vec[Axis::y] = 0.0f;
    }

    Vector2::Vector2(const Float32 value) {
        _vec[Axis::x] = value;
        _vec[Axis::y] = value;
    }

    Vector2::Vector2(const Float32 x, const Float32 y) {
        _vec[Axis::x] = x;
        _vec[Axis::y] = y;
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

    /*
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
    */

    Vector2 operator/(const Vector2& vec, const Float32 scalar) {
        Float32 reciprocal = 1.0f / scalar;
        return Vector2(vec[Axis::x] * reciprocal, vec[Axis::y] * reciprocal); 
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

    bool Vector2::has_opposite_direction_to(const Vector2& other) const {
        return get_dot_product(other) < 0;
    }

    bool Vector2::has_same_direction_as(const Vector2& other) const {
        return !(has_opposite_direction_to(other));
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
        return Vector3(0.0f, 0.0f, (_vec[Axis::x] * other[Axis::y]) - (other[Axis::x] * _vec[Axis::y]));
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

    const Vector3& Vector3::zero() {
        static Vector3 zero_vec = Vector3(0.0f, 0.0f, 0.0f);
        return zero_vec;
    }

    const Vector3& Vector3::unit_i() {
        static Vector3 i_vec = Vector3(1.0f, 0.0f, 0.0f);
        return i_vec;
    }

    const Vector3& Vector3::unit_j() {
        static Vector3 j_vec = Vector3(0.0f, 1.0f, 0.0f);
        return j_vec;
    }

    const Vector3& Vector3::unit_k() {
        static Vector3 k_vec = Vector3(0.0f, 0.0f, 1.0f);
        return k_vec;
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

    /*
    Vector3 operator*(const Vector3& vec, const Matrix4x4& matrix) {
        return matrix * Vector4(vec);
    }

    Vector3 operator*(const Matrix4x4& matrix, const Vector3& vec) {
        return matrix.get_transposition() * Vector4(vec);
    }
    */

    Vector3 operator/(const Vector3& vec, const Float32 scalar) {
        Float32 reciprocal = 1 / scalar;
        return vec * scalar;
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

    bool Vector3::has_opposite_direction_to(const Vector3& other) const {
        return get_dot_product(other) < 0;
    }

    bool Vector3::has_same_direction_as(const Vector3& other) const {
        return !(has_opposite_direction_to(other));
    }

    bool Vector3::is_collinear_to(const Vector3& other) const {
        return get_dot_product(other) == get_magnitude() * other.get_magnitude();
    }

    bool Vector3::is_collinear_opposite_to(const Vector3& other) const {
        return get_dot_product(other) == -(get_magnitude() * other.get_magnitude());
    }

    bool Vector3::is_perpendicular_to(const Vector3& other) const {
        return get_dot_product(other) == 0;
    }

    Float32 Vector3::get_magnitude() const {
        return Math::square_root(get_magnitude_squared());
    }

    Float32 Vector3::get_magnitude_squared() const {
        return (_vec[Axis::x] * _vec[Axis::x]) + (_vec[Axis::y] * _vec[Axis::y]) + (_vec[Axis::z] * _vec[Axis::z]);
    }

    Float32 Vector3::get_projection(const Vector3& other) const {
        return (other.is_normalized()) ? get_dot_product(other) : get_dot_product(other.get_normalized());
    }

    Float32 Vector3::get_dot_product(const Vector3& other) const {
        return (_vec[Axis::x] * other[Axis::x]) + (_vec[Axis::y] * other[Axis::y]) + (_vec[Axis::z] * other[Axis::z]);
    }

    Vector3 Vector3::get_cross_product(const Vector3& other) const {
        return Vector3((_vec[Axis::y] * other[Axis::z]) - (_vec[Axis::z] * other[Axis::y]),
                       (_vec[Axis::z] * other[Axis::x]) - (_vec[Axis::x] * other[Axis::z]),
                       (_vec[Axis::x] * other[Axis::y]) - (_vec[Axis::y] * other[Axis::x]));
    }

    void Vector3::scalar_multiply(const Float32 scalar) {
        *this *= scalar;
    }

    Vector3 Vector3::get_scalar_product(const Float32 scalar) const {
        return *this * scalar;
    }

    // -------
    // Vector4
    // -------

    const Vector4& Vector4::zero() {
        static Vector4 zero_vec = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
        return zero_vec;
    }

    const Vector4& Vector4::unit_i() {
        static Vector4 i_vec = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
        return i_vec;
    }

    const Vector4& Vector4::unit_j() {
        static Vector4 j_vec = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
        return j_vec;
    }

    const Vector4& Vector4::unit_k() {
        static Vector4 k_vec = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
        return k_vec;
    }

    Vector4::Vector4() {
        _vec[Axis::x] = 0.0f;
        _vec[Axis::y] = 0.0f;
        _vec[Axis::z] = 0.0f;
        _vec[Axis::w] = 0.0f;
    }

    Vector4::Vector4(const Float32 val) {
        _vec[Axis::x] = val; 
        _vec[Axis::y] = val;
        _vec[Axis::z] = val;
        _vec[Axis::w] = val;
    }

    Vector4::Vector4(const Float32 x, const Float32 y, const Float32 z, const Float32 w) {
        _vec[Axis::x] = x;
        _vec[Axis::y] = y;
        _vec[Axis::z] = z;
        _vec[Axis::w] = w;
    }

    Vector4::Vector4(const Vector4& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = other[Axis::z];
        _vec[Axis::w] = other[Axis::w];
    }

    Vector4::Vector4(const Vector3& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = other[Axis::z];
        _vec[Axis::w] = 1.0f;
    }

    Vector4::Vector4(const Vector3& other, const Float32 w) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = other[Axis::z];
        _vec[Axis::w] = w;
    }

    Vector4::Vector4(const Vector2& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = 1.0f;
        _vec[Axis::w] = 1.0f;
    }

    Vector4& Vector4::operator=(const Vector4& other) {
        _vec[Axis::x] = other[Axis::x];
        _vec[Axis::y] = other[Axis::y];
        _vec[Axis::z] = other[Axis::z];
        _vec[Axis::w] = other[Axis::w];
        return *this;
    }

    Vector4& Vector4::operator+=(const Vector4& other) {
        _vec[Axis::x] += other[Axis::x];
        _vec[Axis::y] += other[Axis::y];
        _vec[Axis::z] += other[Axis::z];
        _vec[Axis::w] += other[Axis::w];
        return *this;
    }

    Vector4& Vector4::operator-=(const Vector4& other) {
        _vec[Axis::x] -= other[Axis::x];
        _vec[Axis::y] -= other[Axis::y];
        _vec[Axis::z] -= other[Axis::z];
        _vec[Axis::w] -= other[Axis::w];
        return *this;
    }

    Vector4& Vector4::operator*=(const Float32 scalar) {
        _vec[Axis::x] *= scalar;
        _vec[Axis::y] *= scalar;
        _vec[Axis::z] *= scalar;
        _vec[Axis::w] *= scalar;
        return *this;
    }

    Vector4& Vector4::operator/=(const Float32 scalar) {
        _vec[Axis::x] /= scalar;
        _vec[Axis::y] /= scalar;
        _vec[Axis::z] /= scalar;
        _vec[Axis::w] /= scalar;
        return *this;
    }

    Float32& Vector4::operator[](Int32 index) {
        assert(Axis::x <= index && index <= Axis::w);
        return _vec[index];
    }

    Float32 Vector4::operator[](Int32 index) const {
        assert(Axis::x <= index && index <= Axis::w);
        return _vec[index];
    }

    Vector4::operator Vector2() {
        return Vector2(_vec[Axis::x], _vec[Axis::y]);
    }

    Vector4::operator Vector3() {
        return Vector3(_vec[Axis::x], _vec[Axis::y], _vec[Axis::z]);
    }

    Vector4 operator-(const Vector4& vec) {
        return Vector4(-(vec[Axis::x]), -(vec[Axis::y]), -(vec[Axis::z]), -(vec[Axis::w]));
    }

    Vector4 operator+(const Vector4& lhs, const Vector4& rhs) {
        return Vector4(lhs[Axis::x] + rhs[Axis::x], lhs[Axis::y] + rhs[Axis::y], lhs[Axis::z] + rhs[Axis::z], lhs[Axis::w] + rhs[Axis::w]);
    }

    Vector4 operator-(const Vector4& lhs, const Vector4& rhs) {
        return Vector4(lhs[Axis::x] - rhs[Axis::x], lhs[Axis::y] - rhs[Axis::y], lhs[Axis::z] - rhs[Axis::z], lhs[Axis::w] - rhs[Axis::w]);
    }

    Vector4 operator*(const Vector4& vec, const Float32 scalar) {
        return Vector4(vec[Axis::x] * scalar, vec[Axis::y] * scalar, vec[Axis::z] * scalar, vec[Axis::w] * scalar);
    }

    Vector4 operator*(const Float32 scalar, const Vector4& vec) {
        return vec * scalar;
    }

    /*
    Vector4 operator*(const Matrix4x4& matrix, const Vector4& vec) {
        Vector4 ret_vec;
        for (Uint8 row = 0; row < 4; row++) {
            Float32 val = (matrix[row][Axis::x] * vec[Axis::x]) + (matrix[row][Axis::y] * vec[Axis::y])
                        + (matrix[row][Axis::z] * vec[Axis::z]) + (matrix[row][Axis::w] * vec[Axis::w]);

            switch (row) {
                case 0:
                    ret_vec.set_x(val);
                    break;
                case 1:
                    ret_vec.set_y(val);
                    break;
                case 2:
                    ret_vec.set_z(val);
                    break;
                case 3:
                    ret_vec.set_w(val);
                    break;
                default:
                    break;
            }
        }

        return ret_vec;
    }

    Vector4 operator*(const Vector4& vec, const Matrix4x4& matrix) {
        return matrix.get_transposition() * vec;
    }
    */

    Vector4 operator/(const Vector4& vec, const Float32 scalar) {
        Float32 reciprocal = 1 / scalar;
        return Vector4(vec[Axis::x] * reciprocal, vec[Axis::y] * reciprocal, vec[Axis::z] * reciprocal, vec[Axis::w] * reciprocal);
    }

    bool operator==(const Vector4& lhs, const Vector4& rhs) {
        return lhs[Axis::x] == rhs[Axis::x]
            && lhs[Axis::y] == rhs[Axis::y]
            && lhs[Axis::z] == rhs[Axis::z]
            && lhs[Axis::w] == rhs[Axis::w];
    }

    bool operator!=(const Vector4& lhs, const Vector4& rhs) {
        return !(lhs == rhs);
    }

    void Vector4::normalize() {
        *this *= (1 / get_magnitude());
    }

    Vector4 Vector4::get_normalized() const {
        return *this * (1 / get_magnitude());
    }

    bool Vector4::is_normalized() const {
        return get_magnitude() == 1.0f;
    }

    bool Vector4::has_opposite_direction_to(const Vector4& other) const {
        return get_dot_product(other) < 0;
    }

    bool Vector4::has_same_direction_as(const Vector4& other) const {
        return !(has_opposite_direction_to(other));
    }

    bool Vector4::is_collinear_to(const Vector4& other) const {
        return get_dot_product(other) == get_magnitude() * other.get_magnitude();
    }

    bool Vector4::is_collinear_opposite_to(const Vector4& other) const {
        return get_dot_product(other) == -(get_magnitude() * other.get_magnitude());
    }

    bool Vector4::is_perpendicular_to(const Vector4& other) const {
        return get_dot_product(other) == 0;
    }

    Float32 Vector4::get_magnitude() const {
        return Math::square_root(get_magnitude_squared());
    }

    Float32 Vector4::get_magnitude_squared() const {
        return (_vec[Axis::x] * _vec[Axis::x]) + (_vec[Axis::y] * _vec[Axis::y]);
    }

    Float32 Vector4::get_projection(const Vector4& other) const {
        return (other.is_normalized()) ? get_dot_product(other) : get_dot_product(other.get_normalized());

    }

    Float32 Vector4::get_dot_product(const Vector4& other) const {
        return (_vec[Axis::x] * other[Axis::x]) + (_vec[Axis::y] * other[Axis::y]);
    }

    void Vector4::scalar_multiply(const Float32 scalar) {
        *this *= scalar;
    }

    Vector4 Vector4::get_scalar_product(const Float32 scalar) const {
        return *this * scalar;
    }

    // ---------
    // Matrix3x3
    // ---------

    const Matrix3x3& Matrix3x3::identity2D() {
        static Matrix3x3 identity = Matrix3x3(Vector3(1.0, 0.0f, 0.0f),
                                              Vector3(0.0f, 1.0f, 0.0f),
                                              Vector3(0.0f, 0.0f, 1.0f));
        return identity;
    }

    Matrix3x3 Matrix3x3::get_translation_2D(const Vector2& vec) {
        Matrix3x3 matrix = Matrix3x3(Matrix3x3::identity2D());
        matrix[0][Axis::z] = vec[Axis::x];
        matrix[1][Axis::z] = vec[Axis::y];
        return matrix;
    }

    Matrix3x3 Matrix3x3::get_rotation_2D(const Vector2& center, const Degree angle) {
        Float32 radian = Math::angle_to_radian(angle);
        Float32 c = Math::cosine(radian);
        Float32 s = Math::sine(radian);

        return Matrix3x3(Vector3(c, -s, center[Axis::x] * (1.0f - c) + center[Axis::y] * s),
                         Vector3(s, c, center[Axis::y] * (1.0f - c) - center[Axis::x] * s),
                         Vector3(0.0f, 0.0f, 1.0f));
    }

    Matrix3x3 Matrix3x3::get_scaling_2D(const Vector2& vec) {
        return Matrix3x3(Vector3(vec[Axis::x], 0.0f, 0.0f),
                         Vector3(0.0f, vec[Axis::y], 0.0f),
                         Vector3(0.0f, 0.0f, 1.0f));
    }

    Matrix3x3::Matrix3x3() {
        _matrix[0] = Vector3();
        _matrix[1] = Vector3();
        _matrix[2] = Vector3();
    }

    Matrix3x3::Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2) {
        _matrix[0] = v0;
        _matrix[1] = v1;
        _matrix[2] = v2;
    }

    Matrix3x3::Matrix3x3(const Float32 val) {
        _matrix[0] = Vector3(val);
        _matrix[1] = Vector3(val);
        _matrix[2] = Vector3(val);
    }

    Matrix3x3::Matrix3x3(const Matrix3x3& other) {
        _matrix[0] = other[0];
        _matrix[1] = other[1];
        _matrix[2] = other[2];
    }

    Matrix3x3& Matrix3x3::operator=(const Matrix3x3& other) {
        _matrix[0] = other[0];
        _matrix[1] = other[1];
        _matrix[2] = other[2];
        return *this;
    }

    Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
        _matrix[0] += other[0];
        _matrix[1] += other[1];
        _matrix[2] += other[2];
        return *this;
    }

    Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
        _matrix[0] -= other[0];
        _matrix[1] -= other[1];
        _matrix[2] -= other[2];
        return *this;
    }

    Matrix3x3& Matrix3x3::operator*=(const Float32 scalar) {
        _matrix[0] *= scalar;
        _matrix[1] *= scalar;
        _matrix[2] *= scalar;
        return *this;
    }

    Matrix3x3& Matrix3x3::operator/=(const Float32 scalar) {
        _matrix[0] /= scalar;
        _matrix[1] /= scalar;
        _matrix[2] /= scalar;
        return *this;
    }

    Vector3& Matrix3x3::operator[](Int32 index) {
        assert(0 <= index && index < 3);
        return _matrix[index];
    }

    Vector3 Matrix3x3::operator[](Int32 index) const {
        assert(0 <= index && index < 3);
        return _matrix[index];
    }

    Matrix3x3 operator-(const Matrix3x3& matrix) {
        return Matrix3x3(-matrix[0], -matrix[1], -matrix[2]);
    }

    Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs) {
        return Matrix3x3(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
    }

    Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs) {
        return Matrix3x3(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]);
    }

    Matrix3x3 operator/(const Matrix3x3& matrix, const Float32 scalar) {
        return Matrix3x3(matrix[0] / scalar, matrix[1] / scalar, matrix[2] / scalar);
    }

    Matrix3x3 operator*(const Matrix3x3& matrix, const Float32 scalar) {
        return Matrix3x3(matrix[0] * scalar, matrix[1] * scalar, matrix[2] * scalar);
    }

    Matrix3x3 operator*(const Float32 scalar, const Matrix3x3& matrix) {
        return matrix * scalar;
    }

    Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs) {
        Matrix3x3 matrix;
        for (Int32 row = 0; row < 3; row++) {
            for (Int32 col = 0; col < 3; col++) {

                matrix[row][col] = lhs[row][0] * rhs[0][col] 
                                 + lhs[row][1] * rhs[1][col] 
                                 + lhs[row][2] * rhs[2][col];
            }
        }

        return matrix;
    }

    bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs) {
        return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
    }

    bool operator!=(const Matrix3x3& lhs, const Matrix3x3& rhs) {
        return !(lhs == rhs);
    }

    Vector2 Matrix3x3::get_linear_transform(const Vector2& vec) const {
        return Vector2();
    }

    Vector3 Matrix3x3::get_linear_transform(const Vector3& vec) const {
        return Vector3();
    }

    void Matrix3x3::transpose() {
        *this = this->get_transposition();
    }

    Matrix3x3 Matrix3x3::get_transposition() const {
        return Matrix3x3(Vector3(_matrix[0][0], _matrix[1][0], _matrix[2][0]),
                         Vector3(_matrix[0][1], _matrix[1][1], _matrix[2][1]),
                         Vector3(_matrix[0][2], _matrix[1][2], _matrix[2][2]));
    }

    void Matrix3x3::inverse() {
        *this = this->get_inverse();
    }

    Matrix3x3 Matrix3x3::get_inverse() const {
        // This function uses Gauss-Jordan elimination with partial pivoting
        // to inverse the function which I know absolutely nothing about.
        // In short, I have no idea what is going on here...
        // @TODO: Learn about what's going on in this function.
        Matrix3x3 mat1(*this);
        Matrix3x3 mat2(identity2D());
        Int32 j;
        Int32 i;
        Int32 k;

        for (j = 0; j < 3; j++) {
            k = j;
            for (i = j + 1; i < 3; i++) {
                if (Math::absolute_value(mat1[i][j] > Math::absolute_value(mat1[k][j]))) {
                    k = i;
                }
            }
        }

        Vector3 temp = mat1[k];
        mat1[k] = mat1[j];
        mat1[j] = temp;

        temp = mat2[k];
        mat2[k] = mat2[j];
        mat2[j] = temp;

        mat2[j] /= mat1[j][j];
        mat1[j] /= mat1[j][j];

        for (i = 0; i < 3; i++) {
            if (i != j) {
                mat2[i] -= mat1[i][j] * mat2[j];
                mat1[i] -= mat1[i][j] * mat1[j];
            }
        }

        return mat2;
    }

    void Matrix3x3::translate(const Vector2& vec) {
        *this = Matrix3x3::get_translation_2D(vec);
    }

    void Matrix3x3::rotate(const Vector2& center, const Degree angle) {
        *this = Matrix3x3::get_rotation_2D(center, angle);
    }

    void Matrix3x3::scale(const Vector2& vec) {
        *this = Matrix3x3::get_scaling_2D(vec);
    }

    // ---------
    // Matrix4x4
    // ---------

    const Matrix4x4 Matrix4x4::identity3D() {
        Matrix4x4 identity =  Matrix4x4(Vector4(1.0f, 0.0f, 0.0f, 0.0f),
                                        Vector4(0.0f, 1.0f, 0.0f, 0.0f),
                                        Vector4(0.0f, 0.0f, 1.0f, 0.0f),
                                        Vector4(0.0f, 0.0f, 0.0f, 1.0f));
        return identity;
    }

    Matrix4x4 Matrix4x4::get_translation_3D(const Vector3& vec) {
        Matrix4x4 matrix(Matrix4x4::identity3D());
        matrix[0][Axis::w] = vec[Axis::x];
        matrix[1][Axis::w] = vec[Axis::y];
        matrix[2][Axis::w] = vec[Axis::z];
        return matrix;
    }

    Matrix4x4 Matrix4x4::get_rotation_3D(const Vector3& axis, const Degree angle) {
        Float32 radian = Math::angle_to_radian(angle);
        Float32 c = Math::cosine(radian);
        Float32 s = Math::sine(radian);
        Float32 t = 1.0f - c;

        Vector3 norm_axis = axis.get_normalized();

        Matrix4x4 matrix = Matrix4x4::identity3D();

        matrix[0][0] = t * norm_axis[Axis::x] * norm_axis[Axis::x] + c;
        matrix[0][1] = t * norm_axis[Axis::x] * norm_axis[Axis::y] - s * norm_axis[Axis::z];
        matrix[0][2] = t * norm_axis[Axis::x] * norm_axis[Axis::z] + s * norm_axis[Axis::y];

        matrix[1][0] = t * norm_axis[Axis::x] * norm_axis[Axis::y] + s * norm_axis[Axis::z];
        matrix[1][1] = t * norm_axis[Axis::y] * norm_axis[Axis::y] + c;
        matrix[1][2] = t * norm_axis[Axis::y] * norm_axis[Axis::z] - s * norm_axis[Axis::x];

        matrix[2][0] = t * norm_axis[Axis::x] * norm_axis[Axis::z] - s * norm_axis[Axis::y];
        matrix[2][1] = t * norm_axis[Axis::y] * norm_axis[Axis::z] + s * norm_axis[Axis::x];
        matrix[2][2] = t * norm_axis[Axis::z] * norm_axis[Axis::z] + c;

        return matrix;
    }

    Matrix4x4 Matrix4x4::get_scaling_3D(const Vector3& vec) {
        return Matrix4x4(Vector4(vec[Axis::x], 0.0f, 0.0f, 0.0f),
                         Vector4(0.0f, vec[Axis::y], 0.0f, 0.0f),
                         Vector4(0.0f, 0.0f, vec[Axis::z], 0.0f),
                         Vector4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    Matrix4x4 Matrix4x4::get_perspective_3D(const Float32 val) {
        Matrix4x4 matrix = Matrix4x4::identity3D();
        matrix[3][2] = 1.0f / val;
        matrix[3][3] = 0.0f;
        return matrix;
    }

    Matrix4x4::Matrix4x4() {
        _matrix[0] = Vector4();
        _matrix[1] = Vector4();
        _matrix[2] = Vector4();
        _matrix[3] = Vector4();
    }

    Matrix4x4::Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3) {
        _matrix[0] = v0;
        _matrix[1] = v1;
        _matrix[2] = v2;
        _matrix[3] = v3;
    }

    Matrix4x4::Matrix4x4(const Float32 val) {
        _matrix[0] = Vector4(val);
        _matrix[1] = Vector4(val);
        _matrix[2] = Vector4(val);
        _matrix[3] = Vector4(val);
    }

    Matrix4x4::Matrix4x4(const Matrix4x4& other) {
        _matrix[0] = other[0];
        _matrix[1] = other[1];
        _matrix[2] = other[2];
        _matrix[3] = other[3];
    }

    Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) {
        _matrix[0] = other[0];
        _matrix[1] = other[1];
        _matrix[2] = other[2];
        _matrix[3] = other[3];
        return *this;
    }

    Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
        _matrix[0] += other[0];
        _matrix[1] += other[1];
        _matrix[2] += other[2];
        _matrix[3] += other[3];
        return *this;
    }

    Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {
        _matrix[0] -= other[0];
        _matrix[1] -= other[1];
        _matrix[2] -= other[2];
        _matrix[3] -= other[3];
        return *this;
    }

    Matrix4x4& Matrix4x4::operator*=(const Float32 scalar) {
        _matrix[0] *= scalar;
        _matrix[1] *= scalar;
        _matrix[2] *= scalar;
        _matrix[3] *= scalar;
        return *this;
    }

    Matrix4x4& Matrix4x4::operator/=(const Float32 scalar) {
        _matrix[0] /= scalar;
        _matrix[1] /= scalar;
        _matrix[2] /= scalar;
        _matrix[3] /= scalar;
        return *this;
    }

    Vector4& Matrix4x4::operator[](Int32 index) {
        assert(0 <= index && index < 4);
        return _matrix[index];
    }

    Vector4 Matrix4x4::operator[](Int32 index) const {
        assert(0 <= index && index < 4);
        return _matrix[index];
    }

    Matrix4x4 operator-(const Matrix4x4& matrix) {
        return Matrix4x4(-matrix[0], -matrix[1], -matrix[2], -matrix[3]);
    }

    Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs) {
        return Matrix4x4(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3]);
    }

    Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs) {
        return Matrix4x4(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3]);
    }

    Matrix4x4 operator*(const Matrix4x4& matrix, const Float32 scalar) {
        return Matrix4x4(matrix[0] * scalar, matrix[1] * scalar, matrix[2] * scalar, matrix[3] * scalar);
    }

    Matrix4x4 operator*(const Float32 scalar, const Matrix4x4& matrix) {
        return matrix * scalar;
    }

    Matrix4x4 operator*(const Matrix4x4& rhs, const Matrix4x4& lhs) {
        Matrix4x4 matrix;

        for (Int32 row = 0; row < 4; row++) {
            for (Int32 col = 0; col < 4; col++) {
                matrix[row][col] = lhs[row][0] * rhs[0][col]
                                 + lhs[row][1] * rhs[1][col]
                                 + lhs[row][2] * rhs[2][col]
                                 + lhs[row][3] * rhs[3][col];
            }
        }

        return matrix;
    }

    Matrix4x4 operator/(const Matrix4x4& matrix, const Float32 scalar) {
        return Matrix4x4(matrix[0] / scalar, matrix[1] / scalar, matrix[2] / scalar, matrix[3] / scalar);
    }

    bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) {
        return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] && lhs[3] == rhs[3];
    }

    bool operator!=(const Matrix4x4& lhs, const Matrix4x4& rhs) {
        return !(lhs == rhs);
    }

    Vector3 Matrix4x4::get_linear_transform(const Vector3& vec) const {
        return Vector3();
    }

    Vector4 Matrix4x4::get_linear_transform(const Vector4& vec) const {
        return Vector4();
    }

    void Matrix4x4::transpose() {
        *this = this->get_transposition();
    }

    Matrix4x4 Matrix4x4::get_transposition() const {
        return Matrix4x4(Vector4(_matrix[0][0], _matrix[1][0], _matrix[2][0], _matrix[3][0]),
                         Vector4(_matrix[0][1], _matrix[1][1], _matrix[2][1], _matrix[3][1]),
                         Vector4(_matrix[0][2], _matrix[1][2], _matrix[2][2], _matrix[3][2]),
                         Vector4(_matrix[0][3], _matrix[1][3], _matrix[2][3], _matrix[3][3]));
    }

    void Matrix4x4::inverse() {
        *this = this->get_inverse();
    }

    Matrix4x4 Matrix4x4::get_inverse() const {
        // @TODO: See note in Matrix3x3::get_inverse()
        Matrix4x4 mat1(*this);
        Matrix4x4 mat2(Matrix4x4::identity3D());
        Int32 i;
        Int32 j;
        Int32 k;

        for (j = 0; j < 4; j++) {
            k = j;
            for (i = j + 1; i < 4; i++) {
                if (Math::absolute_value(mat1[i][j]) > Math::absolute_value(mat1[k][j])) {
                    k = i;
                }
            }
        }

        Vector4 temp = mat1[k];
        mat1[k] = mat1[j];
        mat1[j] = temp;

        temp = mat2[k];
        mat2[k] = mat2[j];
        mat2[j] = temp;

        mat2[j] /= mat1[j][j];
        mat1[j] /= mat1[j][j];

        for (i = 0; i < 4; i++) {
            if (i != j) {
                mat2[i] -= mat1[i][j] * mat2[j];
                mat1[i] -= mat1[i][j] * mat1[j];
            }
        }

        return mat2;
    }

    void Matrix4x4::translate(const Vector3& vec) {
        *this = Matrix4x4::get_translation_3D(vec);
    }

    void Matrix4x4::rotate(const Vector3& axis, const Degree angle) {
        *this = Matrix4x4::get_rotation_3D(axis, angle);
    }

    void Matrix4x4::scale(const Vector3& vec) {
        *this = Matrix4x4::get_scaling_3D(vec);
    }
}