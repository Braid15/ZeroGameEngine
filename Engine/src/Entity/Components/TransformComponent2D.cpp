#include "TransformComponent2D.h"

namespace ZeroEngine {

    const char* TransformComponent2D::name = "TransformComponent2D";

    bool TransformComponent2D::initialize(const XmlReader& reader) {
        assert(strcmp(reader.get_element_name(), name) == 0);

        if (!reader.move_to_element("Position")) return false;
        _position.set_x(reader.get_element_attribute_value_as_float("x"));
        _position.set_y(reader.get_element_attribute_value_as_float("y"));

        if (!reader.move_to_element("Velocity")) return false;
        _velocity.set_x(reader.get_element_attribute_value_as_float("x"));
        _velocity.set_y(reader.get_element_attribute_value_as_float("y"));

        return true;
    }

    void TransformComponent2D::post_initialize() {
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

    EntityComponent* TransformComponent2D::create() {
        return zero_new TransformComponent2D();
    }
}