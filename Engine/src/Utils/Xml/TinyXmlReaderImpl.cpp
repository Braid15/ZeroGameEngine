#include "TinyXmlReaderImpl.h"

namespace ZeroEngine {

    TinyXmlReaderImpl::~TinyXmlReaderImpl() {
        _document.Clear();
    }

    const char* TinyXmlReaderImpl::get_name() const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            return _current_node->Value();
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Node is invalid");
        }
        return "";
    }

    bool TinyXmlReaderImpl::has_value() const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            LOG_UNIMPLEMENTED();
            return true;
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Node is invalid");
        }
        return false;
    }

    const char* TinyXmlReaderImpl::get_value() const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            return _current_node->Value();
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Node is invalid");
        }
        return "";
    }

    int32_t TinyXmlReaderImpl::get_attribute_count() const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
            TiXmlAttribute* attribute = element->FirstAttribute();
            int32_t count = 0;
            while (attribute) {
                attribute = attribute->Next();
                count++;
            }
            return count;
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Node is invalid");
        }
        return 0;
    }

    void TinyXmlReaderImpl::move_to_first_element() {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            if (!_current_node->NoChildren()) {
                if (_current_node->FirstChildElement()) {
                    _current_node = _current_node->FirstChildElement();
                } else {
                    LOG_DEBUG("TinyXmlReaderImpl", "Error getting first child element");
                }
            } else {
                LOG_DEBUG("TinyXmlReaderImpl", "Current element has no children");
            }
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Node is invalid");
        }
    }

    void TinyXmlReaderImpl::move_to_first_element(const char* name) {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            if (!_current_node->NoChildren()) {
                if (_current_node->FirstChildElement(name)) {
                    _current_node = _current_node->FirstChildElement(name);
                } else {
                    LOG_DEBUG("TinyXmlReaderImpl", "Error getting first child element");
                }
            } else {
                LOG_DEBUG("TinXmlReaderImpl", "Current element has no children");
            }
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Current node is invalid");
        }
    }

    const char* TinyXmlReaderImpl::get_attribute_value(const char* name) const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            const TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
            if (element->Attribute(name)) {
                return element->Attribute(name);
            }
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Current node is not valid");
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
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Current node is not valid");
        }
        return "";
    }

    void TinyXmlReaderImpl::move_to_next_element() {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            if (_current_node->FirstChildElement()) {
                _current_node = _current_node->FirstChildElement();
            } else if (_current_node->NextSiblingElement()) {
                _current_node = _current_node->NextSiblingElement();
            } else {
                LOG_DEBUG("TinyXmlReaderImpl", "Unable to move to next node");
            }
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Current node is not valid");
        }
    }

    void TinyXmlReaderImpl::move_to_next_sibling() {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            _current_node = _current_node->NextSiblingElement();
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Current node is not valid");
        }
    }

    bool TinyXmlReaderImpl::has_attributes() const {
        bool has_attributes = false;
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            TiXmlElement* element = dynamic_cast<TiXmlElement*>(_current_node);
            if (element->FirstAttribute()) {
                has_attributes = true;
            }
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Current node is not valid");
        }
        return has_attributes;
    }

    bool TinyXmlReaderImpl::is_element_empty() const {
        if (_current_node) {
            assert(_current_node->Type() == TiXmlNode::TINYXML_ELEMENT);
            LOG_UNIMPLEMENTED();
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", "Current node is not valid");
        }
        return false;
    }

    void TinyXmlReaderImpl::move_to_root_element() {
        _current_node = _document.FirstChildElement();
    }

    // @TODO: Need way for XmlReader to get error
    bool TinyXmlReaderImpl::load_xml_file(const char* file_path) {
        bool success = _document.LoadFile(file_path);
        if (success) {
            // I assert that current node is always in element in all of this classes methods.
            // I keep _current_node as type TiXmlNode instead of TiXmlElement so that I can 
            // change things in the future more easily if need be.
            _current_node = _document.FirstChildElement();
        } else {
            LOG_DEBUG("TinyXmlReaderImpl", _document.ErrorDesc());
        }
        return success;
    }


}