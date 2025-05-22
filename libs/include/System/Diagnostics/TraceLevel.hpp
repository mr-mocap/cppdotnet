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

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Off",     Diagnostics::TraceLevel::Off },
            { "Error",   Diagnostics::TraceLevel::Error },
            { "Warning", Diagnostics::TraceLevel::Warning },
            { "Info",    Diagnostics::TraceLevel::Info },
            { "Verbose", Diagnostics::TraceLevel::Verbose }
        };

    static constexpr auto NameValuePairs() -> std::span<const name_value_pair_type>
    {
        return std::span{ NameValueArray };
    }

    static constexpr auto Count() -> std::size_t { return NameValuePairs().size(); }

    static constexpr auto Names() -> std::ranges::keys_view<std::span<const name_value_pair_type>>
    {
        return std::views::keys( NameValuePairs() );
    }

    static constexpr auto Values() -> std::ranges::values_view<std::span<const name_value_pair_type>>
    {
        return std::views::values( NameValuePairs() );
    }

    static constexpr auto ValuesAsUnderlyingType()
    {
        auto to_underlying_type = [](const value_type item) { return static_cast<underlying_type>(item); };

        return Values() | std::views::transform( to_underlying_type );
    }

    static constexpr bool IsDefined(value_type value)
    {
        // We can do this because the enumerations are consecutive..
        return (value >= min()) && (value <= max());
    }

    static constexpr bool IsDefined(underlying_type value)
    {
        return IsDefined( static_cast<value_type>(value) );
    }

    static constexpr bool IsDefined(const std::string_view value_string)
    {
        return std::ranges::find( NameValuePairs(),
                                  value_string,
                                  &name_value_pair_type::first
                                ) != NameValuePairs().end();
    }

    static constexpr auto ToName(value_type value) -> const std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr auto ToName(underlying_type value) -> const std::string_view
    {
        return ToName( static_cast<value_type>(value) );
    }

    static constexpr value_type min() { return Diagnostics::TraceLevel::Off; }
    static constexpr value_type max() { return Diagnostics::TraceLevel::Verbose; }
};

}