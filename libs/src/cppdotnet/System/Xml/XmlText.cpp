#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>

namespace
{

std::string_view TextNodeName = "#text";

// NOTE: OuterXml == Data == Value
}

namespace System::Xml
{

XmlText::XmlText()
    :
    XmlCharacterData( nullptr, TextNodeName )
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );
}

XmlText::XmlText(std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( doc, TextNodeName )
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );
}

XmlText::XmlText(std::string_view data, std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( data, doc, TextNodeName )
{
    _outer_xml = data;

    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );
}

XmlText::XmlText(const XmlText &other)
    :
    XmlCharacterData( other )
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );
}

XmlText::XmlText(XmlText &&other)
    :
    XmlCharacterData( std::move( other ) )
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );
}

XmlText &XmlText::operator =(const XmlText &other)
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );

    XmlCharacterData::operator =( other );
    return *this;
}

XmlText &XmlText::operator =(XmlText &&other)
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );

    XmlCharacterData::operator =( std::move( other ) );
    return *this;
}

std::shared_ptr<XmlNode> XmlText::CloneNode(bool deep) const
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );

    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlText>( *this );
    else
        return std::make_shared<XmlText>( *this );
}

void XmlText::Value(std::string_view new_value)
{
    XmlCharacterData::Value( new_value );
    _outer_xml = new_value;

    INVARIANT( !HasChildNodes());
}

void XmlText::Data(std::string_view new_value)
{
    XmlCharacterData::Data( new_value );
    _outer_xml = new_value;

    INVARIANT( !HasChildNodes());
}

void XmlText::WriteTo(XmlWriter &xml_writer) const
{
    INVARIANT( !HasChildNodes());
    INVARIANT( _outer_xml == Data() );
    INVARIANT( _outer_xml == _value );

    xml_writer.WriteRaw( OuterXml() );
}

XmlNodeType XmlText::_getNodeType() const
{
    return XmlNodeType::Text;
}

}