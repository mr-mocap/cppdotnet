#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/NameTable.hpp>

namespace System::Xml
{

XmlDocument::XmlDocument()
    :
    _name_table( std::make_shared<System::Xml::NameTable>() )
{
    INVARIANT( _name_table );
}

std::string_view XmlDocument::Name() const
{
    return "Not Implemented!";
}

XmlNodeType XmlDocument::_getNodeType() const
{
    return XmlNodeType::Document;
}

}