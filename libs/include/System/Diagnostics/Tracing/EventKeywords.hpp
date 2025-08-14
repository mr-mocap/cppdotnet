
namespace System::Diagnostics::Tracing
{

enum class EventKeywords
{
    All  = -1, //@< All the bits are set to 1, representing every possible group of events
    None =  0, //@< No filtering on keywords is performed when the event is published
    MicrosoftTelemetry = 562949953421312,  //@< Attached to all Microsoft telemetry events
    WdiContext         = 562949953421312,  //@< Attached to all Windows Diagnostics Infrastructure (WDI) context events
    WdiDiagnostic      = 1125899906842624, //@< Attached to all Windows Diagnostics Infrastructure (WDI) diagnostic events
    Sqm	               = 2251799813685248, //@< Attached to all Service Quality Mechanism (SQM) events
    AuditFailure       = 4503599627370496, //@< Attached to all failed security audit events. Use this keyword only for events in the security log.
    CorrelationHint    = 4503599627370496, //@< Attached to transfer events where the related activity ID (correlation ID) is a computed value and is not guaranteed to be unique (that is, it is not a real GUID).
    AuditSuccess       = 9007199254740992, //@< Attached to all successful security audit events. Use this keyword only for events in the security log.
    EventLogClassic    = 36028797018963968 //@< Attached to events that are raised by using the @c RaiseEvent function 
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventKeywords> : EnumTraitTypes<Diagnostics::Tracing::EventKeywords>
{
    static auto EnumName() -> std::string_view { return "EventKeywords"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "All",                Diagnostics::Tracing::EventKeywords::All   },
            { "None",               Diagnostics::Tracing::EventKeywords::None  },
            { "MicrosoftTelemetry", Diagnostics::Tracing::EventKeywords::MicrosoftTelemetry },
            { "WdiContext",         Diagnostics::Tracing::EventKeywords::WdiContext         },
            { "Sqm",                Diagnostics::Tracing::EventKeywords::Sqm   },
            { "AuditFailure",       Diagnostics::Tracing::EventKeywords::AuditFailure   },
            { "CorrelationHint",    Diagnostics::Tracing::EventKeywords::CorrelationHint   },
            { "AuditSuccess",       Diagnostics::Tracing::EventKeywords::AuditSuccess   },
            { "EventLogClassic",    Diagnostics::Tracing::EventKeywords::EventLogClassic       }
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventKeywords::All; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventKeywords::EventLogClassic; }
};

}