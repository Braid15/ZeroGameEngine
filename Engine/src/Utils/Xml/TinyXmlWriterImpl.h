#pragma once 

#include "../../ZeroEngineStd.h"
#include "IXmlWriterImpl.h"
#include "../../3rdParty/TinyXML/tinyxml.h"

namespace ZeroEngine {

    // -----------------
    // TinyXmlWriterImpl
    // -----------------

    class TinyXmlWriterImpl final : public IXmlWriterImpl {
    private:
        friend class XmlWriter;
        TiXmlDocument _document;
        // This is used to keep track of what node is being added
        // to the Xml doc. It should not be passed to TiXmlDocument incase
        // it dereferences the pointer. This class will handle it's creation and deletion.
        TiXmlNode* _open_node;
    public:
        ~TinyXmlWriterImpl();
        void write_attribute_string(const char* name, const char* value) override;
        void write_start_attribute(const char* name) override;
        void write_end_attribute() override;
        void write_string(const char* str) override;
        void write_comment(const char* comment) override;
        void write_element_string(const char* name, const char* value) override;
        void write_start_element(const char* name) override;
        void write_end_element() override;
        bool save_file(const char* file_path) override;
        std::string get_xml_string() const override;

        inline StringRepr to_string() const { return "TinyXmlWriterImpl"; }
    private:
        TinyXmlWriterImpl() : _open_node(nullptr) {}
        TinyXmlWriterImpl(const TinyXmlWriterImpl&) {}
        bool is_open_node_valid_type(const TiXmlNode::NodeType& type);
    };
}