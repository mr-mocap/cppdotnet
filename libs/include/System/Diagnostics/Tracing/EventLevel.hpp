
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
struct EnumPolicy<System::Diagnostics::Tracing::EventLevel> : EnumTraitTypes<System::Diagnostics::Tracing::EventLevel>
{
public:

    static constexpr std::string_view EnumName = "EventLevel";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "LogAlways",     Diagnostics::Tracing::EventLevel::LogAlways     },
            { "Critical",      Diagnostics::Tracing::EventLevel::Critical      },
            { "Error",         Diagnostics::Tracing::EventLevel::Error         },
            { "Warning",       Diagnostics::Tracing::EventLevel::Warning       },
            { "Informational", Diagnostics::Tracing::EventLevel::Informational },
            { "Verbose",       Diagnostics::Tracing::EventLevel::Verbose       }
        };
};

}