#include <cppdotnet/System/Xml/XmlWhitespace.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <cctype>
#include <algorithm>
#include <ranges>

namespace
{

bool IsWhitespace(char c)
{
    return std::isspace( static_cast<unsigned char>(c) );
}

bool IsAllWhitespace(std::string_view input)
{
    return std::ranges::all_of( input, IsWhitespace );
}

}

namespace System::Xml
{

XmlWhitespace::XmlWhitespace(std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( doc, "#whitespace" )
{
}

XmlWhitespace::XmlWhitespace(std::string_view comment, std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( comment, doc, "#whitespace" )
{
    bool all_valid = IsAllWhitespace( _value.Value() );

    if ( !all_valid )
        ThrowWithTarget( InvalidOperationException( "Cannot construct XmlWhitespace with non-whitespace characters" ) );

    POSTCONDITION( _value.HasValue() );
    POSTCONDITION( IsAllWhitespace( _value.Value() ) );
}

XmlWhitespace::XmlWhitespace(const XmlWhitespace &other)
    :
    XmlCharacterData( other )
{
}

XmlWhitespace::XmlWhitespace(XmlWhitespace &&other)
    :
    XmlCharacterData( std::move( other ) )
{
}

XmlWhitespace &XmlWhitespace::operator =(const XmlWhitespace &other)
{
    XmlCharacterData::operator =( other );
    return *this;
}

XmlWhitespace &XmlWhitespace::operator =(XmlWhitespace &&other)
{
    XmlCharacterData::operator =( std::move( other ) );
    return *this;
}

std::shared_ptr<XmlNode> XmlWhitespace::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlWhitespace>( *this );
    else
        return std::make_shared<XmlWhitespace>( *this );
}

void XmlWhitespace::WriteTo(XmlWriter &xml_writer) const
{
    Nullable<std::string> value = Value();

    if ( xml_writer.WriteState() == Xml::WriteState::Start )
        xml_writer.WriteStartDocument();

    Xml::WriteState before_write_state = xml_writer.WriteState();

    Nullable<std::string> data = Data();

    if ( data.HasValue() )
    {
        xml_writer.WriteRaw( data.Value() );
    }

    POSTCONDITION( xml_writer.WriteState() == before_write_state );
}

XmlNodeType XmlWhitespace::_getNodeType() const
{
    return XmlNodeType::Whitespace;
}

}