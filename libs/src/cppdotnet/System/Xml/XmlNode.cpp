#include <cppdotnet/System/Xml/XmlNode.hpp>
#include <cppdotnet/System/Xml/XmlNodeList.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>

namespace System::Xml
{

XmlNode::XmlNode(std::shared_ptr<XmlNodeList> specific_children_object)
    :
    _children( specific_children_object )
{
}

XmlNode::XmlNode(std::shared_ptr<XmlNodeList> specific_children_object,
                 std::string_view             local_name,
                 std::string_view             name)
    :
    _children( specific_children_object ),
    _local_name( local_name ),
    _name( name )
{
}

XmlNode::XmlNode(std::shared_ptr<XmlNodeList> specific_children_object,
                 std::string_view             local_name,
                 std::string_view             name,
                 std::string_view             namespace_uri,
                 std::string_view             prefix,
                 std::shared_ptr<XmlDocument> owner_document)
    :
    _children( specific_children_object ),
    _local_name( local_name ),
    _name( name ),
    _namespace_uri( namespace_uri ),
    _prefix( prefix ),
    _owner_document( owner_document )
{
}

XmlNode::XmlNode(const XmlNode &other)
    :
    std::enable_shared_from_this<XmlNode>( other ),
    _attributes( other._attributes ),
    _children( other._children->MemberwiseClone() ),
    _local_name( other._local_name ),
    _name( other._name ),
    _namespace_uri( other._namespace_uri ),
    _prefix( other._prefix ),
    _owner_document( other._owner_document )
{
}

XmlNode::XmlNode(XmlNode &&other)
    :
    std::enable_shared_from_this<XmlNode>( other ),
    _attributes( other._attributes ),
    _children( std::move( other._children ) ),
    _local_name( std::move( other._local_name ) ),
    _name( std::move( other._name ) ),
    _namespace_uri( std::move( other._namespace_uri ) ),
    _prefix( std::move( other._prefix ) ),
    _owner_document( std::move( other._owner_document ) )
{
}

XmlNode &XmlNode::operator =(const XmlNode &other)
{
    if ( this != &other )
    {
        _attributes = other._attributes;
        _children = other._children->MemberwiseClone();
        _local_name = other._local_name;
        _name = other._name;
        _namespace_uri = other._namespace_uri;
        _prefix = other._prefix;
        _owner_document = other._owner_document;
    }
    return *this;
}

XmlNode &XmlNode::operator =(XmlNode &&other)
{
    if ( this != &other )
    {
        _attributes = std::move( other._attributes );
        _children = std::move( other._children );
        _local_name = std::move( other._local_name );
        _name = std::move( other._name );
        _namespace_uri = std::move( other._namespace_uri );
        _prefix = std::move( other._prefix );
        _owner_document = std::move( other._owner_document );
    }
    return *this;
}

std::shared_ptr<XmlNode> XmlNode::Clone() const
{
    return CloneNode( true );
}

std::shared_ptr<XmlNode> XmlNode::AppendChild(std::shared_ptr<XmlNode> new_child)
{
    if ( !_thisNodeCanHaveChildren() )
        ThrowWithTarget( InvalidOperationException( std::format("Node of type '{}' cannot have children.", NodeType() ) ) );

    if ( !_isFromSameDocument( new_child ) )
        ThrowWithTarget( ArgumentException( "Cannot add a child node from a different document.", "new_child" ) );

    if ( !_canAddAsChild( new_child ) )
        ThrowWithTarget( InvalidOperationException( std::format("Cannot add child node of type '{}' to parent node of type '{}'", new_child->NodeType(), NodeType() ) ) );
    
    ChildNodes().Append( new_child );
    return new_child;
}

std::shared_ptr<XmlNode> XmlNode::PrependChild(std::shared_ptr<XmlNode> new_child)
{
    if ( !_thisNodeCanHaveChildren() )
        ThrowWithTarget( InvalidOperationException( std::format("Node of type '{}' cannot have children.", NodeType() ) ) );

    if ( !_isFromSameDocument( new_child ) )
        ThrowWithTarget( ArgumentException( "Cannot add a child node from a different document.", "new_child" ) );

    if ( !_canAddAsChild( new_child ) )
        ThrowWithTarget( InvalidOperationException( std::format("Cannot add child node of type '{}' to parent node of type '{}'", new_child->NodeType(), NodeType() ) ) );
    
    ChildNodes().Insert( 0, new_child );
    return new_child;
}

const XmlAttributeCollection &XmlNode::Attributes() const
{
    return _attributes;
}

XmlAttributeCollection &XmlNode::Attributes()
{
    return _attributes;
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
    return nullptr; // Default value
}

std::shared_ptr<XmlNode> XmlNode::PreviousSibling() const
{
    return nullptr; // Default value
}

std::shared_ptr<XmlNode> XmlNode::ParentNode() const
{
    return nullptr;
}

std::string_view XmlNode::Prefix() const
{
    return _prefix;
}

void XmlNode::Prefix(std::string_view new_prefix)
{
    _prefix = new_prefix;
}

std::shared_ptr<XmlDocument> XmlNode::OwnerDocument() const
{
    return _owner_document;
}

Nullable<std::string> XmlNode::Value() const
{
    return { };
}

void XmlNode::Value(Nullable<std::string> new_value)
{
    UNUSED( new_value );

    ThrowWithTarget( InvalidOperationException( std::format("Cannot set a value on node type '{}'", NodeType()) ) );
}

std::string_view XmlNode::LocalName() const
{
    return _local_name;
}

std::string_view XmlNode::Name() const
{
    return _name;
}

std::string_view XmlNode::NamespaceURI() const
{
    return _namespace_uri;
}

bool XmlNode::_thisNodeCanHaveChildren() const
{
    // By default, nodes cannot have children.
    // This should be overridden in derived classes that can have children.
    return false;
}

bool XmlNode::_canAddAsChild(std::shared_ptr<XmlNode> new_child) const
{
    UNUSED( new_child );

    return false;
}

bool XmlNode::_isFromSameDocument(std::shared_ptr<XmlNode> node)
{
    std::shared_ptr<XmlDocument> this_owner_doc  = OwnerDocument();
    std::shared_ptr<XmlDocument> other_owner_doc = node->OwnerDocument();

    return this_owner_doc == other_owner_doc;
}

}