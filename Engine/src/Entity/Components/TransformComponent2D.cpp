#include "TransformComponent2D.h"
#include "../../Utils/Hash.h"

namespace ZeroEngine {

    const char* TransformComponent2D::name = "TransformComponent2D";
    const EntityComponentId TransformComponent2D::id = STRING_ID("TransformComponent2D");


    bool TransformComponent2D::initialize(const XmlReader& reader) {
        LOG_TODO("TransformComponent2D", "Make universal to be used between 2d and 3d");
        LOG_UNIMPLEMENTED();

        /*
        assert(strcmp(reader.get_element_name(), name) == 0);

        if (!reader.move_to_element("Position")) return false;
        _transform.set_x(reader.get_element_attribute_value_as_f32("x"));
        _transform.set_y(reader.get_element_attribute_value_as_f32("y"));

        */
        return true;
    }

    void TransformComponent2D::post_initialize() {
    }

    void TransformComponent2D::on_write_xml(const XmlWriter& writer) {
        LOG_UNIMPLEMENTED();
        /*
        writer.write_start_element(name);

        writer.write_start_element("Position");
        writer.write_attribute_string("x", std::to_string(_transform.get_x()).c_str());
        writer.write_attribute_string("y", std::to_string(_transform.get_y()).c_str());
        writer.write_end_element();

        writer.write_end_element();
        */
    }

    EntityComponent* TransformComponent2D::create() {
        return zero_new TransformComponent2D();
    }
}