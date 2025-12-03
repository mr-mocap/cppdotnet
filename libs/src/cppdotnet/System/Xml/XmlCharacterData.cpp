#include <cppdotnet/System/Xml/XmlCharacterData.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>

namespace System::Xml
{

XmlCharacterData::XmlCharacterData(std::string_view data, std::shared_ptr<XmlDocument> doc)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _value( std::string(data) ),
    _owner_document( doc )
{
    INVARIANT( _owner_document );
}

void XmlCharacterData::AppendData(std::string_view data)
{
    if ( _value.HasValue() )
        _value.Value().append( data );
    else
        _value = Nullable<std::string>( std::string(data) );
}

std::shared_ptr<XmlDocument> XmlCharacterData::OwnerDocument() const
{
    INVARIANT( _owner_document );

    return _owner_document;
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

}