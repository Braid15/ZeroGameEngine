#include "XmlReader.h"
#include "../../Logger/Logging.h"
#include "TinyXmlReaderImpl.h"

namespace ZeroEngine {

    // @Note: So that implementation can be changed easily.
    // There is no reason why the implementation needs to change during runtime
    // so we set it at compile time.
    IXmlReaderImpl* XmlReader::get_implementation() {
        return zero_new TinyXmlReaderImpl();
    }

    XmlReader::XmlReader() {
        _file_path = nullptr;
        _implementation = get_implementation();
    }

    XmlReader::XmlReader(char* file_path) {
        _file_path = file_path;
        _implementation = get_implementation();
    }

    XmlReader::~XmlReader() {
       zero_delete(_implementation);
    }

    bool XmlReader::load() {
        if (_file_path != nullptr) {
            return _implementation->load_xml_file(_file_path);
        }
        LOG_DEBUG("XmlReader", "_file_path is null");
        return false;
    }

    bool XmlReader::move_to_previous_element() const {
        return _implementation->move_to_previous_element();
    }

    bool XmlReader::load(char* file_path) {
        _file_path = file_path;
        return _implementation->load_xml_file(file_path);
    }

    const char* XmlReader::get_element_name() const {
        return _implementation->get_name();
    }

    bool XmlReader::element_has_attributes() const {
        return _implementation->has_attributes();
    }

    bool XmlReader::element_has_value() const {
        return _implementation->has_value();
    }

    const char* XmlReader::get_element_value() const {
        return _implementation->get_value();
    }

    int32_t XmlReader::get_element_attribute_count() const {
        return _implementation->get_attribute_count();
    }

    bool XmlReader::move_to_element(const char* name) const {
        return _implementation->move_to_element(name);
    }

    const char* XmlReader::get_element_attribute_value(const char* name) const {
        return _implementation->get_attribute_value(name);
    }

    float_t XmlReader::get_element_attribute_value_as_float(const char* name) const {
        return _implementation->get_attribute_value_as_float(name);
    }

    const char* XmlReader::get_element_attribute_value(int32_t index) const {
        return _implementation->get_attribute_value(index);
    }

    bool XmlReader::move_to_next_sibling() const {
        return _implementation->move_to_next_sibling();
    }

    void XmlReader::move_to_root_element() const {
        _implementation->move_to_root_element();
    }

    bool XmlReader::move_to_next_element() const {
        return _implementation->move_to_next_element();
    }

    const char* XmlReader::get_element_attribute_name(const int32_t index) const {
        return _implementation->get_attribute_name(index);
    }

    bool XmlReader::move_to_parent_element() const {
        return _implementation->move_to_parent_element();
    }

#ifdef _DEBUG
    // -----------------
    // Xml File contents
    // -----------------
    // <Actor type = "Sphere" resource = "actors\sphere.xml">

    //     <TransformComponent>
    //     <Position x = "0" y = "5" z = "0" / >
    //     < / TransformComponent>

    //     <PhysicsComponent>
    //     <Shape>Sphere< / Shape>
    //     <Density>pine< / Density>
    //     <PhysicsMaterial>Bouncy< / PhysicsMaterial>
    //     <RigidBodyTransform>
    //     <Scale x = "0.25" y = "0.25" z = "0.25" / >
    //     < / RigidBodyTransform>
    //     < / PhysicsComponent>

    //     <SphereRenderComponent>
    //     <Color r = "0" g = "1.0" b = "1.0" a = "1.0" / >
    //     <Sphere radius = "0.25" segments = "25" / >
    //     < / SphereRenderComponent>

    //     <BaseScriptComponent>
    //     <ScriptObject constructor = "AddSphere" destructor = "RemoveSphere" / >
    //     <ScriptData actorType = "Sphere" / >
    //     < / BaseScriptComponent>

    // < / Actor>

