#include <cppdotnet/System/Xml/XmlImplementation.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/NameTable.hpp>

namespace System::Xml
{

XmlImplementation::XmlImplementation()
    :
    _name_table( std::make_shared<System::Xml::NameTable>() )
{
}

XmlImplementation::XmlImplementation(std::shared_ptr<XmlNameTable> name_table)
    :
    _name_table( name_table )
{
}

std::shared_ptr<XmlDocument> XmlImplementation::CreateDocument()
{
    // All created documents share the same XmlNameTable!
    return std::make_shared<XmlDocument>( _name_table );
}

std::shared_ptr<XmlNameTable> XmlImplementation::NameTable() const
{
    return _name_table;
}

}