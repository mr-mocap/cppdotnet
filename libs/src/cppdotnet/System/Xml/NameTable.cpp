#include <cppdotnet/System/Xml/NameTable.hpp>
#include <cppdotnet/System/Exception.hpp>

namespace System::Xml
{

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

}