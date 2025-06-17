#pragma once

#include "System/Private/enum.hpp"

namespace System::Diagnostics::Tracing
{

enum class EventSourceSettings
{
    Default                      = 0, //@< None of the special configuration options are enabled
    ThrowOnEventWriteErrors      = 1, //@< The event source throws an exception when an error occurs
    EtwManifestEventFormat       = 4, //@< The ETW listener should use a manifest-based format when raising events. Setting this option is a directive to the ETW listener should use manifest-based format when raising events. This is the default option when defining a type derived from EventSource using one of the protected EventSource constructors.
    EtwSelfDescribingEventFormat = 8, //@< The ETW listener should use self-describing event format. This is the default option when creating a new instance of the EventSource using one of the public EventSource constructors.
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventSourceSettings> : EnumTraitTypes<Diagnostics::Tracing::EventSourceSettings>
{
    static auto EnumName() -> std::string_view { return "EventSourceSettings"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Default",                      Diagnostics::Tracing::EventSourceSettings::Default },
            { "ThrowOnEventWriteErrors",      Diagnostics::Tracing::EventSourceSettings::ThrowOnEventWriteErrors },
            { "EtwManifestEventFormat",       Diagnostics::Tracing::EventSourceSettings::EtwManifestEventFormat },
            { "EtwSelfDescribingEventFormat", Diagnostics::Tracing::EventSourceSettings::EtwSelfDescribingEventFormat }
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

    static constexpr bool IsDefined(std::string_view value_string)
    {
        return std::ranges::find( NameValuePairs(),
                                  value_string,
                                  &name_value_pair_type::first
                                ) != NameValuePairs().end();
    }

    static constexpr auto ToName(value_type value) -> std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr auto ToName(underlying_type value) -> std::string_view
    {
        return ToName( static_cast<value_type>(value) );
    }

    static constexpr value_type min() { return Diagnostics::Tracing::EventSourceSettings::Default; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventSourceSettings::EtwSelfDescribingEventFormat; }
};

}