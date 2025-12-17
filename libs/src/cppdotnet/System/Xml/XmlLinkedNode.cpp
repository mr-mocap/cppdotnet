#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>
#include <cppdotnet/System/Xml/XmlNodeList.hpp>

namespace System::Xml
{

XmlLinkedNode::XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object)
    :
    XmlNode( specific_children_object )
{
}

XmlLinkedNode::XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object,
                             std::string_view             local_name,
                             std::string_view             name)
    :
    XmlNode( specific_children_object, local_name, name )
{
}

XmlLinkedNode::XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object,
                             std::string_view             local_name,
                             std::string_view             name,
                             std::string_view             namespace_uri,
                             std::string_view             prefix,
                             std::shared_ptr<XmlDocument> owner_document)
    :
    XmlNode( specific_children_object, local_name, name, namespace_uri, prefix, owner_document )
{
}

XmlLinkedNode::XmlLinkedNode(std::shared_ptr<XmlNodeList>   specific_children_object,
                             NodeConstructionParameters   &&parameters)
    :
    XmlNode(specific_children_object, std::move( parameters ) )
{
}

XmlLinkedNode::XmlLinkedNode(const XmlLinkedNode &other)
    :
    XmlNode( other._children->MemberwiseClone() )
{
}

XmlLinkedNode::XmlLinkedNode(XmlLinkedNode &&other)
    :
    XmlNode( std::move( other._children ) )
{
}

XmlLinkedNode &XmlLinkedNode::operator =(const XmlLinkedNode &other)
{
    XmlNode::operator =( other );
    return *this;
}

XmlLinkedNode &XmlLinkedNode::operator =(XmlLinkedNode &&other)
{
    XmlNode::operator =( std::move( other ) );
    return *this;
}

std::shared_ptr<XmlNode> XmlLinkedNode::NextSibling() const
{
    if ( !ParentNode() )
        return nullptr; // No siblings

    XmlNodeList &siblings = ParentNode()->ChildNodes();

    for (int i = 0; i < siblings.Count(); ++i)
    {
        XmlNode *iCurrentSibling = siblings[ i ].get();

        if ( iCurrentSibling == this )
        {
            if ( i == siblings.Count() - 1 ) // No next after the last sibling
                return nullptr;

            return siblings[ i + 1 ];
        }
    }

    return nullptr; // This node wasn't in the siblings list
}

std::shared_ptr<XmlNode> XmlLinkedNode::PreviousSibling() const
{
    if ( !ParentNode() )
        return nullptr; // No siblings

    XmlNodeList &siblings = ParentNode()->ChildNodes();

    for (int i = 0; i < siblings.Count(); ++i)
    {
        XmlNode *iCurrentSibling = siblings[ i ].get();

        if ( iCurrentSibling == this )
        {
            if ( i == 0 )
                return nullptr; // No previous to the first sibling

            return siblings[ i - 1 ];
        }
    }

    return nullptr; // This node wasn't in the siblings list
}

}