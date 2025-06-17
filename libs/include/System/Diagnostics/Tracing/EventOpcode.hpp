#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventOpcode
{
    Info    = 0, //@< An informational event
    Start   = 1, //@< An event that is published when an application starts a new transaction or activity. This operation code can be embedded within another transaction or activity when multiple events that have the Start code follow each other without an intervening event that has a Stop code.
    Stop    = 2, //@< An event that is published when an activity or a transaction in an application ends. The event corresponds to the last unpaired event that has a Start operation code.
    DataCollectionStart = 3, //@< A trace collection start event
    DataCollectionStop  = 4, //@< A trace collection stop event
    Extension = 5,   //@< An extension event
    Reply     = 6,   //@< An event that is published after an activity in an application replies to an event
    Resume    = 7,   //@< An event that is published after an activity in an application resumes from a suspended state. The event should follow an event that has the Suspend operation code.
    Suspend   = 8,   //@< An event that is published when an activity in an application is suspended
    Send      = 9,   //@< An event that is published when one activity in an application transfers data or system resources to another activity
    Receive   = 240, //@< An event that is published when one activity in an application receives data
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventOpcode> : EnumTraitTypes<Diagnostics::Tracing::EventOpcode>
{
    static auto EnumName() -> std::string_view { return "EventOpcode"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Info",                Diagnostics::Tracing::EventOpcode::Info  },
            { "Start",               Diagnostics::Tracing::EventOpcode::Start },
            { "Stop",                Diagnostics::Tracing::EventOpcode::Stop  },
            { "DataCollectionStart", Diagnostics::Tracing::EventOpcode::DataCollectionStart },
            { "DataCollectionStop",  Diagnostics::Tracing::EventOpcode::DataCollectionStop  },
            { "Extension",           Diagnostics::Tracing::EventOpcode::Extension },
            { "Reply",               Diagnostics::Tracing::EventOpcode::Reply     },
            { "Resume",              Diagnostics::Tracing::EventOpcode::Resume    },
            { "Suspend",             Diagnostics::Tracing::EventOpcode::Suspend   },
            { "Send",                Diagnostics::Tracing::EventOpcode::Send      },
            { "Receive",             Diagnostics::Tracing::EventOpcode::Receive   }
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventOpcode::Info; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventOpcode::Receive; }
};

}