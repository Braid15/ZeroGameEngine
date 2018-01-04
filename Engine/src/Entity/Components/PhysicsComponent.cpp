#include "PhysicsComponent.h"
#include "../../Utils/Hash.h"
#include "../../Utils/StringId.h"
#include "../../AppLayer/Game.h"

namespace ZeroEngine {

    const char* PhysicsComponent::name = "PhysicsComponent";
    const EntityComponentId PhysicsComponent::id = STRING_ID("PhysicsComponent");

    // These constants are the ones used in GameCodeingComplete
    static const Float32 DEFAULT_MAX_VELOCITY = 7.2f;
    static const Float32 DEFAULT_MAX_ANGULAR_VELOCITY = 1.2f; 

    EntityComponent* PhysicsComponent::create() {
        LOG_UNIMPLEMENTED();
        return nullptr;
    }

    PhysicsComponent::PhysicsComponent() {
        // set vector3's
        _acceleration = 0.0f;
        _angular_acceleration = 0.0f;
        _max_velocity = DEFAULT_MAX_VELOCITY;
        _max_angular_velocity = DEFAULT_MAX_ANGULAR_VELOCITY;
        LOG_UNIMPLEMENTED();
    }

    PhysicsComponent::~PhysicsComponent() {
        _game_physics->remove_entity(get_owner()->get_id());
    }

    bool PhysicsComponent::initialize(const XmlReader& reader) {
        _game_physics = Game::get_physics();
        assert(_game_physics);
        LOG_UNIMPLEMENTED();
        return true;
    }

    void PhysicsComponent::post_initialize() {
        LOG_UNIMPLEMENTED();
        // _game_physics->add_shape(whatever this shape is)
    }

    void PhysicsComponent::update(Tick delta_time) {
        LOG_UNIMPLEMENTED();
    }

    void PhysicsComponent::apply_force(const Vector3& direction, const Float32 newtons) {
        _game_physics->apply_force(direction, newtons, get_owner()->get_id());
    }

    void PhysicsComponent::apply_torque(const Vector3& direction, const Float32 newtons) {
        _game_physics->apply_torque(direction, newtons, get_owner()->get_id());
    }

    bool PhysicsComponent::kinematic_move(const Vector2& pos) {
        return _game_physics->kinematic_move(pos, get_owner()->get_id());
    }

    bool PhysicsComponent::kinematic_move(const Vector3& pos) {
        return _game_physics->kinematic_move(pos, get_owner()->get_id());
    }

    void PhysicsComponent::apply_acceleration(const Float32 acceleration) {
        _acceleration = acceleration;
    }

    void PhysicsComponent::remove_acceleration() {
        _acceleration = 0.0f;
    }

    void PhysicsComponent::apply_angular_acceleration(const Float32 acceleration) {
        _angular_acceleration = acceleration;
    }

    void PhysicsComponent::remove_angular_acceleration() {
        _angular_acceleration = 0.0f;
    }

    void PhysicsComponent::set_position(const Vector2& pos) {
        // set owner transofrm then call kinematic_move
    }

    void PhysicsComponent::set_position(const Vector3& pos) {
        // set owner transofrm then call kinematic_move
    }

    void PhysicsComponent::stop() {
        _game_physics->stop_entity(get_owner()->get_id()); 
    }

    void PhysicsComponent::on_write_xml(const XmlWriter& writer) {

    }
}