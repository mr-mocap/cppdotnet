#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>

namespace System::Xml
{

XmlText::XmlText(std::string_view data, std::shared_ptr<XmlDocument> doc)
    :
    XmlCharacterData( data, doc )
{
}

std::shared_ptr<XmlNode> XmlText::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlText>( *this );
    else
        return std::make_shared<XmlText>( *this );
}

std::string_view XmlText::LocalName() const
{
    return _local_name;
}

std::string_view XmlText::Name() const
{
    return _local_name;
}

std::string_view XmlText::NamespaceURI() const
{
    return _namespace_uri;
}

std::string_view XmlText::Prefix() const
{
    return _prefix;
}

void XmlText::Prefix(std::string_view new_prefix)
{
    _prefix = new_prefix;
}

void XmlText::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlText::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlText::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

void XmlText::WriteTo(XmlWriter &xml_writer) const
{
    Nullable<std::string> value = Value();

    if ( value.HasValue() )
        xml_writer.WriteRaw( value.Value() );
}

XmlNodeType XmlText::_getNodeType() const
{
    return XmlNodeType::Text;
}

}