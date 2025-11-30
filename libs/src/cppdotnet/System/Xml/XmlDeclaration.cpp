#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Private/private.hpp>
#include <cppdotnet/System/Xml/Private/Utils.hpp>
#include <format>

namespace System::Xml
{

XmlDeclaration::XmlDeclaration()
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _value{ std::format("version={}", Private::Utils::Quote(_version)) }
{
}

XmlDeclaration::XmlDeclaration(std::string_view version, std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _version( version ),
    _owner_document( document ),
    _value{ std::format("version={}", Private::Utils::Quote(version)) }
{
}

XmlDeclaration::XmlDeclaration(std::string_view version,
                               std::string_view encoding,
                               std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _version( version ),
    _encoding( encoding ),
    _owner_document( document ),
    _value{ std::format("version={} encoding={}", Private::Utils::Quote(version), Private::Utils::Quote(encoding)) }
{
}

XmlDeclaration::XmlDeclaration(std::string_view version,
                               std::string_view encoding,
                               std::string_view standalone,
                               std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _version( version ),
    _encoding( encoding ),
    _standalone( standalone ),
    _owner_document( document ),
    _value{ std::format("version={} encoding={} standalone={}", Private::Utils::Quote(version), Private::Utils::Quote(encoding), Private::Utils::Quote(standalone)) }
{
    POSTCONDITION( _standalone == "yes" || _standalone == "no" );
}

XmlDeclaration::XmlDeclaration(const XmlDeclaration &other)
    :
    XmlLinkedNode( other._children->MemberwiseClone() ),
    _version( other._version ),
    _encoding( other._encoding ),
    _standalone( other._standalone ),
    _owner_document( other._owner_document ),
    _value( other._value )
{
}

XmlDeclaration &XmlDeclaration::operator =(const XmlDeclaration &other)
{
    if (this != &other)
    {
        _version        = other._version;
        _encoding       = other._encoding;
        _standalone     = other._standalone;
        _owner_document = other._owner_document;
        _value          = other._value;
    }
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

std::string_view XmlDeclaration::LocalName() const
{
    return "xml";
}

std::string_view XmlDeclaration::Name() const
{
    return LocalName();
}

std::string_view XmlDeclaration::NamespaceURI() const
{
    // TODO: Return proper namespace URI!
    return { };
}

std::shared_ptr<XmlDocument> XmlDeclaration::OwnerDocument() const
{
    return _owner_document;
}

std::string_view XmlDeclaration::Prefix() const
{
    // TODO: FIXME
    return { };
}

void XmlDeclaration::Prefix(std::string_view new_prefix)
{
    UNUSED( new_prefix );
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

Nullable<std::string> XmlDeclaration::Value() const
{
    PRECONDITION( !Version().empty() );

    return { _value };
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