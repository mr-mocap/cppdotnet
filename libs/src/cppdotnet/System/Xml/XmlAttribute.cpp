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
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>(),
             local_name,
             local_name,
             namespace_uri,
             prefix,
             document )
{
}

XmlAttribute::XmlAttribute(const XmlAttribute &other)
    :
    XmlNode( other ),
    _value( other._value )
{
}

XmlAttribute::XmlAttribute(XmlAttribute &&other)
    :
    XmlNode( std::move( other ) ),
    _value( std::move( other._value ) )
{
}

XmlAttribute &XmlAttribute::operator =(const XmlAttribute &other)
{
    XmlNode::operator =( other );
    if ( this != &other )
    {
        _value = other._value;
    }
    return *this;
}

XmlAttribute &XmlAttribute::operator =(XmlAttribute &&other)
{
    XmlNode::operator =( std::move( other ) );
    _value = std::move( other._value );
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

Nullable<std::string> XmlAttribute::Value() const
{
    return _value;
}

void XmlAttribute::Value(Nullable<std::string> new_value)
{
    _value = new_value;
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