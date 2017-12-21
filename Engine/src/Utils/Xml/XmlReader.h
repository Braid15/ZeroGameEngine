#pragma once

#include "../../ZeroEngineStd.h"
#include "IXmlReaderImpl.h"

namespace ZeroEngine {

    // ----------
    // XmlReader
    // ----------
    // --------------------------------------------------------------------------
    // XmlReader provides a simplified interface for reading xml files.
    // During reading it will only directly access and move along element nodes.
    // This is to make traversal of the xml a bit more simplified.
    // --------------------------------------------------------------------------

    // @TODO: Should there be a full fledged XmlReader class that will traverse
    //        all xml node types and make this class XmlElementReader instead?

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
        const char* get_element_name() const;
        bool element_has_attributes() const;
        bool element_has_value() const;
        const char* get_element_value() const;
        // get_value_as
        int32_t get_element_attribute_count() const;
        bool move_to_element(const char* name) const;
        const char* get_element_attribute_value(const char* name) const;
        const char* get_element_attribute_value(int32_t index) const;
        // get_attribute_value_as
        bool move_to_next_sibling() const;
        void move_to_root_element() const;
        bool move_to_parent_element() const;
        bool move_to_next_element() const;
        const char* get_element_attribute_name(const int32_t index) const;

        inline virtual StringRepr to_string() const override { return "XmlReader"; }
    private:
        static IXmlReaderImpl* get_implementation();
        XmlReader(const XmlReader&) {}
    };

    #ifdef _DEBUG
    extern void TinyXmlReaderImpl_UNIT_TEST();
    #endif
}