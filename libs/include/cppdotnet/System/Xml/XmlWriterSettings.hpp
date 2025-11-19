#pragma once

#include <cppdotnet/System/Environment.hpp>
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

    std::string_view NewLineChars() const { return _new_line_chars; }
    void             NewLineChars(std::string_view new_line) { _new_line_chars = new_line; }

    XmlOutputMethod OutputMethod() const { return _output_method; }

    void Reset();
protected:
    std::string     _new_line_chars{ System::Environment::NewLine() };
    XmlOutputMethod _output_method  = XmlOutputMethod::Xml;
    bool            _close_output   = false;
};

}