#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventFieldFormat
{
    Default     = 0,
    String	    = 2,
    Boolean     = 3,
    Hexadecimal = 4,
    Xml         = 11,
    Json        = 12,
    HResult     = 15	
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventFieldFormat> : EnumTraitTypes<Diagnostics::Tracing::EventFieldFormat>
{
    static auto EnumName() -> std::string_view { return "EventFieldFormat"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Default",     Diagnostics::Tracing::EventFieldFormat::Default     },
            { "String",      Diagnostics::Tracing::EventFieldFormat::String      },
            { "Boolean",     Diagnostics::Tracing::EventFieldFormat::Boolean     },
            { "Hexadecimal", Diagnostics::Tracing::EventFieldFormat::Hexadecimal },
            { "Xml",         Diagnostics::Tracing::EventFieldFormat::Xml         },
            { "Json",        Diagnostics::Tracing::EventFieldFormat::Json        },
            { "HResult",     Diagnostics::Tracing::EventFieldFormat::HResult     }
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventFieldFormat::Default; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventFieldFormat::HResult; }
};

}