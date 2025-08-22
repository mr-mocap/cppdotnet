#include "System/Private/enum.hpp"
#include <algorithm>

namespace System::Diagnostics
{

enum class SourceLevels
{
    All      = -1,
    Off      = 0,
    Critical = 1,
    Error    = 3,
    Warning  = 7,
    Information = 15,
    Verbose  = 31,
    ActivityTracing = 65280
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::SourceLevels> : EnumTraitTypes<System::Diagnostics::SourceLevels>
{
public:

    static constexpr std::string_view EnumName = "SourceLevels";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "All",             Diagnostics::SourceLevels::All             },
            { "Off",             Diagnostics::SourceLevels::Off             },
            { "Critical",        Diagnostics::SourceLevels::Critical        },
            { "Error",           Diagnostics::SourceLevels::Error           },
            { "Warning",         Diagnostics::SourceLevels::Warning         },
            { "Information",     Diagnostics::SourceLevels::Information     },
            { "Verbose",         Diagnostics::SourceLevels::Verbose         },
            { "ActivityTracing", Diagnostics::SourceLevels::ActivityTracing }
        };
};

}