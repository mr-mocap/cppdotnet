#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>

namespace System::Xml
{

XmlAttribute::XmlAttribute(std::string_view prefix,
                           std::string_view local_name,
                           std::string_view namespace_uri,
                           std::shared_ptr<XmlDocument> document)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _prefix( prefix ),
    _local_name( local_name ),
    _namespace_uri( namespace_uri ),
    _owner_document( document )
{
}

XmlAttribute::XmlAttribute(const XmlAttribute &other)
    :
    XmlNode( other._children->MemberwiseClone() ),
    _prefix( other._prefix ),
    _local_name( other._local_name ),
    _namespace_uri( other._namespace_uri ),
    _owner_document( other._owner_document )
{
}

XmlAttribute &XmlAttribute::operator =(const XmlAttribute &other)
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

std::shared_ptr<XmlNode> XmlAttribute::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlAttribute>( *this );
    else
        return std::make_shared<XmlAttribute>( *this );
}

std::string_view XmlAttribute::LocalName() const
{
    return _local_name;
}

std::string_view XmlAttribute::Name() const
{
    return _local_name;
}

std::string_view XmlAttribute::NamespaceURI() const
{
    return _namespace_uri;
}

std::shared_ptr<XmlDocument> XmlAttribute::OwnerDocument() const
{
    return _owner_document;
}

Nullable<std::string> XmlAttribute::Value() const
{
    return _value;
}

void XmlAttribute::Value(Nullable<std::string> new_value)
{
    _value = new_value;
}

std::string_view XmlAttribute::Prefix() const
{
    return _prefix;
}

void XmlAttribute::Prefix(std::string_view new_prefix)
{
    _prefix = new_prefix;
}

void XmlAttribute::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlAttribute::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlAttribute::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

void XmlAttribute::WriteTo(XmlWriter &xml_writer) const
{
    UNUSED( xml_writer );

    //xml_writer.WriteRaw( std::format(" {}={}", LocalName(), Value()) );
    assert( false );
}

bool XmlAttribute::_thisNodeCanHaveChildren() const
{
    return true;
}

XmlNodeType XmlAttribute::_getNodeType() const
{
    return XmlNodeType::Attribute;
}

}