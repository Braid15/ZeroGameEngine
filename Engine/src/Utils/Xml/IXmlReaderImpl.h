#pragma once

#include "../../ZeroEngineStd.h"

namespace ZeroEngine {
// --------------
    // IXmlReaderImpl
    // --------------

    class IXmlReaderImpl : virtual public IZeroObject {
    public:
        virtual const char* get_name() const = 0;
        virtual bool has_value() const = 0;
        virtual const char* get_value() const = 0;
        virtual int32_t get_attribute_count() const = 0;
        virtual void move_to_start_element() = 0;
        virtual void move_to_start_element(const char* name) = 0;
        virtual const char* get_attribute_value(const char* name) const = 0;
        virtual const char* get_attribute_value(int32_t index) const = 0;
        virtual void move_to_next_element() = 0;
        virtual void move_to_next_sibling() = 0;
        virtual bool load_xml_file(const char* file_path) = 0;
        virtual bool is_element_empty() const = 0;

        virtual StringRepr to_string() const = 0;
    };
}