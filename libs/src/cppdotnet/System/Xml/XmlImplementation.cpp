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

XmlImplementation::XmlImplementation(std::unique_ptr<XmlNameTable> &&name_table)
    :
    _name_table( std::move(name_table) )
{
}

XmlImplementation::XmlImplementation(std::shared_ptr<const XmlNameTable> name_table)
    :
    _name_table( std::const_pointer_cast<XmlNameTable>(name_table) )
{
}

XmlImplementation::XmlImplementation(std::shared_ptr<XmlNameTable> name_table)
    :
    _name_table( name_table )
{
}

XmlImplementation::~XmlImplementation()
{
}

std::shared_ptr<XmlDocument> XmlImplementation::CreateDocument()
{
    // All created documents share the same XmlNameTable!
    return std::make_shared<XmlDocument>( _name_table );
}

std::shared_ptr<const XmlNameTable> XmlImplementation::NameTable() const
{
    return std::const_pointer_cast<const XmlNameTable>(_name_table);
}

std::shared_ptr<XmlNameTable> XmlImplementation::NameTable()
{
    return _name_table;
}

}