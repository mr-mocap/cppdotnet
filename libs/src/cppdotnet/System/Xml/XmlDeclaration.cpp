#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Private/private.hpp>

namespace System::Xml
{

XmlDeclaration::XmlDeclaration()
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _value( std::format("version=\"{}\"", _version) )
{
}

XmlDeclaration::XmlDeclaration(std::string_view version, std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _version( version ),
    _owner_document( document ),
    _value( std::format("version=\"{}\"", version) )
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
    _value( std::format("version=\"{}\" encoding=\"{}\"", version, encoding) )
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
    _value( std::format("version=\"{}\" encoding=\"{}\" standalone=\"{}\"", version, encoding, standalone) )
{   
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
    std::string text = std::format("version=\"{}\"", Version());

    if ( !Encoding().empty() )
        text += std::format(" encoding=\"{}\"", Encoding());
    if ( !Standalone().empty() )
        text += std::format(" standalone=\"{}\"", Standalone());

    xml_writer.WriteProcessingInstruction( LocalName(), text);

    POSTCONDITION( xml_writer.WriteState() == Xml::WriteState::Prolog );
}

XmlNodeType XmlDeclaration::_getNodeType() const
{
    return XmlNodeType::XmlDeclaration;
}

}