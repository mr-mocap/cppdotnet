#include <cppdotnet/System/Xml/XmlCharacterData.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>

namespace System::Xml
{

XmlCharacterData::XmlCharacterData(std::shared_ptr<XmlDocument> doc, std::string_view name)
    :
    XmlCharacterData( std::make_shared<Private::DefaultNodeListImplementation>(),
                      NodeConstructionParameters{ .local_name     = name,
                                                  .name           = name,
                                                  .owner_document = doc } )
{
}

XmlCharacterData::XmlCharacterData(std::string_view data, std::shared_ptr<XmlDocument> doc, std::string_view name)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   NodeConstructionParameters{ .local_name     = name,
                                               .name           = name,
                                               .owner_document = doc } ),
    _value( std::string(data) )
{
}

XmlCharacterData::XmlCharacterData(std::shared_ptr<XmlNodeList>   specific_child_object,
                                   NodeConstructionParameters   &&parameters)
    :
    XmlLinkedNode( specific_child_object, std::move( parameters ) )
{
}

XmlCharacterData::XmlCharacterData(const XmlCharacterData &other)
    :
    XmlLinkedNode( other ),
    _value( other._value )
{
}

XmlCharacterData::XmlCharacterData(XmlCharacterData &&other)
    :
    XmlLinkedNode( std::move( other ) ),
    _value( std::move( other._value ) )
{
}

XmlCharacterData &XmlCharacterData::operator =(const XmlCharacterData &other)
{
    XmlLinkedNode::operator =( other );
    if ( this != &other )
    {
        _value = other._value;
    }
    return *this;
}

XmlCharacterData &XmlCharacterData::operator =(XmlCharacterData &&other)
{
    XmlLinkedNode::operator =( std::move( other ) );
    _value = std::move( other._value );
    return *this;
}

void XmlCharacterData::AppendData(std::string_view data)
{
    _value.append( data );
}

std::string_view XmlCharacterData::Value() const
{
    return _value;
}

void XmlCharacterData::Value(std::string_view new_value)
{
    _value = new_value;
}

std::string_view XmlCharacterData::Data() const
{
    return _value;
}

void XmlCharacterData::Data(std::string_view new_data)
{
    _value = new_data;
}

std::size_t XmlCharacterData::Length() const
{
    return _value.size();
}

void XmlCharacterData::RemoveAll()
{
    _children = std::make_shared<Private::DefaultNodeListImplementation>();
}

std::shared_ptr<XmlNode> XmlCharacterData::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlCharacterData::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

}