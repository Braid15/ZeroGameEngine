#include "Vector2.h"

namespace ZeroEngine {

    // ----------------------
    // Vector2 Static Members
    // ----------------------

    const Vector2 Vector2::zero = Vector2(0.0, 0.0);
    const Vector2 Vector2::unit_i = Vector2(1.0, 0.0);
    const Vector2 Vector2::unit_j = Vector2(0.0, 1.0);

    Vector2 Vector2::add(const Vector2& v1, const Vector2& v2) {
        return v1 + v2;
    }

    Vector2 Vector2::add(const Vector2* v1, const Vector2* v2) {
        return *v1 + *v2;
    }

    Vector2 Vector2::add(const Vector2& v1, const Vector2* v2) {
        return v1 + *v2;
    }

    Vector2 Vector2::add(const Vector2* v1, const Vector2& v2) {
        return *v1 + v2;
    }

    Vector2 Vector2::subtract(const Vector2& v1, const Vector2& v2) {
        return v1 - v2;
    }

    Vector2 Vector2::subtract(const Vector2* v1, const Vector2* v2) {
        return *v1 - *v2;
    }

    Vector2 Vector2::subtract(const Vector2& v1, const Vector2* v2) {
        return v1 - *v2;
    }

    Vector2 Vector2::subtract(const Vector2* v1, const Vector2& v2) {
        return *v1 - v2;
    }

    Vector2 Vector2::scalar_multiply(const Vector2& v, const float_t& scalar) {
        return v * scalar;
    }

    Vector2 Vector2::scalar_multiply(const Vector2* v, const float_t& scalar) {
        return *v * scalar;
    }

    Vector2 Vector2::normalize(const Vector2& v) {
        float_t magnitude = v.get_magnitude();
        float_t reciprocal = 1 / magnitude;
        return Vector2(v.get_x() * reciprocal, v.get_y() * reciprocal);
    }

    Vector2 Vector2::normalize(const Vector2* v) {
        float_t magnitude = v->get_magnitude();
        float_t reciprocal = 1 / magnitude;
        return Vector2(v->get_x() * reciprocal, v->get_y() * reciprocal);
    }

    Vector2 Vector2::euler_integrate(const Vector2& cur_pos, const Vector2& cur_vel, const float_t& delta) {
        return cur_pos + (cur_vel * delta);
    }

    Vector2 Vector2::euler_integrate(const Vector2* cur_pos, const Vector2* cur_vel, const float_t& delta) {
        return *cur_pos + (*cur_vel * delta);
    }

    Vector2 Vector2::euler_integrate(const Vector2* cur_pos, const Vector2& cur_vel, const float_t& delta) {
        return *cur_pos + (cur_vel * delta);
    }

    Vector2 Vector2::euler_integrate(const Vector2& cur_pos, const Vector2* cur_vel, const float_t& delta) {
        return cur_pos + (*cur_vel * delta);
    }

    float_t Vector2::dot_product(const Vector2& v1, const Vector2& v2) {
        return (v1.get_x() * v2.get_x()) + (v1.get_y() * v2.get_y());
    }

    float_t Vector2::dot_product(const Vector2* v1, const Vector2* v2) {
        return (v1->get_x() * v2->get_x()) + (v1->get_y() * v2->get_y());
    }

    float_t Vector2::dot_product(const Vector2& v1, const Vector2* v2) {
        return (v1.get_x() * v2->get_x()) + (v1.get_y() * v2->get_y());
    }

    float_t Vector2::dot_product(const Vector2* v1, const Vector2& v2) {
        return (v1->get_x() * v2.get_x()) + (v1->get_y() * v2.get_y());
    }

