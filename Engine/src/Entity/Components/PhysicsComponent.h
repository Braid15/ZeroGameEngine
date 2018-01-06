#pragma once

#include "../../ZeroEngineStd.h"
#include "../EntityComponent.h"
#include "../../Math/MathTypes.h"
#include "../../Utils/Xml/XmlReader.h"
#include "../../Utils/Xml/XmlWriter.h"
#include "../../Physics/IPhysics.h"

namespace ZeroEngine {

    class PhysicsComponent : public EntityComponent {
    private:
        Vector3 _rigid_body_location;
        Vector3 _rigid_body_orientation;
        Vector3 _rigid_body_scale;
        Float32 _acceleration;
        Float32 _angular_acceleration;
        Float32 _max_velocity;
        Float32 _max_angular_velocity;

        std::shared_ptr<IPhysics> _game_physics;

    public:
        PhysicsComponent();
        ~PhysicsComponent();

        static const EntityComponentId id;
        static const char* name;

        static EntityComponent* create();

        bool initialize(const XmlReader&) override;
        void post_initialize() override;
        void update(Tick delta_time) override;

        inline const char* get_name() const override { return name; }
        inline StringRepr to_string() const { return "PhysicsComponent"; }
        inline const EntityComponentId& get_id() const override { return id; }

        void apply_force(const Vector3& direction, const Float32 newtons);
        void apply_torque(const Vector3& direction, const Float32 newtons);

        // @TODO: Should be using matrix
        bool kinematic_move(const Vector2& pos);
        bool kinematic_move(const Vector3& pos);

        void apply_acceleration(const Float32 acceleration);
        void remove_acceleration();
        void apply_angular_acceleration(const Float32 acceleration);
        void remove_angular_acceleration();

        // Should be using matrix
        // Vector3 get_velocity() const;
        // void set_velocity(const Vector3& vel);

        void set_position(const Vector2& pos);
        void set_position(const Vector3& pos);

        void stop();

    private:
        void on_write_xml(const XmlWriter& writer) override;





        // @TODO:  
        // shape
        // density
        // material
    };

}