#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventManifestOptions
{
    None         = 0, //@< No options are specified
    Strict       = 1, //@< Causes an exception to be raised if any inconsistencies occur when writing the manifest file
    AllCultures  = 2, //@< Generates a resources node under the localization folder for every satellite assembly provided
    OnlyIfNeededForRegistration = 4, //@< A manifest is generated only the event source must be registered on the host computer
    AllowEventSourceOverride    = 8  //@< Overrides the default behavior that the current EventSource must be the base class of the user-defined type passed to the write method. This enables the validation of .NET event sources.
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventManifestOptions> : EnumTraitTypes<Diagnostics::Tracing::EventManifestOptions>
{
    static auto EnumName() -> std::string_view { return "EventManifestOptions"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",                        Diagnostics::Tracing::EventManifestOptions::None         },
            { "Strict",                      Diagnostics::Tracing::EventManifestOptions::Strict       },
            { "AllCultures",                 Diagnostics::Tracing::EventManifestOptions::AllCultures  },
            { "OnlyIfNeededForRegistration", Diagnostics::Tracing::EventManifestOptions::OnlyIfNeededForRegistration },
            { "AllowEventSourceOverride",    Diagnostics::Tracing::EventManifestOptions::AllowEventSourceOverride    }
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventManifestOptions::None; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventManifestOptions::AllowEventSourceOverride; }
};

}