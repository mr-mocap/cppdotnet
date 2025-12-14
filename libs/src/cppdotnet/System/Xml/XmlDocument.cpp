#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/XmlAttribute.hpp>
#include <cppdotnet/System/Xml/XmlElement.hpp>
#include <cppdotnet/System/Xml/XmlText.hpp>
#include <cppdotnet/System/Xml/XmlComment.hpp>
#include <cppdotnet/System/Xml/XmlDeclaration.hpp>
#include <cppdotnet/System/Xml/XmlDocumentType.hpp>
#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
#include <cppdotnet/System/Xml/XmlWhitespace.hpp>
#include <cppdotnet/System/Xml/NameTable.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>

namespace System::Xml
{

XmlDocument::XmlDocument()
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _implementation( std::make_shared<XmlImplementation>() )
{
    INVARIANT( _implementation );
}

XmlDocument::XmlDocument(std::shared_ptr<XmlImplementation> implementation)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _implementation( implementation )
{
    INVARIANT( _implementation );
}

XmlDocument::XmlDocument(const XmlNameTable &name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _implementation( std::make_shared<XmlImplementation>( name_table.MemberwiseClone() ) )
{
    INVARIANT( _implementation );
}

XmlDocument::XmlDocument(std::unique_ptr<XmlNameTable> &&name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _implementation( std::make_shared<XmlImplementation>( std::move( name_table ) ) )
{
    INVARIANT( _implementation );
}

XmlDocument::XmlDocument(std::shared_ptr<XmlNameTable> &name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _implementation( std::make_shared<XmlImplementation>( name_table ) )
{
    INVARIANT( _implementation );
}

XmlDocument::XmlDocument(const std::shared_ptr<XmlNameTable> &name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _implementation( std::make_shared<XmlImplementation>( name_table ) )
{
    INVARIANT( _implementation );
}

XmlDocument::XmlDocument(std::shared_ptr<XmlNameTable> &&name_table)
    :
    XmlNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _implementation( std::make_shared<XmlImplementation>( name_table ) )
{
    INVARIANT( _implementation );
}

std::shared_ptr<XmlNode> XmlDocument::CloneNode(bool deep) const
{
    INVARIANT( _implementation );

    if ( deep )
    {
        return std::make_shared<XmlDocument>( _implementation->NameTable()->MemberwiseClone() );
    }
    else
    {
        return std::make_shared<XmlDocument>( _implementation->NameTable() );
    }
}

std::shared_ptr<XmlAttribute> XmlDocument::CreateAttribute(std::string_view prefix,
                                                           std::string_view local_name,
                                                           std::string_view namespace_uri)
{
    return std::make_shared<XmlAttribute>( prefix, local_name, namespace_uri, _localSharedFromThis() );
}

std::shared_ptr<XmlAttribute> XmlDocument::CreateAttribute(std::string_view local_name,
                                                           std::string_view namespace_uri)
{
    return CreateAttribute( std::string_view(), local_name, namespace_uri );
}

std::shared_ptr<XmlAttribute> XmlDocument::CreateAttribute(std::string_view name)
{
    INVARIANT( _implementation );

    size_t has_colon = name.find( ':' );
    std::string_view prefix;

    if ( has_colon != std::string_view::npos )
    {
        // Check for a ':', but has nothing before it
        if ( has_colon > 0 )
            prefix = name.substr( 0, has_colon + 1 );
    }
    std::string_view local_name = (has_colon == std::string_view::npos) ? name : name.substr( has_colon + 1 );

    return CreateAttribute( prefix, local_name, std::string_view() );
}

std::shared_ptr<XmlElement> XmlDocument::CreateElement(std::string_view prefix,
                                                       std::string_view local_name,
                                                       std::string_view namespace_uri)
{
    return std::make_shared<XmlElement>( prefix, local_name, namespace_uri, _localSharedFromThis() );
}

std::shared_ptr<XmlElement> XmlDocument::CreateElement(std::string_view local_name,
                                                       std::string_view namespace_uri)
{
    return CreateElement( std::string_view(), local_name, namespace_uri );
}

std::shared_ptr<XmlElement> XmlDocument::CreateElement(std::string_view name)
{
    INVARIANT( _implementation );

    size_t has_colon = name.find( ':' );
    std::string_view prefix;

    if ( has_colon != std::string_view::npos )
    {
        // Check for a ':', but has nothing before it
        if ( has_colon > 0 )
            prefix = name.substr( 0, has_colon + 1 );
    }
    std::string_view local_name = (has_colon == std::string_view::npos) ? name : name.substr( has_colon + 1 );

    return CreateElement( prefix, local_name, std::string_view() );
}

std::shared_ptr<XmlText> XmlDocument::CreateTextNode(std::string_view text)
{
    return std::make_shared<XmlText>( text, _localSharedFromThis() );
}

std::shared_ptr<XmlDeclaration> XmlDocument::CreateXmlDeclaration(std::string_view version)
{
    return std::make_shared<XmlDeclaration>( version, _localSharedFromThis() );
}

std::shared_ptr<XmlDeclaration> XmlDocument::CreateXmlDeclaration(std::string_view version,
                                                                  std::string_view encoding)
{
    return std::make_shared<XmlDeclaration>( version, encoding, _localSharedFromThis() );
}

std::shared_ptr<XmlDeclaration> XmlDocument::CreateXmlDeclaration(std::string_view version,
                                                                  std::string_view encoding,
                                                                  std::string_view standalone)
{
    return std::make_shared<XmlDeclaration>( version, encoding, standalone, _localSharedFromThis() );
}

std::shared_ptr<XmlProcessingInstruction> XmlDocument::CreateProcessingInstruction(std::string_view target)
{
    return std::make_shared<XmlProcessingInstruction>( target, _localSharedFromThis() );
}

std::shared_ptr<XmlProcessingInstruction> XmlDocument::CreateProcessingInstruction(std::string_view target,
                                                                                   std::string_view data)
{
    return std::make_shared<XmlProcessingInstruction>( target, data, _localSharedFromThis() );
}

std::shared_ptr<XmlComment> XmlDocument::CreateComment(std::string_view data)
{
    return std::make_shared<XmlComment>( data, _localSharedFromThis() );
}

std::shared_ptr<XmlDocumentType> XmlDocument::CreateDocumentType(std::string_view name)
{
    return std::make_shared<XmlDocumentType>( name, _localSharedFromThis() );
}

std::shared_ptr<XmlDocumentType> XmlDocument::CreateDocumentType(std::string_view name,
                                                                 std::string_view publicId,
                                                                 std::string_view systemId,
                                                                 std::string_view internalSubset)
{
    return std::make_shared<XmlDocumentType>( name, publicId, systemId, internalSubset, _localSharedFromThis() );
}

std::shared_ptr<XmlWhitespace> XmlDocument::CreateWhitespace(std::string_view ws)
{
    return std::make_shared<XmlWhitespace>( ws, _localSharedFromThis() );
}

std::shared_ptr<XmlImplementation> XmlDocument::Implementation() const
{
    INVARIANT( _implementation );

    return _implementation;
}

void XmlDocument::RemoveAll()
{
    INVARIANT( _implementation );

    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlDocument::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    INVARIANT( _implementation );

    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlDocument::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    INVARIANT( _implementation );

    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

void XmlDocument::WriteTo(XmlWriter &xml_writer) const
{
    UNUSED( xml_writer );

    assert( false );
}

XmlNodeType XmlDocument::_getNodeType() const
{
    INVARIANT( _implementation );

    return XmlNodeType::Document;
}

std::shared_ptr<XmlDocument> XmlDocument::_localSharedFromThis()
{
    // Downcast the XmlNode * to an XmlDocument *, since we KNOW we
    // have an XmlDocument *.
    return std::static_pointer_cast<XmlDocument>( shared_from_this() );
}

bool XmlDocument::_thisNodeCanHaveChildren() const
{
    return true;
}

bool XmlDocument::_canAddAsChild(std::shared_ptr<XmlNode> new_child) const
{
    INVARIANT( _implementation );

    XmlNodeType new_child_type = new_child->NodeType();

    return new_child_type == XmlNodeType::Element ||
           new_child_type == XmlNodeType::ProcessingInstruction ||
           new_child_type == XmlNodeType::Comment ||
           new_child_type == XmlNodeType::DocumentType;
}

}