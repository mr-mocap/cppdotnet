#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventLevel
{
    LogAlways     = 0, //@< No level filtering is done on the event. When used as a level filter for enabling events, for example in EventListener.EnableEvents(), events of all levels will be included.
    Critical      = 1, //@<	This level corresponds to a critical error, which is a serious error that has caused a major failure. 
    Error         = 2, //@< This level adds standard errors that signify a problem. 
    Warning       = 3, //@< This level adds warning events (for example, events that are published because a disk is nearing full capacity).
    Informational = 4, //@< This level adds informational events or messages that are not errors. These events can help trace the progress or state of an application.
    Verbose       = 5  //@< This level adds lengthy events or messages. It causes all events to be logged.
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventLevel> : EnumTraitTypes<Diagnostics::Tracing::EventLevel>
{
    static auto EnumName() -> std::string_view { return "EventLevel"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "LogAlways",     Diagnostics::Tracing::EventLevel::LogAlways     },
            { "Critical",      Diagnostics::Tracing::EventLevel::Critical      },
            { "Error",         Diagnostics::Tracing::EventLevel::Error         },
            { "Warning",       Diagnostics::Tracing::EventLevel::Warning       },
            { "Informational", Diagnostics::Tracing::EventLevel::Informational },
            { "Verbose",       Diagnostics::Tracing::EventLevel::Verbose       }
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventLevel::LogAlways; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventLevel::Verbose; }
};

}