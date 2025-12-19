#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <format>


namespace
{

std::string_view CommentNodeName = "#comment";

std::string GenerateOuterXml(std::string_view comment)
{
    return std::format( "<!--{}-->", comment );
}

}

namespace System::Xml
{

XmlComment::XmlComment(std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( doc, CommentNodeName )
{
    _outer_xml = GenerateOuterXml( _value );
}

XmlComment::XmlComment(std::string_view comment, std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( comment, doc, CommentNodeName )
{
    _outer_xml = GenerateOuterXml( _value );
}

XmlComment::XmlComment(const XmlComment &other)
    :
    XmlCharacterData( other )
{
}

XmlComment::XmlComment(XmlComment &&other)
    :
    XmlCharacterData( std::move( other ) )
{
}

XmlComment &XmlComment::operator =(const XmlComment &other)
{
    XmlCharacterData::operator =( other );
    return *this;
}

XmlComment &XmlComment::operator =(XmlComment &&other)
{
    XmlCharacterData::operator =( std::move( other ) );
    return *this;
}

std::shared_ptr<XmlNode> XmlComment::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlComment>( *this );
    else
        return std::make_shared<XmlComment>( *this );
}

void XmlComment::Value(std::string_view new_value)
{
    XmlCharacterData::Value( new_value );
    _outer_xml = GenerateOuterXml( new_value );
}

void XmlComment::Data(std::string_view new_value)
{
    XmlCharacterData::Data( new_value );
    _outer_xml = GenerateOuterXml( new_value );
}

void XmlComment::WriteTo(XmlWriter &xml_writer) const
{
    Nullable<std::string> value = Value();

    if ( xml_writer.WriteState() == Xml::WriteState::Start )
        xml_writer.WriteStartDocument();

    Xml::WriteState  before_write_state = xml_writer.WriteState();
    std::string_view data_to_write = OuterXml();

    xml_writer.WriteRaw( data_to_write );

    POSTCONDITION( xml_writer.WriteState() == before_write_state );
}

XmlNodeType XmlComment::_getNodeType() const
{
    return XmlNodeType::Comment;
}

}