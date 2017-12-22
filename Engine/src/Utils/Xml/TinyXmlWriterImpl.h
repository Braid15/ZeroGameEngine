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
        const char* get_xml_string() const override;

        inline StringRepr to_string() const { return "TinyXmlWriterImpl"; }
    private:
        TinyXmlWriterImpl();
        TinyXmlWriterImpl(const TinyXmlWriterImpl&) {}
    };
}