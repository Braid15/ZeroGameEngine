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
        writer.write_end_element();
    }
}