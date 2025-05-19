#pragma once

#include "System/Exception.hpp"
#include "System/Private/private.hpp"
#include "System/Private/enum.hpp"
#include <string_view>
#include <variant>
#include <optional>
#include <algorithm>
#include <limits>

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
struct EnumTraits<Diagnostics::TraceLevel> : EnumTraitTypes<Diagnostics::TraceLevel>
{
    static auto EnumName() -> const std::string_view { return "TraceLevel"; }

    static auto NameValuePairs() -> std::span<name_value_pair_type>
    {
        static name_value_pair_type array[] = {
            { "Off",     Diagnostics::TraceLevel::Off },
            { "Error",   Diagnostics::TraceLevel::Error },
            { "Warning", Diagnostics::TraceLevel::Warning },
            { "Info",    Diagnostics::TraceLevel::Info },
            { "Verbose", Diagnostics::TraceLevel::Verbose }
        };

        return array;
    }

    static auto Count() -> std::size_t { return 5; }

    static auto Names() -> std::ranges::keys_view<std::span<name_value_pair_type>>
    {
        return std::views::keys( NameValuePairs() );
    }

    static auto Values() -> std::ranges::values_view<std::span<name_value_pair_type>>
    {
        return std::views::values( NameValuePairs() );
    }

    static auto ValuesAsUnderlyingType()
    {
        auto to_underlying_type = [](const value_type item) { return static_cast<underlying_type>(item); };

        return Values() | std::views::transform( to_underlying_type );
    }

    static auto ToName(value_type value) -> const std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr value_type min() { return Diagnostics::TraceLevel::Off; }
    static constexpr value_type max() { return Diagnostics::TraceLevel::Verbose; }
};

}

template <>
struct std::formatter<System::Diagnostics::TraceLevel> : System::EnumFormatter<System::Diagnostics::TraceLevel>
{
};