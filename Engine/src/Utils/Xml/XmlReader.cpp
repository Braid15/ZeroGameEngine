#include "XmlReader.h"
#include "../../Logger/Logging.h"
#include "TinyXmlReaderImpl.h"

namespace ZeroEngine {

    // @Note: So that implementation can be changed easily.
    // There is no reason why the implementation needs to change during runtime
    // so we set it's implementation at compile time.
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

    bool XmlReader::load(char* file_path) {
        _file_path = file_path;
        return _implementation->load_xml_file(file_path);
    }

    const char* XmlReader::get_current_element_name() const {
        return _implementation->get_name();
    }

    bool XmlReader::current_element_has_attributes() const {
        return _implementation->has_attributes();
    }

    bool XmlReader::current_element_has_value() const {
        return _implementation->has_value();
    }

    const char* XmlReader::get_current_element_value() const {
        return _implementation->get_value();
    }

    int32_t XmlReader::get_current_element_attribute_count() const {
        return _implementation->get_attribute_count();
    }

    void XmlReader::move_to_start_element() const {
        _implementation->move_to_first_element();
    }

    void XmlReader::move_to_start_element(const char* name) const {
        _implementation->move_to_first_element(name);
    }

    const char* XmlReader::get_current_element_attribute_value(const char* name) const {
        return _implementation->get_attribute_value(name);
    }

    const char* XmlReader::get_current_element_attribute_value(int32_t index) const {
        return _implementation->get_attribute_value(index);
    }

    void XmlReader::move_to_next_element() const {
        _implementation->move_to_next_element();
    }

    void XmlReader::move_to_next_sibling() const {
        _implementation->move_to_next_sibling();
    }

    bool XmlReader::is_current_element_empty() const {
        return _implementation->is_element_empty();
    }

    void XmlReader::move_to_root_element() const {
        _implementation->move_to_root_element();
    }

    bool XmlReader::read() const {
        return _implementation->read();
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

        while (reader.read()) {
            std::cout << "get_element_name: " << reader.get_current_element_name() << "\n";
            std::cout << "has_attributes: " << reader.current_element_has_attributes() << "\n";
            std::cout << "has_value: " << reader.current_element_has_value() << "\n";
            std::cout << "value: " << reader.get_current_element_value() << "\n";
            if (reader.current_element_has_attributes()) {
                int count = reader.get_current_element_attribute_count();
                for (int i = 0; i < count; i++) {
                    std::cout << "attribue_val(" << i << "): " << reader.get_current_element_attribute_value(i) << "\n";
                }
            }
            std::cout << "\n";
        }

    }


    #endif

}