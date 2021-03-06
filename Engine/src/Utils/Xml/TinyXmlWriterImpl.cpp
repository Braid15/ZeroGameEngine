#pragma comment(lib, "tinyxml.lib")

#include "TinyXmlWriterImpl.h"
#include "../../Logger/Logging.h"

// @TODO: Methods should return bool 

namespace ZeroEngine {

    // --------------------------------
    // TinyXmlWriterImpl Public Members
    // ---------------------------------
    
    TinyXmlWriterImpl::~TinyXmlWriterImpl() {
        // _element_chain should be empty by this point,
        // but just to be sure.
        if (_element_chain.empty()) {
            LOG_DEBUG("TinyXmlWriterImpl", "element chain is not empty");
            while (!_element_chain.empty()) {
                TiXmlElement* element = _element_chain.back();
                _element_chain.pop_back();
                zero_delete(element);
            }
        }
    }

    void TinyXmlWriterImpl::write_attribute_string(const char* name, const char* value) {
        if (_element_chain.empty()) return;
        _element_chain.back()->SetAttribute(name, value);
    }

    void TinyXmlWriterImpl::write_start_attribute(const char* name) {
        if (_element_chain.empty()) return;
        _element_chain.back()->SetAttribute(name, "");
        _writing_attribute = true;
    }

    void TinyXmlWriterImpl::write_end_attribute() {
        _writing_attribute = false;
    }

    void TinyXmlWriterImpl::write_string(const char* str) {
        if (_element_chain.empty()) return;
        if (_writing_attribute) {
            _element_chain.back()->LastAttribute()->SetValue(str);
        } else {
            TiXmlText* text = zero_new TiXmlText(str);
            _element_chain.back()->LinkEndChild(text);
        }
    }

    void TinyXmlWriterImpl::write_comment(const char* comment) {
        TiXmlComment* comment_node = zero_new TiXmlComment(comment);
        if (!_element_chain.empty()) {
            _element_chain.back()->LinkEndChild(comment_node);
        } else {
            _document.LinkEndChild(comment_node);
        }
    }

    void TinyXmlWriterImpl::write_element_string(const char* name, const char* value) {
        TiXmlElement* element = zero_new TiXmlElement(name);
        TiXmlText* text = zero_new TiXmlText(value);
        element->LinkEndChild(text);
        _document.LinkEndChild(element);
    }

    void TinyXmlWriterImpl::write_start_element(const char* name) {
        TiXmlElement* element = zero_new TiXmlElement(name);
        if (!_element_chain.empty()) {
            _element_chain.back()->LinkEndChild(element);
        }
        _element_chain.push_back(element);
        _current_element++;
    }

    void TinyXmlWriterImpl::write_end_element() {
        _current_element = (_current_element > 0) ? _current_element - 1 : 0;
        if (_current_element == 0) {
            TiXmlElement* root = _element_chain.front();
            _document.LinkEndChild(root);
            _element_chain.clear();
        } else {
            _element_chain.pop_back();
        }
    }

    bool TinyXmlWriterImpl::save_file(const char* file_path) {
        if (!file_path) return false;
        return _document.SaveFile(file_path);
    }

    std::string TinyXmlWriterImpl::get_xml_string() const {
        TiXmlPrinter printer;
        _document.Accept(&printer);
        return printer.CStr();
    }

    // ---------------------------------
    // TinyXmlWriterImpl Private Members
    // ---------------------------------
}