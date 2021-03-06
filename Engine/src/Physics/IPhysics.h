#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Entity/EntityId.h"

namespace ZeroEngine {

    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix3x3;
    class Matrix4x4;
    class IRigidBody;

    // @TODO: This interface should be using a matrix where there
    // needs to be overloads for different vector types.

    class IPhysics : public virtual IZeroObject {
    public:
        virtual bool initialize() = 0;
        virtual void on_update(Tick delta_time) = 0;
        virtual void sync_visible_scene() = 0;
        virtual void render_diagnostics() = 0;
        virtual void remove_entity(EntityId) = 0;
        virtual void apply_force(const Vector3& direction, Float32 newtons, EntityId id) = 0;
        virtual void apply_torque(const Vector3& direction, Float32 newtons, EntityId id) = 0;
        virtual void add_entity(const EntityId& id) = 0;

        // @TODO: Should be using matrix
        virtual bool kinematic_move(const Matrix3x3& pos, EntityId id) = 0;
        virtual bool kinematic_move(const Matrix4x4& pos, EntityId id) = 0;

        virtual Vector3 get_velocity(EntityId id) = 0;
        virtual void set_velocity(const Vector3& vel, EntityId id) = 0;

        virtual void stop_entity(EntityId id) = 0;

        virtual void set_world_transform(const Matrix3x3& transform, EntityId id) = 0;
        virtual void set_world_transform(const Matrix4x4& transform, EntityId id) = 0;

        // get_transform()



        // rotate_y()
        // get_y_orientation()
        // translate()
        // get/set angular_velocity()
        // add_spere()
        // add_box()
        // add_point_cloud()
        // create_trigger()

        virtual StringRepr to_string() const = 0;
        virtual ~IPhysics() {}
    };
}