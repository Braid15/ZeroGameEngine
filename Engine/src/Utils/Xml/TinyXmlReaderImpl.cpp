#include "TinyXmlReaderImpl.h"

namespace ZeroEngine {

    const char* TinyXmlReaderImpl::get_name() const {
        return "";
    }

    bool TinyXmlReaderImpl::has_value() const {
        return false;
    }

    const char* TinyXmlReaderImpl::get_value() const {
        return "";
    }

    int32_t TinyXmlReaderImpl::get_attribute_count() const {
        return 3;
    }

    void TinyXmlReaderImpl::move_to_start_element() {

    }

    void TinyXmlReaderImpl::move_to_start_element(const char* name) {

    }

    const char* TinyXmlReaderImpl::get_attribute_value(const char* name) const {
        return "";
    }

    const char* TinyXmlReaderImpl::get_attribute_value(int32_t index) const {
        return "";
    }

    void TinyXmlReaderImpl::move_to_next_element() {

    }

    void TinyXmlReaderImpl::move_to_next_sibling() {

    }

    bool TinyXmlReaderImpl::load_xml_file(const char* file_path) {
        _has_loaded = _document.LoadFile(file_path);
        return _has_loaded;
    }

    bool TinyXmlReaderImpl::is_element_empty() const {
        return false;
    }
}