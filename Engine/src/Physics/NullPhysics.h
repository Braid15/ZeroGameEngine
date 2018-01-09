#pragma once

#include "../ZeroEngineStd.h"
#include "IPhysics.h"
#include "../Math/MathTypes.h"

namespace ZeroEngine {

    class Vector2;
    class Vector3;
    class Vector4;

    class NullPhysics final : public IPhysics {
    public:
        ~NullPhysics() {}
        inline bool initialize() override { return true; }
        inline void on_update(Tick delta_time) override {}
        inline void sync_visible_scene() override {}
        inline void render_diagnostics() override {}
        inline void remove_entity(EntityId) override {}
        inline void apply_force(const Vector3&, Float32, EntityId) override {}
        inline void apply_torque(const Vector3&, Float32, EntityId) override {}
        inline bool kinematic_move(const Matrix3x3&, EntityId) override { return false; }
        inline bool kinematic_move(const Matrix4x4&, EntityId) override { return false; }
        inline Vector3 get_velocity(EntityId) override { return Vector3(); }
        inline void set_velocity(const Vector3&, EntityId) override {}
        inline void stop_entity(EntityId) override {}
        inline void set_world_transform(const Matrix3x3&, EntityId) override {}
        inline void set_world_transform(const Matrix4x4&, EntityId) override {}
        inline void add_entity(const EntityId& id) {}
        inline StringRepr to_string() const override { return "NullPhysics"; }
    };
}