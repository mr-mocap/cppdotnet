#pragma once

#include "System/Diagnostics/Private/CommonTypes.hpp"
#include <string>
#include <string_view>


namespace System::Diagnostics::Metrics
{

struct MeterOptions
{
    MeterOptions(std::string_view name)
        :
        Name( name )
    {
    }

    std::string  Name;
    std::string  Version;
    void        *Scope = nullptr;
    Diagnostics::Types::NameObjectPairList Tags;
};

}
