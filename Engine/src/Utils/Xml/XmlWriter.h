#pragma once 

#include "../../ZeroEngineStd.h"
#include "IXmlWriterImpl.h"

namespace ZeroEngine {

    class XmlWriter final : public IZeroObject {
    private:
        IXmlWriterImpl* _implementation;
        char* _file_path;
    public:
        XmlWriter();
        ~XmlWriter();
        explicit XmlWriter(char* file_path);

        void set_file_path(char* path);
        void write_attribute_string(const char* name, const char* value) const;
        void write_start_attribute(const char* name) const;
        void write_end_attribute() const;
        void write_string(const char* str) const;
        void write_comment(const char* comment) const;
        void write_element_string(const char* name, const char* value) const;
        void write_start_element(const char* name) const;
        void write_end_element() const;
        bool save_file() const;
        bool save_file(const char* file_path) const;
        std::string get_xml_string() const;

        StringRepr to_string() const override { return "XmlWriter"; }
    private:
        static IXmlWriterImpl* get_implementation();
        XmlWriter(const XmlWriter&) {}
    };

    #ifdef _DEBUG
    extern void XmlWriter_TinyXmlImpl_UNIT_TEST();
    #endif
}