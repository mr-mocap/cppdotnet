#include <cppdotnet/System/Xml/XmlCharacterData.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>

namespace System::Xml
{

XmlCharacterData::XmlCharacterData(std::shared_ptr<XmlDocument> doc, std::string_view name)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   name,
                   name,
                   std::string_view(),
                   std::string_view(),
                   doc )
{
    INVARIANT( _owner_document );
}

XmlCharacterData::XmlCharacterData(std::string_view data, std::shared_ptr<XmlDocument> doc, std::string_view name)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   name,
                   name,
                   std::string_view(),
                   std::string_view(),
                   doc ),
    _value( std::string(data) )
{
    INVARIANT( _owner_document );
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
    if ( _value.HasValue() )
        _value.Value().append( data );
    else
        _value = Nullable<std::string>( std::string(data) );
}

Nullable<std::string> XmlCharacterData::Value() const
{
    INVARIANT( _owner_document );

    return _value;
}

void XmlCharacterData::Value(Nullable<std::string> new_value)
{
    INVARIANT( _owner_document );

    _value = new_value;
}

Nullable<std::string> XmlCharacterData::Data() const
{
    INVARIANT( _owner_document );

    return _value;
}

void XmlCharacterData::Data(Nullable<std::string_view> new_data)
{
    INVARIANT( _owner_document );

    _value = new_data;
}

std::size_t XmlCharacterData::Length() const
{
    INVARIANT( _owner_document );

    return _value.HasValue() ? _value.Value().size() : 0;
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