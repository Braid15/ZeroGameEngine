#include "TinyXmlReaderImpl.h"

namespace ZeroEngine {

    // Convenience macro since I log this in every method.
    // I don't want to assert whether _current_node is a valid pointer
    // because some methods use it's invalid state to work.
    #define LOG_INVALID_NODE() LOG_DEBUG("TinyXmlReaderImpl", "Node is invalid");


    TinyXmlReaderImpl::~TinyXmlReaderImpl() {
        _document.Clear();
    }

    const char* TinyXmlReaderImpl::get_name() const {
        if (!_current_node) return "";

        assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
        return _current_node->Value();
    }

    bool TinyXmlReaderImpl::has_value() const {
        if (!_current_node || _current_node->NoChildren()) return false;

        assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
        LOG_TODO("TinyXmlReaderImpl", "Fix to iterate through all children to check for value");
        return (_current_node->FirstChild()->Type() == TiXmlNode::TINYXML_TEXT);
    }

    const char* TinyXmlReaderImpl::get_value() const {
        // has_value() will do the proper validation checks
        return (has_value()) ? _current_node->FirstChild()->Value() : "";
    }

    bool TinyXmlReaderImpl::move_to_parent_element() {
        if (!_current_node || !_current_node->Parent()) return false;

        _current_node = _current_node->Parent();
        return true;
    }

    int32_t TinyXmlReaderImpl::get_attribute_count() const {
        if (!_current_node) return 0;

        assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
        TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
        TiXmlAttribute* attribute = element->FirstAttribute();
        int32_t count = 0;
        while (attribute) {
            attribute = attribute->Next();
            count++;
        }
        return count;
    }

    bool TinyXmlReaderImpl::move_to_element(const char* name) {
        make_first_move();
        if (!_current_node) return false;
        if (strcmp(_current_node->Value(), name) == 0) return true;

        if (_current_node->FirstChildElement(name)) {
            _current_node = _current_node->FirstChildElement(name);
            return true;
        }

        // Check if parent is requested element
        if (strcmp(_current_node->Parent()->Value(), name) == 0) {
            _current_node = _current_node->Parent();
            return true;
        }

        // Check parents child elements, which will be a sibling
        // to the current node. 
        if (_current_node->Parent()->FirstChildElement(name)) {
            _current_node = _current_node->Parent()->FirstChildElement(name);
            return true;
        }

        return false;
    }

    const char* TinyXmlReaderImpl::get_attribute_value(const char* name) const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            const TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
            if (element->Attribute(name)) {
                return element->Attribute(name);
            } 
        }
        return "";
    }

    const char* TinyXmlReaderImpl::get_attribute_value(const int32_t index) const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
            TiXmlAttribute* attribute = element->FirstAttribute();
            int32_t current_index = 0;
            while (attribute && current_index != index) {
                attribute = attribute->Next();
                current_index++;
            }

            if (attribute && current_index == index) {
                return attribute->Value();
            }
        } 
        return "";
    }

    bool TinyXmlReaderImpl::move_to_next_element() {
        if (make_first_move() && _current_node) return true;
        if (!_current_node) return false;

        assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
        if (_current_node->FirstChildElement()) {
            _current_node = _current_node->FirstChildElement();
            return true;
        } 
        if (_current_node->NextSiblingElement()) {
            _current_node = _current_node->NextSiblingElement();
            return true;
        }

        while (_current_node) {
            if (_current_node->NextSiblingElement()) {
                _current_node = _current_node->NextSiblingElement();
                return true;
            } else {
                _current_node = _current_node->Parent();
            }
        }
        // next element wasn't found
        return false;
    }

    bool TinyXmlReaderImpl::move_to_next_sibling() {
        if (make_first_move() && _current_node) return true;
        if (!_current_node || !_current_node->NextSibling()) return false;

        _current_node = _current_node->NextSiblingElement();
        return true;
    }

    const char* TinyXmlReaderImpl::get_attribute_name(const int32_t index) const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
            TiXmlAttribute* attribute = element->FirstAttribute();
            int32_t count = 0;
            while (attribute) {
                if (count == index) {
                    return attribute->Name();
                }
                attribute = attribute->Next();
                count++;
            }
        }
        return "";
    }

    bool TinyXmlReaderImpl::has_attributes() const {
        if (!_current_node)  return false;

        assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
        TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
        return (element->FirstAttribute() != nullptr);
    }

    void TinyXmlReaderImpl::move_to_root_element() {
        _current_node = _document.FirstChildElement();
        _has_moved = true;
    }

    bool TinyXmlReaderImpl::make_first_move() {
        if (_has_moved) return false;
        _current_node = _document.FirstChildElement();
        _has_moved = true;
        return true; 
    }

    // @TODO: Need way for XmlReader to get error
    bool TinyXmlReaderImpl::load_xml_file(const char* file_path) {
        return _document.LoadFile(file_path);
    }
}