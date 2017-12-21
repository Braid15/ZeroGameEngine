#pragma once

#include "../../ZeroEngineStd.h"
#include "IXmlReaderImpl.h"

namespace ZeroEngine {

    class XmlReader final : public IZeroObject {
    private:
        IXmlReaderImpl* _implementation;
        char* _file_path;
    public:
        XmlReader();
        explicit XmlReader(char* file_path);
        ~XmlReader();
        bool load();
        bool load(char* file_path);
        const char* get_current_element_name() const;
        bool current_element_has_attributes() const;
        bool current_element_has_value() const;
        const char* get_current_element_value() const;
        // get_value_as
        int32_t get_current_element_attribute_count() const;
        void move_to_start_element() const;
        void move_to_start_element(const char* name) const;
        const char* get_current_element_attribute_value(const char* name) const;
        const char* get_current_element_attribute_value(int32_t index) const;
        // get_attribute_value_as
        void move_to_next_element() const;
        void move_to_next_sibling() const;
        bool is_current_element_empty() const;
        void move_to_root_element() const;

        inline virtual StringRepr to_string() const override { return "XmlReader"; }
    private:
        static IXmlReaderImpl* get_implementation();
        XmlReader(const XmlReader&) {}
    };
}