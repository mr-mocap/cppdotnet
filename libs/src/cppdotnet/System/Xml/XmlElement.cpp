#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cppdotnet/System/Xml/XmlAttributeCollection.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Exception.hpp>

namespace System::Xml
{

XmlElement::XmlElement(std::string_view prefix,
                       std::string_view local_name,
                       std::string_view namespace_uri,
                       std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   local_name,
                   local_name,
                   namespace_uri,
                   prefix,
                   document )
{
}

XmlElement::XmlElement(const XmlElement &other)
    :
    XmlLinkedNode( other._children->MemberwiseClone() )
{
}

XmlElement::XmlElement(XmlElement &&other)
    :
    XmlLinkedNode( std::move( other._children ) ),
    _value( std::move( other._value ) )
{
}

XmlElement &XmlElement::operator =(const XmlElement &other)
{
    XmlLinkedNode::operator =( other );
    if ( this != &other )
    {
        _value = other._value;
    }
    return *this;
}

XmlElement &XmlElement::operator =(XmlElement &&other)
{
    XmlLinkedNode::operator =( std::move( other ) );
    _value = std::move( other._value );
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

std::string_view XmlElement::Value() const
{
    return _value;
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

std::shared_ptr<XmlAttribute> XmlElement::GetAttributeNode(std::string_view name) const
{
    std::shared_ptr<XmlNode> attr_node = Attributes().GetNamedItem( name );

    return std::static_pointer_cast<XmlAttribute>( attr_node );
}

void XmlElement::SetAttributeNode(std::shared_ptr<XmlAttribute> new_attribute)
{
    _attributes.SetNamedItem( new_attribute );
}

std::string_view XmlElement::GetAttribute(std::string_view name) const
{
    std::shared_ptr<XmlAttribute> attr_node = GetAttributeNode( name );

    if ( attr_node )
        return attr_node->Value();

    return { };
}

void XmlElement::SetAttribute(std::string_view name, std::string_view value)
{
    std::shared_ptr<XmlAttribute> attr_node = GetAttributeNode( name );

    if ( attr_node )
    {
        std::static_pointer_cast<XmlNode>(attr_node)->Value( value );
        return;
    }

    if ( !OwnerDocument() )
        ThrowWithTarget( System::InvalidOperationException( "Cannot create new XmlAttribute without a valid XmlDocument" ) );

    attr_node = OwnerDocument()->CreateAttribute(name);
    std::static_pointer_cast<XmlNode>(attr_node)->Value( value );
    _attributes.SetNamedItem( attr_node );
}

void XmlElement::RemoveAttribute(std::string_view name)
{
    _attributes.RemoveNamedItem( name );
}

void XmlElement::WriteTo(XmlWriter &xml_writer) const
{
    XmlNodeList &children = ChildNodes();

    if ( children.Count() == 0 )
    {
        xml_writer.WriteStartElement( LocalName() );
        _writeAttributes( xml_writer );
        xml_writer.WriteRaw( " />" );
    }
    else
    {
        xml_writer.WriteRaw( std::format("<{}", LocalName()) );
        _writeAttributes( xml_writer );
        xml_writer.WriteRaw( ">" );

        _writeChildren( xml_writer );
        
        xml_writer.WriteRaw( std::format("</{}>", LocalName()) );
    }
}

bool XmlElement::_thisNodeCanHaveChildren() const
{
    return true;
}

XmlNodeType XmlElement::_getNodeType() const
{
    return XmlNodeType::Element;
}

void XmlElement::_writeAttributes(XmlWriter &xml_writer) const
{
    const XmlAttributeCollection &attributes = Attributes();

    for (size_t a = 0; a < attributes.Count(); ++a)
        attributes.Item( a )->WriteTo( xml_writer );
}

void XmlElement::_writeChildren(XmlWriter &xml_writer) const
{
    for (int i = 0; i < ChildNodes().Count(); ++i)
        ChildNodes()[ i ]->WriteTo( xml_writer );
}

bool XmlElement::_canAddAsChild(std::shared_ptr<XmlNode> new_child) const
{
    XmlNodeType new_child_type = new_child->NodeType();

    return new_child_type == XmlNodeType::Element ||
           new_child_type == XmlNodeType::Text    ||
           new_child_type == XmlNodeType::CDATA   ||
           new_child_type == XmlNodeType::Comment ||
           new_child_type == XmlNodeType::ProcessingInstruction ||
           new_child_type == XmlNodeType::Whitespace;
}

}