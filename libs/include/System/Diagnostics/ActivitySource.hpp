#pragma once

#include <string>
#include <string_view>


namespace System::Diagnostics
{

class ActivitySource final
{
public:
    ActivitySource(const std::string_view name)
        :
        _name( name )
    {
    }

    ActivitySource(const std::string_view name, const std::string_view version)
        :
        _name( name ),
        _version( version )
    {
    }

protected:
    std::string _name;
    std::string _version;
};

}