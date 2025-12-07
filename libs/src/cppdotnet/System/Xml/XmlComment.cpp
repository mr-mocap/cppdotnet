#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <format>

namespace System::Xml
{


XmlComment::XmlComment(std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( doc, "#comment" )
{
}

XmlComment::XmlComment(std::string_view comment, std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( comment, doc, "#comment" )
{
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

void XmlComment::WriteTo(XmlWriter &xml_writer) const
{
    Nullable<std::string> value = Value();

    if ( xml_writer.WriteState() == Xml::WriteState::Start )
        xml_writer.WriteStartDocument();

    Xml::WriteState before_write_state = xml_writer.WriteState();

    xml_writer.WriteRaw( std::format( "<!--{}-->", value.GetValueOrDefault() ) );

    POSTCONDITION( xml_writer.WriteState() == before_write_state );
}

XmlNodeType XmlComment::_getNodeType() const
{
    return XmlNodeType::Comment;
}

}