#include <cppdotnet/System/Xml/XmlWriterSettings.hpp>


namespace System::Xml
{

void XmlWriterSettings::Reset()
{
    _new_line_chars = System::Environment::NewLine();
    _output_method  = XmlOutputMethod::Xml;
    _close_output   = false;
}

}