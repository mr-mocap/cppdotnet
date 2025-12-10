#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>

namespace System::Xml
{

XmlText::XmlText(std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( doc, "#text" )
{
    INVARIANT( !HasChildNodes());
}

XmlText::XmlText(std::string_view data, std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( data, doc, "#text" )
{
    INVARIANT( !HasChildNodes());
}

XmlText::XmlText(const XmlText &other)
    :
    XmlCharacterData( other )
{
    INVARIANT( !HasChildNodes());
}

XmlText::XmlText(XmlText &&other)
    :
    XmlCharacterData( std::move( other ) )
{
    INVARIANT( !HasChildNodes());
}

XmlText &XmlText::operator =(const XmlText &other)
{
    INVARIANT( !HasChildNodes());

    XmlCharacterData::operator =( other );
    return *this;
}

XmlText &XmlText::operator =(XmlText &&other)
{
    XmlCharacterData::operator =( std::move( other ) );
    return *this;
}

std::shared_ptr<XmlNode> XmlText::CloneNode(bool deep) const
{
    INVARIANT( !HasChildNodes());

    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlText>( *this );
    else
        return std::make_shared<XmlText>( *this );
}

void XmlText::WriteTo(XmlWriter &xml_writer) const
{
    INVARIANT( !HasChildNodes());

    Nullable<std::string> value = Value();

    if ( value.HasValue() )
        xml_writer.WriteRaw( value.Value() );
}

XmlNodeType XmlText::_getNodeType() const
{
    return XmlNodeType::Text;
}

}