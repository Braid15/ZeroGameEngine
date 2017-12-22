#include "TinyXmlWriterImpl.h"
#include "../../Logger/Logging.h"

namespace ZeroEngine {

    // --------------------------------
    // TinyXmlWriterImpl Public Members
    // ---------------------------------
    
    TinyXmlWriterImpl::~TinyXmlWriterImpl() {
    }

    void TinyXmlWriterImpl::write_attribute_string(const char* name, const char* value) {
        if (!is_open_node_valid_type(TiXmlNode::TINYXML_ELEMENT)) return;
        TiXmlElement* element = dynamic_cast<TiXmlElement*>(_open_node);
        element->SetAttribute(name, value);
        _open_node = element;
    }

    void TinyXmlWriterImpl::write_start_attribute(const char* name) {
        LOG_UNIMPLEMENTED();
    }

    void TinyXmlWriterImpl::write_end_attribute() {
        LOG_UNIMPLEMENTED();
    }

    void TinyXmlWriterImpl::write_string(const char* str) {
        if (!_open_node) return;
        int32_t type = _open_node->Type();
        if (type != TiXmlNode::TINYXML_ELEMENT && type != TiXmlNode::TINYXML_TEXT) return;

        switch (_open_node->Type()) {
            case TiXmlNode::TINYXML_ELEMENT:
            {
                LOG_TODO("TinyXmlWriterImpl", "Not clear on implementatino details yet");
                break;
            }
            case TiXmlNode::TINYXML_TEXT:
            {
                LOG_TODO("TinyXmlWriterImpl", "Not clear on implementatino details yet");
                break;
            }
            default:
            {
                LOG_DEBUG("TinyXmlWriterImpl", "Error. Unexpected type");
                break;
            }
        }
    }

    void TinyXmlWriterImpl::write_comment(const char* comment) {
        TiXmlComment* comment_node = zero_new TiXmlComment(comment);
        _document.LinkEndChild(comment_node);
    }

    void TinyXmlWriterImpl::write_element_string(const char* name, const char* value) {
        TiXmlElement* element = zero_new TiXmlElement(name);
        TiXmlText* text = zero_new TiXmlText(value);
        element->LinkEndChild(text);
        _document.LinkEndChild(element);
    }

    void TinyXmlWriterImpl::write_start_element(const char* name) {
        
    }

    void TinyXmlWriterImpl::write_end_element() {

    }

    bool TinyXmlWriterImpl::save_file(const char* file_path) {
        assert(file_path);
        LOG_UNIMPLEMENTED();
        return false;
    }

    std::string TinyXmlWriterImpl::get_xml_string() const {
        TiXmlPrinter printer;
        _document.Accept(&printer);
        return printer.CStr();
    }

    // ---------------------------------
    // TinyXmlWriterImpl Private Members
    // ---------------------------------


    bool TinyXmlWriterImpl::is_open_node_valid_type(const TiXmlNode::NodeType& type) {
        return (_open_node && _open_node->Type() == type);
    }

}