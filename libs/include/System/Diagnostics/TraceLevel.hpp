#pragma once

#include "System/Exception.hpp"
#include "System/Private/private.hpp"
#include "System/Private/enum.hpp"
#include <string_view>
#include <variant>
#include <algorithm>

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
struct EnumPolicy<System::Diagnostics::TraceLevel>
{
public:
    using value_type = System::Diagnostics::TraceLevel;
    using name_value_pair_type = std::pair<const char *, value_type>;

    static constexpr std::string_view EnumName = "TraceLevel";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Off",     Diagnostics::TraceLevel::Off },
            { "Error",   Diagnostics::TraceLevel::Error },
            { "Warning", Diagnostics::TraceLevel::Warning },
            { "Info",    Diagnostics::TraceLevel::Info },
            { "Verbose", Diagnostics::TraceLevel::Verbose }
        };
};

}