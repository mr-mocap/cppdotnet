#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>
#include <cppdotnet/System/Xml/XmlNodeList.hpp>

namespace System::Xml
{

XmlLinkedNode::XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object)
    :
    XmlNode( specific_children_object )
{
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