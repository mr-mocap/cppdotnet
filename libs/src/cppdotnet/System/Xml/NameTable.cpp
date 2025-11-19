#include <cppdotnet/System/Xml/NameTable.hpp>
#include <cppdotnet/System/Exception.hpp>

namespace System::Xml
{

NameTable::NameTable()
{
}

NameTable::NameTable(const NameTable &other)
    :
    _names( other._names )
{
}

NameTable &NameTable::operator=(const NameTable &other)
{
    if ( this != &other )
    {
        _names = other._names;
    }
    return *this;
}

NameTable::NameTable(NameTable &&other)
    :
    _names( std::move(other._names) )
{
}

NameTable::~NameTable()
{
}

NameTable &NameTable::operator=(NameTable &&other)
{
    if ( this != &other )
    {
        _names = std::move(other._names);
    }
    return *this;
}

std::string_view NameTable::Add(std::string_view name)
{
    if ( name.empty() )
        ThrowWithTarget( System::ArgumentNullException( "name" ) );

    auto [it, inserted] = _names.insert( std::string(name) ); // TODO: FIXME in C++23

    return *it;
}

std::string_view NameTable::Get(std::string_view name) const
{
    if ( name.empty() )
        ThrowWithTarget( System::ArgumentNullException( "name" ) );

    auto it = _names.find( std::string(name) ); // TODO: FIXME in C++23

    return (it != _names.end()) ? *it : std::string_view{};
}

std::shared_ptr<XmlNameTable> NameTable::MemberwiseClone() const
{
    return std::make_shared<NameTable>( *this );
}

}