#include <cppdotnet/System/Xml/XmlAttributeCollection.hpp>
#include <cppdotnet/System/Xml/XmlNode.hpp>
#include <cppdotnet/System/Private/private.hpp>

namespace System::Xml
{

size_t XmlAttributeCollection::Count() const
{
    return _nodes.Count();
}
    
const std::shared_ptr<XmlNode> XmlAttributeCollection::Item(size_t index) const
{
    if ( index >= _nodes.Count() )
        return nullptr;
    return _nodes[ index ];
}

std::shared_ptr<XmlNode> XmlAttributeCollection::Item(size_t index)
{
    if ( index >= _nodes.Count() )
        return nullptr;
    return _nodes[ index ];
}

const std::shared_ptr<XmlNode> XmlAttributeCollection::Item(int index) const
{
    if ( index < 0 )
        return nullptr;
    
    size_t s_index = static_cast<size_t>(index);

    if ( s_index >= _nodes.Count() )
        return nullptr;

    return _nodes[ index ];
}

std::shared_ptr<XmlNode> XmlAttributeCollection::Item(int index)
{
    if ( index < 0 )
        return nullptr;
    
    size_t s_index = static_cast<size_t>(index);

    if ( s_index >= _nodes.Count() )
        return nullptr;

    return _nodes[ index ];
}

const std::shared_ptr<XmlNode> XmlAttributeCollection::GetNamedItem(std::string_view name) const
{
    for (const std::shared_ptr<XmlNode> &iCurrentNode : _nodes)
    {
        if ( iCurrentNode->Name() == name )
            return iCurrentNode;
    }

    return nullptr;
}

std::shared_ptr<XmlNode> XmlAttributeCollection::GetNamedItem(std::string_view name)
{
    for (std::shared_ptr<XmlNode> &iCurrentNode : _nodes)
    {
        if ( iCurrentNode->Name() == name )
            return iCurrentNode;
    }

    return nullptr;
}

std::shared_ptr<XmlNode> XmlAttributeCollection::SetNamedItem(std::shared_ptr<XmlNode> node)
{
    PRECONDITION( node );

    std::string_view node_name = node->Name();

    for (std::shared_ptr<XmlNode> &iCurrentNode : _nodes)
    {
        if ( iCurrentNode->Name() == node_name )
        {
            std::shared_ptr<XmlNode> local_copy = iCurrentNode;

            iCurrentNode = node;
            return local_copy;
        }
    }
    _nodes.Add( node );
    return node;
}

std::shared_ptr<XmlNode> XmlAttributeCollection::RemoveNamedItem(std::string_view name)
{
    int at_index = _nodes.FindIndex( [=](const std::shared_ptr<XmlNode> &current_node)
                                        {
                                            return current_node->Name() == name;
                                        }
                                   );
    
    if ( at_index == -1 )
        return nullptr;

    size_t at_index_as_size_t = static_cast<size_t>(at_index);
    std::shared_ptr<XmlNode> local_copy = _nodes[ at_index_as_size_t ];

    _nodes.RemoveAt( at_index_as_size_t );
    return local_copy;
}

std::shared_ptr<XmlNode> XmlAttributeCollection::RemoveAt(int index)
{
    if ( index < 0 )
        return nullptr;
    
    size_t index_as_size_t = static_cast<size_t>(index);

    if ( index_as_size_t >= _nodes.Count() )
        return nullptr;
    
    std::shared_ptr<XmlNode> local_copy = _nodes[ index_as_size_t ];

    _nodes.RemoveAt( index_as_size_t );
    return local_copy;
}

void XmlAttributeCollection::RemoveAll()
{
    _nodes.Clear();
}

}