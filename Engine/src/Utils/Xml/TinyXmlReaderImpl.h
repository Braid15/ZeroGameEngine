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
        TiXmlNode* _previous_node;
        bool _has_moved;
    public:
        ~TinyXmlReaderImpl();
        const char* get_name() const override;
        bool has_value() const override;
        const char* get_value() const override;
        Int32 get_attribute_count() const override;
        bool move_to_element(const char* name) override;
        const char* get_attribute_value(const char* name) const override;
        Float32 get_attribute_value_as_f32(const char* name) const override;
        const char* get_attribute_value(const Int32 index) const override;
        bool move_to_next_sibling() override;
        bool load_xml_file(const char* file_path) override;
        bool has_attributes() const override;
        void move_to_root_element() override;
        bool move_to_next_element() override;
        bool move_to_previous_element() override;
        const char* get_attribute_name(const Int32 index) const override;
        bool move_to_parent_element() override;

        inline StringRepr to_string() const override { return "TinyXmlReaderImpl"; }
    private:
        void set_current_node(TiXmlNode* node);
        bool make_first_move();
        TinyXmlReaderImpl() : _current_node(nullptr), _previous_node(false), _has_moved(false) {}
        TinyXmlReaderImpl(const TinyXmlReaderImpl&) {}
    };
}