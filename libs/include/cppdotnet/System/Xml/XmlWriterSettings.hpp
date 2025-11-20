#pragma once

#include <cppdotnet/System/Environment.hpp>
#include <cppdotnet/System/Xml/NewLineHandling.hpp>
#include <cppdotnet/System/Xml/XmlOutputMethod.hpp>
#include <string>
#include <string_view>

namespace System::Xml
{

class XmlWriterSettings
{
public:
    XmlWriterSettings() = default;

    bool CloseOutput() const { return _close_output; }
    void CloseOutput(bool new_value) { _close_output = new_value; }

    bool Indent() const { return _indent; }
    void Indent(bool new_value) { _indent = new_value; }

    std::string_view IndentChars() const { return _indent_chars; }
    void             IndentChars(std::string_view new_indent_string) { _indent_chars = new_indent_string; }

    std::string_view NewLineChars() const { return _new_line_chars; }
    void             NewLineChars(std::string_view new_line) { _new_line_chars = new_line; }

    enum NewLineHandling NewLineHandling() const { return _new_line_handling; }
    void                 NewLineHandling(enum NewLineHandling new_value) { _new_line_handling = new_value; }

    bool NewLineOnAttributes() const { return _new_line_on_attributes; }
    void NewLineOnAttributes(bool new_value) { _new_line_on_attributes = new_value; }

    bool OmitXmlDeclaration() const { return _omit_xml_declaration; }
    void OmitXmlDeclaration(bool new_value) { _omit_xml_declaration = new_value; }

    XmlOutputMethod OutputMethod() const { return _output_method; }

    void Reset();
protected:
    std::string          _indent_chars{ 2, ' ' }; // Two spaces for default
    std::string          _new_line_chars{ System::Environment::NewLine() };
    enum NewLineHandling _new_line_handling = System::Xml::NewLineHandling::Replace;
    XmlOutputMethod      _output_method     = XmlOutputMethod::Xml;
    bool                 _new_line_on_attributes = false;
    bool                 _omit_xml_declaration   = false;
    bool                 _close_output   = false;
    bool                 _indent         = false;
};

}