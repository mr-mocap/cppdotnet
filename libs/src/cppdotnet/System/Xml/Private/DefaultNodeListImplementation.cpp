#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>

namespace System::Xml::Private
{

DefaultNodeListImplementation::DefaultNodeListImplementation(const DefaultNodeListImplementation &other)
    :
    _nodes( other._nodes )
{
}

DefaultNodeListImplementation::~DefaultNodeListImplementation()
{
}

DefaultNodeListImplementation &DefaultNodeListImplementation::operator =(const DefaultNodeListImplementation &other)
{
    if ( this != &other)
    {
        _nodes = other._nodes;
    }
    return *this;
}

int DefaultNodeListImplementation::Count() const
{
    return _nodes.Count();
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::operator [](size_t index) const
{
    if ( index >= _nodes.Count() )
        return nullptr;
    
    return _nodes[ index ];
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::operator [](int index) const
{
    if ( index < 0 )
        return nullptr;
    
    return operator []( static_cast<size_t>( index ) );
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::Item(size_t index) const
{
    if ( index >= _nodes.Count() )
        return nullptr;
    
    return _nodes[ index ];
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::Item(int index) const
{
    if ( index < 0 )
        return nullptr;
    
    return Item( static_cast<size_t>( index ) );
}

std::shared_ptr<XmlNodeList> DefaultNodeListImplementation::MemberwiseClone() const
{
    return std::make_shared<DefaultNodeListImplementation>( *this );
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::Append(std::shared_ptr<XmlNode> new_node)
{
    _nodes.Add( new_node );
    return new_node;
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::Insert(int index, std::shared_ptr<XmlNode> new_node)
{
    _nodes.Insert( index, new_node );
    return new_node;
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::Insert(size_t index, std::shared_ptr<XmlNode> new_node)
{
    _nodes.Insert( index, new_node );
    return new_node;
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::RemoveChild(std::shared_ptr<XmlNode> child_node)
{
    int at_index = _nodes.IndexOf( child_node );

    if ( at_index == -1 )
        ThrowWithTarget( ArgumentException( "child_node", "Not a child of this node" ) );
    
    std::shared_ptr<XmlNode> node = _nodes[ at_index ];
    bool removed = _nodes.Remove( child_node );

    INVARIANT( removed );

    return node;
}

std::shared_ptr<XmlNode> DefaultNodeListImplementation::ReplaceChild(std::shared_ptr<XmlNode> new_child,
                                                                     std::shared_ptr<XmlNode> old_child)
{
    int at_index = _nodes.IndexOf( old_child );

    if ( at_index == -1 )
        ThrowWithTarget( ArgumentException( "child_node", "Not a child of this node" ) );
    
    std::shared_ptr<XmlNode> node = _nodes[ at_index ];

    _nodes[ at_index ] = new_child;
    return node;
}

}