#include "PhysicsComponent.h"
#include "../../Utils/Hash.h"
#include "../../Utils/StringId.h"
#include "../../AppLayer/Game.h"
#include "../../Logger/Logging.h"
#include "../Transform.h"

namespace ZeroEngine {

    const char* RigidBodyComponent::name = "PhysicsComponent";
    const EntityComponentId RigidBodyComponent::id = STRING_ID("PhysicsComponent");

    // These constants are the ones used in GameCodeingComplete
    static const Float32 DEFAULT_MAX_VELOCITY = 7.2f;
    static const Float32 DEFAULT_MAX_ANGULAR_VELOCITY = 1.2f; 

    EntityComponent* RigidBodyComponent::create() {
        LOG_UNIMPLEMENTED();
        return nullptr;
    }

    RigidBodyComponent::RigidBodyComponent() {
        _location = Vector3(0);
        _orientation = Vector3(0);
        _scale = Vector3(1);
        _velocity = Vector3(0);
        _acceleration = 0.0f;
        _angular_acceleration = 0.0f;
        _max_velocity = DEFAULT_MAX_VELOCITY;
        _max_angular_velocity = DEFAULT_MAX_ANGULAR_VELOCITY;
    }

    RigidBodyComponent::~RigidBodyComponent() {
        _game_physics->remove_entity(get_owner()->get_id());
    }

    bool RigidBodyComponent::initialize(const XmlReader& reader) {
        _game_physics = Game::get_physics();
        assert(_game_physics);
        LOG_UNIMPLEMENTED();
        return true;
    }

    void RigidBodyComponent::post_initialize() {
        LOG_UNIMPLEMENTED();
        // _game_physics->add_shape(whatever this shape is)
    }

    void RigidBodyComponent::update(Tick delta_time) {
        Transform transform = get_owner()->get_transform();


        if (_acceleration != 0.0f) {
            Float32 acceleration = _acceleration / 1000.0f * delta_time;
            _game_physics->apply_force(_velocity, acceleration, get_owner()->get_id());
        }

        if (_angular_acceleration != 0.0f) {
            Float32 acceleration = _angular_acceleration / 1000.0f * delta_time;
            _game_physics->apply_torque(_velocity, acceleration, get_owner()->get_id());
        }
    }

    void RigidBodyComponent::apply_force(const Vector3& direction, const Float32 newtons) {
        _game_physics->apply_force(direction, newtons, get_owner()->get_id());
    }

    void RigidBodyComponent::apply_torque(const Vector3& direction, const Float32 newtons) {
        _game_physics->apply_torque(direction, newtons, get_owner()->get_id());
    }

    bool RigidBodyComponent::kinematic_move(const Matrix3x3& pos) {
        return _game_physics->kinematic_move(pos, get_owner()->get_id());
    }

    bool RigidBodyComponent::kinematic_move(const Matrix4x4& pos) {
        return _game_physics->kinematic_move(pos, get_owner()->get_id());
    }

    void RigidBodyComponent::apply_acceleration(const Float32 acceleration) {
        _acceleration = acceleration;
    }

    void RigidBodyComponent::remove_acceleration() {
        _acceleration = 0.0f;
    }

    void RigidBodyComponent::apply_angular_acceleration(const Float32 acceleration) {
        _angular_acceleration = acceleration;
    }

    void RigidBodyComponent::remove_angular_acceleration() {
        _angular_acceleration = 0.0f;
    }

    void RigidBodyComponent::set_position(const Vector2& pos) {
        Transform transform = get_owner()->get_transform();
        Matrix3x3 mat = transform.get_world_transform();
        mat[0][Axis::z] = pos[Axis::x];
        mat[1][Axis::z] = pos[Axis::y];

        kinematic_move(mat);
    }

    void RigidBodyComponent::set_position(const Vector3& pos) {
        LOG_UNIMPLEMENTED();
    }

    void RigidBodyComponent::stop() {
        _game_physics->stop_entity(get_owner()->get_id()); 
    }

    void RigidBodyComponent::on_write_xml(const XmlWriter& writer) {

    }
}