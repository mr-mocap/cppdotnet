#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Xml/Private/Utils.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>

namespace
{

std::string GenerateOuterXml(std::string_view local_name)
{
    return std::format( "{}=\"\"", local_name );
}

std::string GenerateOuterXml(std::string_view local_name, std::string_view value)
{
    return std::format( "{}={}", local_name, System::Xml::Private::Utils::Quote( value ) );
}

}

namespace System::Xml
{

XmlAttribute::XmlAttribute(std::string_view prefix,
                           std::string_view local_name,
                           std::string_view namespace_uri,
                           std::shared_ptr<XmlDocument> document)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>(),
             NodeConstructionParameters{ .local_name    = local_name,
                                         .name          = local_name,
                                         .namespace_uri = namespace_uri,
                                         .outer_xml     = GenerateOuterXml( local_name ),
                                         .prefix        = prefix,
                                         .owner_document = document }
           )
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

std::shared_ptr<XmlText> XmlAttribute::AppendChild(std::shared_ptr<XmlText> new_child)
{
    if ( HasChildNodes() )
        ThrowWithTarget( InvalidOperationException("Attribute node can have only a single child") );

    XmlNode::AppendChild( std::static_pointer_cast<XmlNode>(new_child) );
    Value( new_child->Data() );
    return new_child;
}

std::shared_ptr<XmlText> XmlAttribute::PrependChild(std::shared_ptr<XmlText> new_child)
{
    if ( HasChildNodes() )
        ThrowWithTarget( InvalidOperationException("Attribute node can have only a single child") );

    XmlNode::PrependChild( std::static_pointer_cast<XmlNode>(new_child) );
    Value( new_child->Data() );
    return new_child;
}

std::shared_ptr<XmlNode> XmlAttribute::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlAttribute>( *this );
    else
        return std::make_shared<XmlAttribute>( *this );
}

std::string_view XmlAttribute::Value() const
{
    return _value;
}

void XmlAttribute::Value(std::string_view new_value)
{
    if ( !OwnerDocument() )
        ThrowWithTarget( InvalidOperationException("Attribute needs an OwnerDocument in order to set Value") );

    if ( HasChildNodes() )
    {
        ASSERT( ChildNodes().Count() == 1 );
        ASSERT( ChildNodes().Item( 0 )->NodeType() == XmlNodeType::Text );
    
        ChildNodes().Item( 0 )->Value( new_value );
        _updateValue( new_value );
    }
    else
    {
        // Add a Text node as a child...
        std::shared_ptr<XmlText> node = OwnerDocument()->CreateTextNode( new_value );

        AppendChild( node );
    }

    POSTCONDITION( ChildNodes().Count() == 1 );
    POSTCONDITION( ChildNodes().Item( 0 )->NodeType() == XmlNodeType::Text );
    POSTCONDITION( ChildNodes().Item( 0 )->Value() == new_value );
}

void XmlAttribute::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
    _clearValue();
}

std::shared_ptr<XmlNode> XmlAttribute::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    auto retval = children_as_derived_type->RemoveChild( old_child );

    if ( retval )
        _clearValue();
    return retval;
}

std::shared_ptr<XmlNode> XmlAttribute::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    auto retval = children_as_derived_type->ReplaceChild( new_child, old_child );

    _updateValue( new_child->Value() );
    return retval;
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

bool XmlAttribute::_canAddAsChild(std::shared_ptr<XmlNode> new_child) const
{
    XmlNodeType new_child_type = new_child->NodeType();

    return new_child_type == XmlNodeType::Text;
}

XmlNodeType XmlAttribute::_getNodeType() const
{
    return XmlNodeType::Attribute;
}

void XmlAttribute::_clearValue()
{
    _value.clear();
    _outer_xml = GenerateOuterXml( Name(), _value );
}

void XmlAttribute::_updateValue(std::string_view new_value)
{
    _value = new_value;
    _outer_xml = GenerateOuterXml( Name(), new_value );
}

}