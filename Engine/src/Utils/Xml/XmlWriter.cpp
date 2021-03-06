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

    bool XmlWriter::save_file(const char* file_path) const {
        return _implementation->save_file(file_path);
    }

    std::string XmlWriter::get_xml_string() const {
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
       writer.write_comment("Comment One");
       writer.write_start_element("RootElement");
       writer.write_start_element("ElementTwo");
       writer.write_start_element("ElementThree");
       writer.write_comment("Comment Two");
       writer.write_start_element("ElementFour");
       writer.write_attribute_string("Attribute", "Value");
       writer.write_string("ElementFourVal");
       writer.write_end_element();
       writer.write_end_element();
       writer.write_end_element();
       writer.write_end_element();

       /*
       const char* file;
       file = "S:\\projects\\game-engines\\zerogameengine\\test.xml";
       writer.save_file(file);
       */
    }
    #endif
}