#include "XmlWriter.h"
#include "../../Logger/Logging.h"
#include "TinyXmlWriterImpl.h"

namespace ZeroEngine {

    // -------------------------
    // XmlWriter Private Members
    // -------------------------

    XmlWriter::XmlWriter() {
        _file_path = nullptr;
        _implementation = get_implementation();
    }

    XmlWriter::XmlWriter(char* file_path) {
        _file_path = file_path;
        _implementation = get_implementation();
    }

    XmlWriter::~XmlWriter() {
        zero_free(_file_path);
        zero_delete(_implementation);
    }

    void XmlWriter::set_file_path(char* file_path) {
        _file_path = file_path;
    }

    void XmlWriter::write_attribute_string(const char* name, const char* value) const {
        _implementation->write_attribute_string(name, value);
    }

    void XmlWriter::write_start_attribute(const char* name) const {
        _implementation->write_start_attribute(name);
    }

    void XmlWriter::write_end_attribute() const {
        _implementation->write_end_attribute();
    }

    void XmlWriter::write_string(const char* str) const {
        _implementation->write_string(str);
    }

    void XmlWriter::write_comment(const char* comment) const {
        _implementation->write_comment(comment);
    }

    void XmlWriter::write_element_string(const char* name, const char* value) const {
        _implementation->write_element_string(name, value);
    }

    void XmlWriter::write_start_element(const char* name) const {
        _implementation->write_start_element(name);
    }

    void XmlWriter::write_end_element() const {
        _implementation->write_end_element();
    }

    bool XmlWriter::save_file() const {
        if (!_file_path) return false;
        return _implementation->save_file(_file_path);
    }

    const char* XmlWriter::get_xml_string() const {
        return _implementation->get_xml_string();
    }

    // -------------------------
    // XmlWriter Private Members
    // -------------------------

    IXmlWriterImpl* XmlWriter::get_implementation() {
        return zero_new TinyXmlWriterImpl();
    }

    #ifdef _DEBUG
    void XmlWriter_TinyXmlImpl_UNIT_TEST() {
       XmlWriter writer;
       writer.write_element_string("TestElement", "TestValue");
    }
    #endif
}