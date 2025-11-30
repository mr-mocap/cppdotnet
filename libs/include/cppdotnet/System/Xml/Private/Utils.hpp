#pragma once

#include <string>
#include <string_view>

namespace System::Xml::Private::Utils
{

inline std::string Quote(std::string_view s)
{
    std::string quoted_string;

    quoted_string.reserve( s.size() + 2 );
    return quoted_string.append( "\"" ).append( s ).append( "\"" );
}

}