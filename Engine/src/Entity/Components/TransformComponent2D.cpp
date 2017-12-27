#include "TransformComponent2D.h"

namespace ZeroEngine {

    const char* TransformComponent2D::name = "TransformComponent2D";

    bool TransformComponent2D::initialize() {
        LOG_UNIMPLEMENTED();
        return true;
    }

    void TransformComponent2D::post_initialize() {
        LOG_UNIMPLEMENTED();
    }

    const EntityComponentId& TransformComponent2D::get_id() const {
        LOG_TODO("TransformComponent2D", "Id needs to be hashed string");
        return _id;
    }

    void TransformComponent2D::on_write_xml(const XmlWriter& writer) {
        writer.write_start_element(name);

        writer.write_start_element("Position");
        writer.write_attribute_string("x", std::to_string(_position.get_x()).c_str());
        writer.write_attribute_string("y", std::to_string(_position.get_y()).c_str());
        writer.write_end_element();

        writer.write_start_element("Velocity");
        writer.write_attribute_string("x", std::to_string(_velocity.get_x()).c_str());
        writer.write_attribute_string("y", std::to_string(_velocity.get_y()).c_str());
        writer.write_end_element();

        writer.write_end_element();
    }

    EntityComponent* TransformComponent2D::create(const XmlReader& reader) {
        assert(strcmp(reader.get_element_name(), name) == 0);

        Vector2 position;
        reader.move_to_element("Position");
        position.set_x(reader.get_element_attribute_value_as_float("x"));
        position.set_y(reader.get_element_attribute_value_as_float("y"));

        Vector2 velocity;
        reader.move_to_element("Velocity");
        velocity.set_x(reader.get_element_attribute_value_as_float("x"));
        velocity.set_y(reader.get_element_attribute_value_as_float("y"));

        TransformComponent2D* transform = zero_new TransformComponent2D();
        transform->set_position(position);
        transform->set_velocity(velocity);
        return transform;
    }
}