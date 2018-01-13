#pragma once

#include "../ZeroEngineStd.h"
#include "../Math/MathTypes.h"
#include "../Entity/EntityId.h"

namespace ZeroEngine {

    class IPhysics;

    class IRigidBody {
    public:
        virtual ~IRigidBody() {}

        virtual void set_position(const Vector3&) = 0;
        virtual Vector3& get_position() const = 0;

        virtual void set_orientation(const Vector3&) = 0;
        virtual Vector3& set_orientation() const = 0;

        virtual void set_scale(const Vector3&) = 0;
        virtual Vector3& get_scale() const = 0;

        virtual void set_velocity(const Vector3&) = 0;
        virtual Vector3& get_velocity() const = 0;

        virtual void set_direction(const Vector3&) = 0;
        virtual Vector3& get_direction() const = 0;

        virtual void set_acceleration(const Float32) = 0;
        virtual Float32 get_acceleration() const = 0;

        virtual void set_angular_acceleration(const Float32) = 0;
        virtual Float32 get_angular_acceleration() const = 0;

        virtual void set_max_scalar_velocity(const Float32) = 0;
        virtual Float32 get_max_scalar_velocity() const = 0;

        virtual void set_max_angular_scalar_velocity(const Float32) = 0;
        virtual Float32 get_max_angular_scalar_velocity() const = 0;

        virtual EntityId get_owner_id() const = 0;

    };

    class BaseRigidBody : public IRigidBody {
    protected:
        EntityId _owner_id;
        Vector3 _position;
        Vector3 _orientation;
        Vector3 _scale;
        Vector3 _velocity;
        Float32 _acceleration;
        Float32 _angular_acceleration;
        Float32 _max_velocity;
        Float32 _max_angular_velocity;

        std::shared_ptr<IPhysics> _game_physics;


    public:

    };
}