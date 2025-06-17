#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventChannel
{
    None        =  0,  //@< No channel specified
    Admin       = 16,  //@< The administrator log channel
    Operational = 17,  //@< The operational log channel
    Analytic    = 18,  //@< The analytic log channel
    Debug       = 19   //@< The debug channel
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventChannel> : EnumTraitTypes<Diagnostics::Tracing::EventChannel>
{
    static auto EnumName() -> std::string_view { return "EventChannel"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",        Diagnostics::Tracing::EventChannel::None        },
            { "Admin",       Diagnostics::Tracing::EventChannel::Admin       },
            { "Operational", Diagnostics::Tracing::EventChannel::Operational },
            { "Analytin",    Diagnostics::Tracing::EventChannel::Analytic    },
            { "Debug",       Diagnostics::Tracing::EventChannel::Debug       }
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventChannel::None; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventChannel::Debug; }
};

}