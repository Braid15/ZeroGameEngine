#pragma once

#include "../../ZeroEngineStd.h"
#include "IXmlReaderImpl.h"
#include "../../3rdParty/TinyXML/tinyxml.h"

namespace ZeroEngine {

    class TinyXmlReaderImpl final : public IXmlReaderImpl {
    private:
        friend class XmlReader;
        TiXmlDocument _document;
        TiXmlNode* _current_node;
        bool _has_moved;
    public:
        ~TinyXmlReaderImpl();
        const char* get_name() const override;
        bool has_value() const override;
        const char* get_value() const override;
        int32_t get_attribute_count() const override;
        void move_to_first_element() override;
        void move_to_first_element(const char* name) override;
        const char* get_attribute_value(const char* name) const override;
        const char* get_attribute_value(const int32_t index) const override;
        void move_to_next_element() override;
        void move_to_next_sibling() override;
        bool load_xml_file(const char* file_path) override;
        bool is_element_empty() const override;
        bool has_attributes() const override;
        void move_to_root_element() override;
        bool read() override;

        inline StringRepr to_string() const override { return "TinyXmlReaderImpl"; }
    private:
        bool needed_init();
        TinyXmlReaderImpl() : _current_node(nullptr), _has_moved(false) {}
        TinyXmlReaderImpl(const TinyXmlReaderImpl&) {}
    };
}