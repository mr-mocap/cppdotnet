
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
struct EnumPolicy<System::Diagnostics::Tracing::EventOpcode> : EnumTraitTypes<System::Diagnostics::Tracing::EventOpcode>
{
public:

    static constexpr std::string_view EnumName = "EventOpcode";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Info",                Diagnostics::Tracing::EventOpcode::Info      },
            { "Start",               Diagnostics::Tracing::EventOpcode::Start     },
            { "Stop",                Diagnostics::Tracing::EventOpcode::Stop      },
            { "DataCollectionStart", Diagnostics::Tracing::EventOpcode::DataCollectionStart },
            { "DataCollectionStop",  Diagnostics::Tracing::EventOpcode::DataCollectionStop  },
            { "Extension",           Diagnostics::Tracing::EventOpcode::Extension },
            { "Reply",               Diagnostics::Tracing::EventOpcode::Reply     },
            { "Resume",              Diagnostics::Tracing::EventOpcode::Resume    },
            { "Suspend",             Diagnostics::Tracing::EventOpcode::Suspend   },
            { "Send",                Diagnostics::Tracing::EventOpcode::Send      },
            { "Receive",             Diagnostics::Tracing::EventOpcode::Receive   }
        };
};

}