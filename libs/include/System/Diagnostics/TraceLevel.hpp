#include "System/Private/enum.hpp"

namespace System::Diagnostics
{

enum class TraceLevel
{
    Off = 0,
    Error,
    Warning,
    Info,
    Verbose
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::TraceLevel> : EnumTraitTypes<System::Diagnostics::TraceLevel>
{
    static constexpr std::string_view EnumName = "TraceLevel";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Off",     Diagnostics::TraceLevel::Off     },
            { "Error",   Diagnostics::TraceLevel::Error   },
            { "Warning", Diagnostics::TraceLevel::Warning },
            { "Info",    Diagnostics::TraceLevel::Info    },
            { "Verbose", Diagnostics::TraceLevel::Verbose }
        };
};

}