    bool Vector2::opposite_directions(const Vector2& v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) < 0;
    }

    bool Vector2::opposite_directions(const Vector2* v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) < 0;
    }

    bool Vector2::opposite_directions(const Vector2& v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) < 0;
    }

    bool Vector2::opposite_directions(const Vector2* v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) < 0;
    }

    bool Vector2::are_collinear(const Vector2& v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) == v1.get_magnitude() * v2.get_magnitude();
    }

    bool Vector2::are_collinear(const Vector2* v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) == v1->get_magnitude() * v2->get_magnitude();
    }

    bool Vector2::are_collinear(const Vector2& v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) == v1.get_magnitude() * v2->get_magnitude();
    }

    bool Vector2::are_collinear(const Vector2* v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) == v1->get_magnitude() * v2.get_magnitude();
    }

    bool Vector2::are_collinear_opposites(const Vector2& v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) == -(v1.get_magnitude() * v2.get_magnitude());
    }

    bool Vector2::are_collinear_opposites(const Vector2* v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) == -(v1->get_magnitude() * v2->get_magnitude());
    }

    bool Vector2::are_collinear_opposites(const Vector2& v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) == -(v1.get_magnitude() * v2->get_magnitude());
    }

    bool Vector2::are_collinear_opposites(const Vector2* v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) == -(v1->get_magnitude() * v2.get_magnitude());
    }

    bool Vector2::are_perpendicular(const Vector2& v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) == 0;
    }

    bool Vector2::are_perpendicular(const Vector2* v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) == 0;
    }

    bool Vector2::are_perpendicular(const Vector2& v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) == 0;
    }

    bool Vector2::are_perpendicular(const Vector2* v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) == 0;
    }

    bool Vector2::same_directions(const Vector2& v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) > 0;
    }

    bool Vector2::same_directions(const Vector2* v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) > 0;
    }

    bool Vector2::same_directions(const Vector2& v1, const Vector2* v2) {
        return Vector2::dot_product(v1, v2) > 0;
    }

    bool Vector2::same_directions(const Vector2* v1, const Vector2& v2) {
        return Vector2::dot_product(v1, v2) > 0;
    }   

    // ----------------------
    // Vector2 Public Members
    // ----------------------

    // @TODO: Flag to keep track if x or y has changed so that we can cache magnitude
    // instead of calculating it every call?
    // @TODO: Test performance between the two ways to get the magnitude
    float_t Vector2::get_magnitude() const {
        // return Math::absolute_value(Math::square_root(Math::square(_x) + Math::square(_y)));
        return Math::square_root(Vector2::dot_product(this, this));
    }

    void Vector2::normalize() {
        float_t magnitude = get_magnitude();
        float_t reciprocal = 1 / magnitude;
        _x *= reciprocal;
        _y *= reciprocal;
    }

    float_t Vector2::get_projection(const Vector2& other) {
        if (other.is_unit_vector()) {
            return Vector2::dot_product(this, other);
        } else {
            return Vector2::dot_product(this, Vector2::normalize(other));
        }
    }

    float_t Vector2::get_projection(const Vector2* other) {
        if (other->is_unit_vector()) {
            return Vector2::dot_product(this, other);
        } else {
            return Vector2::dot_product(this, Vector2::normalize(other));
        }
    }

    bool Vector2::has_opposite_direction_as(const Vector2& other) {
        return Vector2::opposite_directions(this, other);
    }

    bool Vector2::has_opposite_direction_as(const Vector2* other) {
        return Vector2::opposite_directions(this, other);
    }

    bool Vector2::is_collinear_to(const Vector2& other) {
        // hanlde unit vectors
        return Vector2::are_collinear(this, other);
    }

    bool Vector2::is_collinear_to(const Vector2* other) {
        return Vector2::are_collinear(this, other);
    }

    bool Vector2::is_collinear_opposite_to(const Vector2& other) {
        // handle unit vectors
        return Vector2::are_collinear_opposites(this, other);
    }

    bool Vector2::is_collinear_opposite_to(const Vector2* other) {
        return Vector2::are_collinear_opposites(this, other);
    }

    bool Vector2::is_perpendicular_to(const Vector2& other) {
        return Vector2::are_perpendicular(this, other);
    }

    bool Vector2::is_perpendicular_to(const Vector2* other) {
        return Vector2::are_perpendicular(this, other);
    }

    bool Vector2::has_same_direction_as(const Vector2& other) {
        return Vector2::same_directions(this, other);
    }

    bool Vector2::has_same_direction_as(const Vector2* other) {
        return Vector2::same_directions(this, other);
    }

    float_t Vector2::get_dot_product(const Vector2& other) {
        return Vector2::dot_product(this, other);
    }

    float_t Vector2::get_dot_product(const Vector2* other) {
        return Vector2::dot_product(this, other);
    }

    void Vector2::project_onto(const Vector2& other) {
        LOG_UNIMPLEMENTED();
    }

    void Vector2::project_onto(const Vector2* other) {
        LOG_UNIMPLEMENTED();
    }

    std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
        os << "Vector2: (" << vector.get_x() << ", " << vector.get_y() << ")";
        return os;
    }
}