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



}