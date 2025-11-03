#include <cppdotnet/System/Xml/XmlReaderSettings.hpp>


namespace System::Xml
{

void XmlReaderSettings::Reset()
{
    _name_table = System::Xml::NameTable{};
    _close_input = false;
    _ignore_comments = false;
}

}