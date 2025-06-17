#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventActivityOptions
{
    None       = 0, //@< Use the default behavior for start and stop tracking.
    Disable    = 2, //@< Turn off start and stop tracking.
    Recursive  = 4, //@< Allow recursive activity starts. By default, an activity cannot be recursive. That is, a sequence of Start A, Start A, Stop A, Stop A is not allowed. Unintentional recursive activities can occur if the app executes and for some the stop is not reached before another start is called.
    Detachable = 8  //@< Allow overlapping activities. By default, activity starts and stops must be property nested. That is, a sequence of Start A, Start B, Stop A, Stop B is not allowed will result in B stopping at the same time as A.
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventActivityOptions> : EnumTraitTypes<Diagnostics::Tracing::EventActivityOptions>
{
    static auto EnumName() -> std::string_view { return "EventActivityOptions"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",       Diagnostics::Tracing::EventActivityOptions::None       },
            { "Disable",    Diagnostics::Tracing::EventActivityOptions::Disable    },
            { "Recursive",  Diagnostics::Tracing::EventActivityOptions::Recursive  },
            { "Detachable", Diagnostics::Tracing::EventActivityOptions::Detachable }
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventActivityOptions::None; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventActivityOptions::Detachable; }
};

}