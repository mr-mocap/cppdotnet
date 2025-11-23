#include <cppdotnet/System/Xml/XmlNode.hpp>
#include <cppdotnet/System/Xml/XmlNodeList.hpp>

namespace System::Xml
{

XmlNode::XmlNode(std::shared_ptr<XmlNodeList> specific_children_object)
    :
    _children( specific_children_object )
{
}

std::shared_ptr<XmlNode> XmlNode::Clone() const
{
    return CloneNode( true );
}

std::shared_ptr<XmlNode> XmlNode::AppendChild(std::shared_ptr<XmlNode> new_child)
{
    // TODO: Implement Exception Handling
    //       InvalidOperationException - This node type doesn't allow nodes of type new_child
    //       ArgumentException - new_child was created from a different document.
    //                           This node is read only.
    ChildNodes().Append( new_child );
    return new_child;
}

std::shared_ptr<XmlNode> XmlNode::PrependChild(std::shared_ptr<XmlNode> new_child)
{
    ChildNodes().Insert( 0, new_child );
    return new_child;
}

std::shared_ptr<XmlAttributeCollection> XmlNode::Attributes() const
{
    return nullptr;
}

bool XmlNode::IsReadOnly() const
{
    return false;
}

std::shared_ptr<XmlNode> XmlNode::InsertAfter(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> ref_child)
{
    PRECONDITION( ref_child );

    XmlNode *ref_child_raw_ptr = ref_child.get();
    XmlNodeList &children = ChildNodes();

    for (int index = 0; index < children.Count(); ++index)
    {
        XmlNode *iCurrentNode = children[ index ].get();

        if ( iCurrentNode == ref_child_raw_ptr )
        {
            // We can do this because index < _children.Count() and therefore
            // index + 1 will be AT MOST _children.Count().
            // Insert( _children.Count(), new_child ) is handled as an Append().
            children.Insert( index + 1, new_child );
            break;
        }
    }
    return new_child;
}

std::shared_ptr<XmlNode> XmlNode::InsertBefore(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> ref_child)
{
    PRECONDITION( ref_child );

    XmlNode *ref_child_raw_ptr = ref_child.get();
    XmlNodeList &children = ChildNodes();

    for (int index = 0; index < children.Count(); ++index)
    {
        XmlNode *iCurrentNode = children[ index ].get();

        if ( iCurrentNode == ref_child_raw_ptr )
        {
            children.Insert( index, new_child );
            break;
        }
    }
    return new_child;
}

XmlNodeList &XmlNode::ChildNodes() const
{
    INVARIANT( _children );

    return *_children;
}

std::shared_ptr<XmlNode> XmlNode::FirstChild() const
{
    INVARIANT( _children );

    if ( HasChildNodes() )
        return ChildNodes().Item(0);

    return nullptr;
}

std::shared_ptr<XmlNode> XmlNode::LastChild() const
{
    INVARIANT( _children );

    if ( HasChildNodes() )
        return ChildNodes().Item( ChildNodes().Count() - 1 );

    return nullptr;
}

bool XmlNode::HasChildNodes() const
{
    INVARIANT( _children );

    return ChildNodes().Count() != 0;
}

std::shared_ptr<XmlNode> XmlNode::NextSibling() const
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

std::shared_ptr<XmlNode> XmlNode::PreviousSibling() const
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

std::shared_ptr<XmlNode> XmlNode::ParentNode() const
{
    return nullptr;
}

Nullable<std::string> XmlNode::Value() const
{
    return { };
}

void XmlNode::Value(Nullable<std::string> new_value)
{
    UNUSED( new_value );
}

}