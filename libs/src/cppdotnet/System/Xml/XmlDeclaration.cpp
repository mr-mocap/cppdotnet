#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>
#include <cppdotnet/System/Xml/Private/Utils.hpp>
#include <format>

namespace System::Xml
{

XmlDeclaration::XmlDeclaration()
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   "xml",
                   "xml",
                   std::string_view{ },
                   std::string_view{ },
                   nullptr ),
    _value( std::format("version={}", Private::Utils::Quote(_version)) )
{
}

XmlDeclaration::XmlDeclaration(std::string_view version, std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   "xml",
                   "xml",
                   std::string_view{ },
                   std::string_view{ },
                   document ),
    _version( version ),
    _value( std::format("version={}", Private::Utils::Quote(_version)) )
{
}

XmlDeclaration::XmlDeclaration(std::string_view version,
                               std::string_view encoding,
                               std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   "xml",
                   "xml",
                   std::string_view{ },
                   std::string_view{ },
                   document ),
    _version( version ),
    _encoding( encoding ),
    _value( std::format("version={} encoding={}", Private::Utils::Quote(_version), Private::Utils::Quote(_encoding)) )
{
}

XmlDeclaration::XmlDeclaration(std::string_view version,
                               std::string_view encoding,
                               std::string_view standalone,
                               std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   "xml",
                   "xml",
                   std::string_view{ },
                   std::string_view{ },
                   document ),
    _version( version ),
    _encoding( encoding ),
    _standalone( standalone ),
    _value{ std::format("version={} encoding={} standalone={}",
            Private::Utils::Quote(_version),
            Private::Utils::Quote(_encoding),
            Private::Utils::Quote(_standalone)) }
{
    POSTCONDITION( _standalone == "yes" || _standalone == "no" );
}

XmlDeclaration::XmlDeclaration(const XmlDeclaration &other)
    :
    XmlLinkedNode( other ),
    _version( other._version ),
    _encoding( other._encoding ),
    _standalone( other._standalone ),
    _value( other._value )
{
}

XmlDeclaration::XmlDeclaration(XmlDeclaration &&other)
    :
    XmlLinkedNode( std::move(other) ),
    _version( std::move(other._version) ),
    _encoding( std::move(other._encoding) ),
    _standalone( std::move(other._standalone) ),
    _value( std::move(other._value) )
{
}

XmlDeclaration &XmlDeclaration::operator =(const XmlDeclaration &other)
{
    XmlLinkedNode::operator =( other );
    if (this != &other)
    {
        _version        = other._version;
        _encoding       = other._encoding;
        _standalone     = other._standalone;
        _value          = other._value;
    }
    return *this;
}

XmlDeclaration &XmlDeclaration::operator =(XmlDeclaration &&other)
{
    XmlLinkedNode::operator =( std::move( other ) );
    _version    = std::move( other._version );
    _encoding   = std::move( other._encoding );
    _standalone = std::move( other._standalone );
    _value      = std::move( other._value );
    return *this;
}

std::shared_ptr<XmlNode> XmlDeclaration::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlDeclaration>( *this );
    else
        return std::make_shared<XmlDeclaration>( *this );
}

void XmlDeclaration::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlDeclaration::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlDeclaration::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

std::string_view XmlDeclaration::Value() const
{
    PRECONDITION( !Version().empty() );

    return _value;
}

void XmlDeclaration::Value(std::string_view new_value)
{
    _value = new_value;
}

void XmlDeclaration::WriteTo(XmlWriter &xml_writer) const
{
    // Check for invalid state(s)
    if ( xml_writer.WriteState() != Xml::WriteState::Start )
        ThrowWithTarget( ArgumentException("XML Declaration has already been written") );

    // We are at the start state, so we can write the XML Declaration
    std::string text = std::format("<?{} version={}", LocalName(), Private::Utils::Quote( Version() ));

    if ( !Encoding().empty() )
        text += std::format(" encoding={}", Private::Utils::Quote( Encoding() ));
    if ( !Standalone().empty() )
        text += std::format(" standalone={}", Private::Utils::Quote( Standalone() ));

    text += "?>";
    bool omit_xml_declaration = xml_writer.Settings().OmitXmlDeclaration();

    xml_writer.Settings().OmitXmlDeclaration( true );

    ASSERT( xml_writer.WriteState() == Xml::WriteState::Start );
    ASSERT( xml_writer.Settings().OmitXmlDeclaration() == true );

    xml_writer.WriteStartDocument(); // Should write nothing because we set OmitXmlDeclaration to true
    xml_writer.Settings().OmitXmlDeclaration( omit_xml_declaration ); // Restore previous setting

    xml_writer.WriteRaw( text ); // Manually write the XML declaration

    POSTCONDITION( xml_writer.WriteState() == Xml::WriteState::Prolog );
}

XmlNodeType XmlDeclaration::_getNodeType() const
{
    return XmlNodeType::XmlDeclaration;
}

}