    void TinyXmlReaderImpl_UNIT_TEST() {
        XmlReader reader("S:/projects/Game-Engines/ZeroGameEngine/Engine/test/test.xml");
        reader.load();

        while (reader.move_to_next_element()) {
            const char* element = reader.get_element_name();
            if (strcmp(element, "Actor") == 0) {
                assert(reader.element_has_attributes() == true);
                assert(reader.get_element_attribute_count() == 2);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
                assert(strcmp(reader.get_element_attribute_value("type"), "Sphere") == 0);
                assert(strcmp(reader.get_element_attribute_value("resource"), "actors\\sphere.xml") == 0);
                assert(strcmp(reader.get_element_attribute_value(0), "Sphere") == 0);
                assert(strcmp(reader.get_element_attribute_value(1), "actors\\sphere.xml") == 0);
                assert(strcmp(reader.get_element_attribute_name(0), "type") == 0);
                assert(strcmp(reader.get_element_attribute_name(1), "resource") == 0);
            } else if (strcmp(element, "TransformComponent") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
            } else if (strcmp(element, "Position") == 0) {
                assert(reader.element_has_attributes() == true);
                assert(reader.get_element_attribute_count() == 3);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
                assert(strcmp(reader.get_element_attribute_value("x"), "0") == 0);
                assert(strcmp(reader.get_element_attribute_value("y"), "5") == 0);
                assert(strcmp(reader.get_element_attribute_value("z"), "0") == 0);
                assert(strcmp(reader.get_element_attribute_value(0), "0") == 0);
                assert(strcmp(reader.get_element_attribute_value(1), "5") == 0);
                assert(strcmp(reader.get_element_attribute_value(2), "0") == 0);
                assert(strcmp(reader.get_element_attribute_name(0), "x") == 0);
                assert(strcmp(reader.get_element_attribute_name(1), "y") == 0);
                assert(strcmp(reader.get_element_attribute_name(2), "z") == 0);
            } else if (strcmp(element, "PhysicsComponent") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
            } else if (strcmp(element, "Shape") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == true);
                assert(strcmp(reader.get_element_value(), "Sphere") == 0);
            } else if (strcmp(element, "Density") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == true);
                assert(strcmp(reader.get_element_value(), "pine") == 0);
            } else if (strcmp(element, "PhysicsMaterial") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == true);
                assert(strcmp(reader.get_element_value(), "Bouncy") == 0);
            } else if (strcmp(element, "RigidBodyTransform") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
            } else if (strcmp(element, "Scale") == 0) {
                assert(reader.element_has_attributes() == true);
                assert(reader.get_element_attribute_count() == 3);
                assert(reader.element_has_value() == true);
                assert(strcmp(reader.get_element_value(), "SCALE_TEXT") == 0);
                assert(strcmp(reader.get_element_attribute_value("x"), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_value("y"), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_value("z"), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_value(0), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_value(1), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_value(2), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_name(0), "x") == 0);
                assert(strcmp(reader.get_element_attribute_name(1), "y") == 0);
                assert(strcmp(reader.get_element_attribute_name(2), "z") == 0);
            } else if (strcmp(element, "SphereRenderComponent") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
            } else if (strcmp(element, "Color") == 0) {
                assert(reader.element_has_attributes() == true);
                assert(reader.get_element_attribute_count() == 4);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
                assert(strcmp(reader.get_element_attribute_value("r"), "0") == 0);
                assert(strcmp(reader.get_element_attribute_value("g"), "1.0") == 0);
                assert(strcmp(reader.get_element_attribute_value("b"), "1.0") == 0);
                assert(strcmp(reader.get_element_attribute_value("a"), "1.0") == 0);
                assert(strcmp(reader.get_element_attribute_value(0), "0") == 0);
                assert(strcmp(reader.get_element_attribute_value(1), "1.0") == 0);
                assert(strcmp(reader.get_element_attribute_value(2), "1.0") == 0);
                assert(strcmp(reader.get_element_attribute_value(3), "1.0") == 0);
                assert(strcmp(reader.get_element_attribute_name(0), "r") == 0);
                assert(strcmp(reader.get_element_attribute_name(1), "g") == 0);
                assert(strcmp(reader.get_element_attribute_name(2), "b") == 0);
                assert(strcmp(reader.get_element_attribute_name(3), "a") == 0);
            } else if (strcmp(element, "Sphere") == 0) {
                assert(reader.element_has_attributes() == true);
                assert(reader.get_element_attribute_count() == 2);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
                assert(strcmp(reader.get_element_attribute_value("radius"), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_value("segments"), "25") == 0);
                assert(strcmp(reader.get_element_attribute_value(0), "0.25") == 0);
                assert(strcmp(reader.get_element_attribute_value(1), "25") == 0);
                assert(strcmp(reader.get_element_attribute_name(0), "radius") == 0);
                assert(strcmp(reader.get_element_attribute_name(1), "segments") == 0);
            } else if (strcmp(element, "BaseScriptComponent") == 0) {
                assert(reader.element_has_attributes() == false);
                assert(reader.get_element_attribute_count() == 0);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
            } else if (strcmp(element, "ScriptObject") == 0) {
                assert(reader.element_has_attributes() == true);
                assert(reader.get_element_attribute_count() == 2);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
                assert(strcmp(reader.get_element_attribute_value("constructor"), "AddSphere") == 0);
                assert(strcmp(reader.get_element_attribute_value("destructor"), "RemoveSphere") == 0);
                assert(strcmp(reader.get_element_attribute_value(0), "AddSphere") == 0);
                assert(strcmp(reader.get_element_attribute_value(1), "RemoveSphere") == 0);
                assert(strcmp(reader.get_element_attribute_name(0), "constructor") == 0);
                assert(strcmp(reader.get_element_attribute_name(1), "destructor") == 0);
            } else if (strcmp(element, "ScriptData") == 0) {
                assert(reader.element_has_attributes() == true);
                assert(reader.get_element_attribute_count() == 1);
                assert(reader.element_has_value() == false);
                assert(reader.get_element_value() == "");
                assert(strcmp(reader.get_element_attribute_value("actorType"), "Sphere") == 0);
                assert(strcmp(reader.get_element_attribute_value(0), "Sphere") == 0);
                assert(strcmp(reader.get_element_attribute_name(0), "actorType") == 0);
            }
        }

        reader.move_to_root_element();
        assert(strcmp(reader.get_element_name(), "Actor") == 0);
        assert(reader.move_to_next_element());
        assert(strcmp(reader.get_element_name(), "TransformComponent") == 0);
        assert(reader.move_to_next_sibling());
        assert(strcmp(reader.get_element_name(), "PhysicsComponent") == 0);
        assert(reader.move_to_next_element());
        assert(strcmp(reader.get_element_name(), "Shape") == 0);
        assert(reader.move_to_next_sibling());
        assert(strcmp(reader.get_element_name(), "Density") == 0);
        assert(reader.move_to_next_sibling());
        assert(strcmp(reader.get_element_name(), "PhysicsMaterial") == 0);
        assert(reader.move_to_next_sibling());
        assert(strcmp(reader.get_element_name(), "RigidBodyTransform") == 0);
        assert(reader.move_to_parent_element());
        assert(strcmp(reader.get_element_name(), "PhysicsComponent") == 0);
        assert(reader.move_to_next_sibling());
        assert(strcmp(reader.get_element_name(), "SphereRenderComponent") == 0);
        assert(reader.move_to_next_sibling());
        assert(strcmp(reader.get_element_name(), "BaseScriptComponent") == 0);

        reader.move_to_root_element();
        assert(reader.move_to_element("TransformComponent"));
        assert(strcmp(reader.get_element_name(), "TransformComponent") == 0);
        reader.move_to_root_element();
        assert(reader.move_to_element("PhysicsComponent"));
        assert(strcmp(reader.get_element_name(), "PhysicsComponent") == 0);
        assert(reader.move_to_element("RigidBodyTransform"));
        assert(strcmp(reader.get_element_name(), "RigidBodyTransform") == 0);

        assert(reader.move_to_element("Shape"));
        assert(strcmp(reader.get_element_name(), "Shape") == 0);

        assert(reader.move_to_element("PhysicsComponent"));
        assert(strcmp(reader.get_element_name(), "PhysicsComponent") == 0);

        assert(reader.move_to_element("BaseScriptComponent"));
        assert(strcmp(reader.get_element_name(), "BaseScriptComponent") == 0);

        assert(reader.move_to_element("TransformComponent"));
        assert(strcmp(reader.get_element_name(), "TransformComponent") == 0);

        reader.move_to_root_element();
        assert(strcmp(reader.get_element_name(), "Actor") == 0);

        assert(reader.move_to_previous_element());
        assert(strcmp(reader.get_element_name(), "TransformComponent") == 0);

        assert(reader.move_to_previous_element());
        assert(strcmp(reader.get_element_name(), "Actor") == 0);

        assert(reader.move_to_element("BaseScriptComponent"));
        assert(strcmp(reader.get_element_name(), "BaseScriptComponent") == 0);

        assert(reader.move_to_previous_element());
        assert(strcmp(reader.get_element_name(), "Actor") == 0);






        // Add:
        // move_to_previous_element
    }
#endif

} // End XmlReader.cpp