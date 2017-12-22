#pragma once

#include "../../ZeroEngineStd.h" 

namespace ZeroEngine {

    // --------------
    // IXmlWriterImpl
    // --------------

    class IXmlWriterImpl : virtual public IZeroObject {
    public:
        virtual void write_attribute_string(const char* name, const char* value) = 0;
        virtual void write_start_attribute(const char* name) = 0;
        virtual void write_end_attribute() = 0;

        virtual void write_string(const char* str) = 0;
        virtual void write_comment(const char* comment) = 0;

        virtual void write_element_string(const char* name, const char* value) = 0;
        virtual void write_start_element(const char* name) = 0;
        virtual void write_end_element() = 0;
        virtual bool save_file(const char* file_path) = 0;
        virtual const char* get_xml_string() const = 0;

        virtual StringRepr to_string() const = 0;
        virtual ~IXmlWriterImpl() {}
    };
}