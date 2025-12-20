#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cppdotnet/System/Xml/XmlAttributeCollection.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Exception.hpp>
#include <algorithm>


namespace
{

std::size_t CalculateLength(const System::Xml::XmlAttributeCollection &attributes)
{
    size_t length = 0;
    size_t count  = attributes.Count();

    for (size_t i = 0; i < count; ++i)
        length += attributes.Item( i )->OuterXml().size();
    
    length += std::max( count - 1, static_cast<size_t>(0) );  // Take care of the space BETWEEN the attributes
    return length;
}

std::string GenerateAttributesString(const System::Xml::XmlAttributeCollection &attributes)
{
    std::string retval;
    size_t      length = CalculateLength( attributes );

    retval.reserve( length );
    for (size_t i = 0, count = attributes.Count(); i < count; ++i)
    {
        std::shared_ptr<System::Xml::XmlNode> node = attributes.Item( i );

        if ( i > 0 )
            retval.append(" ");
        retval.append( node->OuterXml() );
    }
    return retval;
}

std::string GenerateOuterXml(std::string_view name)
{
    std::string retval;

    retval.reserve( name.size() + 4 );
    return retval.append("<").append(name).append(" />");
}

std::string GenerateOuterXml(      std::string_view                     name,
                             const System::Xml::XmlAttributeCollection &attributes)
{
    std::string retval;
    std::string attr_string = GenerateAttributesString( attributes );

    retval.reserve( name.size() + attr_string.size() + 4 ); // The 4 is: "<" + " />"

    // Build the string...
    return retval.append("<").append(name).append(" ").append(attr_string).append(" />");
}

std::string GenerateOuterXml(      std::string_view name,
                             const System::Xml::XmlAttributeCollection &attributes,
                                   std::string_view value)
{
    std::string retval;
    std::string attr_string = GenerateAttributesString( attributes );

    retval.append("<").append(name).append(" ").append(attr_string).append(">"); // The opening marker
    retval.append(value);
    retval.append("</").append(name).append(">"); // The closing marker
    return retval;
}

}

namespace System::Xml
{

XmlElement::XmlElement(std::string_view prefix,
                       std::string_view local_name,
                       std::string_view namespace_uri,
                       std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   NodeConstructionParameters{ .local_name    = local_name,
                                               .name          = local_name,
                                               .namespace_uri = namespace_uri,
                                               .outer_xml     = GenerateOuterXml( local_name ),
                                               .prefix        = prefix,
                                               .owner_document = document }
                   )
{
}

XmlElement::XmlElement(const XmlElement &other)
    :
    XmlLinkedNode( other._children->MemberwiseClone() ),
    _value( other._value )
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
    _clearValue();
}

std::shared_ptr<XmlNode> XmlElement::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    std::shared_ptr<XmlNode> removed_node = children_as_derived_type->RemoveChild( old_child );

    _updateValue( _generateValue() );
    return removed_node;
}

std::shared_ptr<XmlNode> XmlElement::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    std::shared_ptr<XmlNode> removed_node = children_as_derived_type->ReplaceChild( new_child, old_child );

    _updateValue( _generateValue() );
    return removed_node;
}

std::shared_ptr<XmlAttribute> XmlElement::GetAttributeNode(std::string_view name) const
{
    std::shared_ptr<XmlNode> attr_node = Attributes().GetNamedItem( name );

    return std::static_pointer_cast<XmlAttribute>( attr_node );
}

void XmlElement::SetAttributeNode(std::shared_ptr<XmlAttribute> new_attribute)
{
    _attributes.SetNamedItem( new_attribute );
    _updateOuterXml();
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
        ASSERT( attr_node->ChildNodes().Count() == 1 );
        ASSERT( attr_node->ChildNodes().Item( 0 )->NodeType() == XmlNodeType::Text );

        std::shared_ptr<XmlText> text = std::static_pointer_cast<XmlText>( attr_node->ChildNodes().Item( 0 ) );

        text->Data( value );
        _updateOuterXml();
        return;
    }

    if ( !OwnerDocument() )
        ThrowWithTarget( System::InvalidOperationException( "Cannot create new XmlAttribute without a valid XmlDocument" ) );

    attr_node = OwnerDocument()->CreateAttribute( name );

    attr_node->AppendChild( OwnerDocument()->CreateTextNode( value ) );
    SetAttributeNode( attr_node );
}

void XmlElement::RemoveAttribute(std::string_view name)
{
    _attributes.RemoveNamedItem( name );
    _updateOuterXml();
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

void XmlElement::_clearValue()
{
    _value.clear();
    _updateOuterXml();
}

void XmlElement::_updateValue(std::string_view new_value)
{
    _value = new_value;
    _updateOuterXml();
}

void XmlElement::_updateOuterXml()
{
    if ( Value().empty() )
        _outer_xml = GenerateOuterXml( Name(), Attributes() );
    else
        _outer_xml = GenerateOuterXml( Name(), Attributes(), Value() );
}

std::string XmlElement::_generateValue() const
{
    std::string        new_value;
    const XmlNodeList &children = ChildNodes();

    for (size_t i = 0, count = children.Count(); i < count; ++i)
    {
        new_value.append( children.Item( i )->OuterXml() );
    }
    return new_value;
}

}