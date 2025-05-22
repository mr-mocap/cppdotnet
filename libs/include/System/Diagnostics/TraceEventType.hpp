#pragma once

#include "System/Private/enum.hpp"

namespace System::Diagnostics
{
    enum class TraceEventType
    {
        Critical    = 0x01,
        Error       = 0x02,
        Warning     = 0x04,
        Information = 0x08,
        Verbose     = 0x10,
        Start       = 0x0100,
        Stop        = 0x0200,
        Suspend     = 0x0400,
        Resume      = 0x0800,
        Transfer    = 0x1000
    };
}

namespace System
{

template <>
struct EnumTraits<Diagnostics::TraceEventType> : EnumTraitTypes<Diagnostics::TraceEventType>
{
    static auto EnumName() -> const std::string_view { return "TraceEventType"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Critical",    Diagnostics::TraceEventType::Critical },
            { "Error",       Diagnostics::TraceEventType::Error },
            { "Warning",     Diagnostics::TraceEventType::Warning },
            { "Information", Diagnostics::TraceEventType::Information },
            { "Verbose",     Diagnostics::TraceEventType::Verbose },
            { "Start",       Diagnostics::TraceEventType::Start },
            { "Stop",        Diagnostics::TraceEventType::Stop },
            { "Suspend",     Diagnostics::TraceEventType::Suspend },
            { "Resume",      Diagnostics::TraceEventType::Resume },
            { "Transfer",    Diagnostics::TraceEventType::Transfer }
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
        return std::ranges::find( NameValuePairs(),
                                  value,
                                  &name_value_pair_type::second
                                ) != NameValuePairs().end();
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

    static constexpr value_type min() { return Diagnostics::TraceEventType::Critical; }
    static constexpr value_type max() { return Diagnostics::TraceEventType::Transfer; }
};

}