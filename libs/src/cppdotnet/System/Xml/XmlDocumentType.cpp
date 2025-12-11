#include <cppdotnet/System/Xml/XmlDocumentType.hpp>
#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>

namespace System::Xml
{

XmlDocumentType::XmlDocumentType(std::string_view name,
                                 std::shared_ptr<XmlDocument> doc)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   name,
                   name,
                   std::string_view{ },
                   std::string_view{ },
                   doc )
{
}

XmlDocumentType::XmlDocumentType(std::string_view name,
                                 std::string_view publicId,
                                 std::string_view systemId,
                                 std::string_view internalSubset,
                                 std::shared_ptr<XmlDocument> doc)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   name,
                   name,
                   std::string_view{ },
                   std::string_view{ },
                   doc )
{
    UNUSED( publicId );
    UNUSED( systemId );
    UNUSED( internalSubset );
}

XmlDocumentType::XmlDocumentType(const XmlDocumentType &other)
    :
    XmlLinkedNode( other )
{
}

XmlDocumentType::XmlDocumentType(XmlDocumentType &&other)
    :
    XmlLinkedNode( std::move( other ) )
{
}

XmlDocumentType &XmlDocumentType::operator =(const XmlDocumentType &other)
{
    XmlLinkedNode::operator =( other );
    return *this;
}

XmlDocumentType &XmlDocumentType::operator =(XmlDocumentType &&other)
{
    XmlLinkedNode::operator =( std::move( other ) );
    return *this;
}

std::shared_ptr<XmlNode> XmlDocumentType::CloneNode(bool deep) const
{
    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlDocumentType>( *this );
    else
        return std::make_shared<XmlDocumentType>( *this );
}

void XmlDocumentType::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlDocumentType::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlDocumentType::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

void XmlDocumentType::WriteTo(XmlWriter &xml_writer) const
{
    UNUSED( xml_writer );
}

XmlNodeType XmlDocumentType::_getNodeType() const
{
    return XmlNodeType::DocumentType;
}

bool XmlDocumentType::_thisNodeCanHaveChildren() const
{
    return true;
}

bool XmlDocumentType::_canAddAsChild(std::shared_ptr<XmlNode> new_child) const
{
    XmlNodeType new_child_type = new_child->NodeType();

    return new_child_type == XmlNodeType::Element  ||
           new_child_type == XmlNodeType::Notation ||
           new_child_type == XmlNodeType::Entity;
           // ATTRLIST?
}

}