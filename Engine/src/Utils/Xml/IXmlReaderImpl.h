#pragma once

#include "../../ZeroEngineStd.h"

namespace ZeroEngine {

    // --------------
    // IXmlReaderImpl
    // --------------

    class IXmlReaderImpl : virtual public IZeroObject {
    public:
        virtual ~IXmlReaderImpl() {}
        virtual const char* get_name() const = 0;
        virtual bool has_value() const = 0;
        virtual const char* get_value() const = 0;
        virtual int32 get_attribute_count() const = 0;
        virtual bool move_to_element(const char* name) = 0;
        virtual const char* get_attribute_value(const char* name) const = 0;
        virtual float32 get_attribute_value_as_f32(const char* name) const = 0;
        virtual const char* get_attribute_value(int32 index) const = 0;
        virtual bool move_to_next_sibling() = 0;
        virtual bool load_xml_file(const char* file_path) = 0;
        virtual bool has_attributes() const = 0;
        virtual bool move_to_previous_element() = 0;
        virtual void move_to_root_element() = 0;
        virtual bool move_to_next_element() = 0;
        virtual const char* get_attribute_name(const int32 index) const = 0;
        virtual bool move_to_parent_element() = 0;

        virtual StringRepr to_string() const = 0;
    };
}