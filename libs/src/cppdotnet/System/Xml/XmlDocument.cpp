#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cppdotnet/System/Xml/NameTable.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Private/private.hpp>

namespace System::Xml
{

XmlDocument::XmlDocument(const XmlNameTable &name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _name_table( name_table.MemberwiseClone() )
{
}

XmlDocument::XmlDocument(std::unique_ptr<XmlNameTable> &&name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _name_table( std::move(name_table) )
{
    INVARIANT( _name_table );
}

XmlDocument::XmlDocument(std::shared_ptr<XmlNameTable> &name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _name_table( name_table )
{
    INVARIANT( _name_table );
}

XmlDocument::XmlDocument(const std::shared_ptr<XmlNameTable> &name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _name_table( name_table )
{
    INVARIANT( _name_table );
}

XmlDocument::XmlDocument(std::shared_ptr<XmlNameTable> &&name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _name_table( std::move(name_table) )
{
    INVARIANT( _name_table );
}

XmlDocument::XmlDocument()
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _name_table( std::make_shared<System::Xml::NameTable>() )
{
    INVARIANT( _name_table );
}

std::shared_ptr<XmlNode> XmlDocument::CloneNode(bool deep) const
{
    if ( deep )
    {
        return std::make_shared<XmlDocument>( _name_table->MemberwiseClone() );
    }
    else
    {
        return std::make_shared<XmlDocument>( _name_table );
    }
}

std::shared_ptr<XmlAttribute> XmlDocument::CreateAttribute(std::string_view name)
{
    size_t has_colon = name.find( ':' );
    std::string_view prefix;

    if ( has_colon != std::string_view::npos )
    {
        // Check for a ':', but has nothing before it
        if ( has_colon > 0 )
            prefix = name.substr( 0, has_colon + 1 );
    }
    std::string_view local_name = (has_colon == std::string_view::npos) ? name : name.substr( has_colon + 1 );

    return std::make_shared<XmlAttribute>( prefix,
                                           local_name,
                                           std::string_view(),
                                           _localSharedFromThis()
                                         );
}

std::string_view XmlDocument::LocalName() const
{
    return "XmlDocument::LocalName() Not Implemented!";
}

std::string_view XmlDocument::Name() const
{
    return "XmlDocument::Name() Not Implemented!";
}

std::string_view XmlDocument::NamespaceURI() const
{
    return "XmlDocument::NamespaceURI() Not Implemented!";
}

std::shared_ptr<XmlDocument> XmlDocument::OwnerDocument() const
{
    return nullptr;
}

std::string_view XmlDocument::Prefix() const
{
    return "XmlDocument::Prefix() NOT IMPLEMENTED";
}

void XmlDocument::Prefix(std::string_view new_prefix)
{
    UNUSED( new_prefix );
}

void XmlDocument::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlDocument::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlDocument::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

Nullable<std::string> XmlDocument::Value() const
{
    return { };
}

XmlNodeType XmlDocument::_getNodeType() const
{
    return XmlNodeType::Document;
}

std::shared_ptr<XmlDocument> XmlDocument::_localSharedFromThis()
{
    // Downcast the XmlNode * to an XmlDocument *, since we KNOW we
    // have an XmlDocument *.
    return std::static_pointer_cast<XmlDocument>( shared_from_this() );
}

}