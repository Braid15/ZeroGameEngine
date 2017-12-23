#pragma once 

#include "../../ZeroEngineStd.h"
#include "IXmlWriterImpl.h"
#include "../../3rdParty/TinyXML/tinyxml.h"

#include <stack>

namespace ZeroEngine {

    // -----------------
    // TinyXmlWriterImpl
    // -----------------

    class TinyXmlWriterImpl final : public IXmlWriterImpl {
    private:
        friend class XmlWriter;
        std::list<TiXmlElement*> _element_chain;
        TiXmlDocument _document;
        uint32_t _current_element;
        bool _writing_attribute;
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
        TinyXmlWriterImpl() : _writing_attribute(false), 
            _current_element(0) {}
        TinyXmlWriterImpl(const TinyXmlWriterImpl&) {}
    };
}