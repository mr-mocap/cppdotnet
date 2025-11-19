#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>

namespace System::Xml
{

XmlElement::XmlElement(std::string_view prefix,
                           std::string_view local_name,
                           std::string_view namespace_uri,
                           std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _prefix( prefix ),
    _local_name( local_name ),
    _namespace_uri( namespace_uri ),
    _owner_document( document )
{
}

XmlElement::XmlElement(const XmlElement &other)
    :
    XmlLinkedNode( other._children->MemberwiseClone() ),
    _prefix( other._prefix ),
    _local_name( other._local_name ),
    _namespace_uri( other._namespace_uri ),
    _owner_document( other._owner_document )
{
}

XmlElement &XmlElement::operator =(const XmlElement &other)
{
    if ( this != &other )
    {
        _prefix = other._prefix;
        _local_name = other._local_name;
        _namespace_uri = other._namespace_uri;
        _owner_document = other._owner_document;
    }
    return *this;
}

std::shared_ptr<XmlNode> XmlElement::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlElement>( *this );
    else
        return std::make_shared<XmlElement>( *this );
}

std::string_view XmlElement::LocalName() const
{
    return _local_name;
}

std::string_view XmlElement::Name() const
{
    return "XmlElement::Name() NOT IMPLEMENTED";
}

std::string_view XmlElement::NamespaceURI() const
{
    return _namespace_uri;
}

std::shared_ptr<const XmlDocument> XmlElement::OwnerDocument() const
{
    return _owner_document;
}

std::shared_ptr<XmlDocument> XmlElement::OwnerDocument()
{
    return _owner_document;
}

Nullable<std::string> XmlElement::Value() const
{
    return { _value };
}

std::string_view XmlElement::Prefix() const
{
    return _prefix;
}

void XmlElement::Prefix(std::string_view new_prefix)
{
    _prefix = new_prefix;
}

void XmlElement::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlElement::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlElement::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

XmlNodeType XmlElement::_getNodeType() const
{
    return XmlNodeType::Element;
}

}