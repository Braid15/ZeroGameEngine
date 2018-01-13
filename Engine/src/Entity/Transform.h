#pragma once

#include "../ZeroEngineStd.h"
#include "../Math/MathTypes.h"
#include "../Logger/Logging.h"

namespace ZeroEngine {

    class Transform {
    private:
        Vector3 _position;
        Vector3 _rotation;
        Vector3 _scale;
    public:
        Transform() : 
            _position(0, 0, 1), _rotation(0), _scale(1) {}
        virtual ~Transform() {}

        Transform(const Transform& other) {
            _position = other._position;
            _rotation = other._rotation;
            _scale = other._scale;
        }

        Transform& operator=(const Transform&other) {
            _position = other._position;
            _rotation = other._rotation;
            _scale = other._scale;
            return *this;
        }

        inline const Vector3& get_direction() const;

        inline const Vector3& get_position() const { return _position; }
        inline void set_position(const Vector3& pos) { _position = pos; }

        inline void set_position(const Matrix3x3& pos) { LOG_UNIMPLEMENTED(); }

        inline void set_position(const Vector2& pos) { 
            _position[0] = pos[0];
            _position[1] = pos[1];
        }

        inline const Vector3& get_rotation() const { return _rotation; }
        inline void set_rotation(const Degree degree) { _rotation.set(_position[0], _position[1], degree); }
        inline void set_rotation(const Vector3& rotation) { _rotation.set(rotation); }
        inline void set_rotation(const Vector2& center, const Degree degrees) { 
            _rotation[0] = center[0]; 
            _rotation[1] = center[1];
            _rotation[2] = degrees;
        }

        inline const Vector3& get_scale() const { return _scale; }
        inline void set_scale(const Float32 scale) { _scale.set(scale); }
        inline void set_scale(const Vector3& scale) { _scale.set(scale); }
        inline void set_scale(const Vector2& scale) { 
            _scale[0] = scale[0];
            _scale[1] = scale[1];
        }

        inline const Matrix3x3& get_world_transform() const { 
            Matrix3x3 transform = Matrix3x3::identity();

            LOG_TODO("Transform", "FIX!!");

            transform = transform * Matrix3x3::get_scaling_2D(_scale);
            transform = transform * Matrix3x3::get_rotation_2D(Vector2(_rotation), _rotation[Axis::z]);
            transform = transform * Matrix3x3::get_translation_2D(_position);

            return transform;
        }

        inline void set_world_transform(const Matrix3x3& mat) { 
        }

        Transform get_inverse() const { LOG_UNIMPLEMENTED(); return Transform(); }
    };

    inline const Vector3& Transform::get_direction() const {
        LOG_UNIMPLEMENTED();
        return Vector3();
    }
}