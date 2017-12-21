#pragma once

#include "../../ZeroEngineStd.h"
#include "IXmlReaderImpl.h"
#include "../../3rdParty/TinyXML/tinyxml.h"

namespace ZeroEngine {

    class TinyXmlReaderImpl final : public IXmlReaderImpl {
    private:
        friend class XmlReader;
        TiXmlDocument _document;
        bool _has_loaded;
    public:
        const char* get_name() const override;
        bool has_value() const override;
        const char* get_value() const override;
        int32_t get_attribute_count() const override;
        void move_to_start_element() override;
        void move_to_start_element(const char* name) override;
        const char* get_attribute_value(const char* name) const override;
        const char* get_attribute_value(int32_t index) const override;
        void move_to_next_element() override;
        void move_to_next_sibling() override;
        bool load_xml_file(const char* file_path) override;
        bool is_element_empty() const override;

        inline StringRepr to_string() const override { return "TinyXmlReaderImpl"; }
    private:
        TinyXmlReaderImpl() { _has_loaded = false; }
        TinyXmlReaderImpl(const TinyXmlReaderImpl&) {}
    };
}