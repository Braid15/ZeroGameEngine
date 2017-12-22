#include "TinyXmlWriterImpl.h"
#include "../../Logger/Logging.h"

namespace ZeroEngine {

    // --------------------------------
    // TinyXmlWriterImpl Public Members
    // ---------------------------------
    
    TinyXmlWriterImpl::~TinyXmlWriterImpl() {

    }

    void TinyXmlWriterImpl::write_attribute_string(const char* name, const char* value) {

    }

    void TinyXmlWriterImpl::write_start_attribute(const char* name) {

    }

    void TinyXmlWriterImpl::write_end_attribute() {

    }

    void TinyXmlWriterImpl::write_string(const char* str) {

    }

    void TinyXmlWriterImpl::write_comment(const char* comment) {

    }

    void TinyXmlWriterImpl::write_element_string(const char* name, const char* value) {

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

    const char* TinyXmlWriterImpl::get_xml_string() const {
        LOG_UNIMPLEMENTED();
        return "";
    }


    // ---------------------------------
    // TinyXmlWriterImpl Private Members
    // ----------------------------------

    TinyXmlWriterImpl::TinyXmlWriterImpl() {

    }
}