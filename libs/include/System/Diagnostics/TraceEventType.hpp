#include "System/Private/enum.hpp"

namespace System::Diagnostics
{
    enum class TraceEventType
    {
        Critical    = 0x01,
        Error       = 0x02,
        Warning     = 0x04,
        Information = 0x08,
        Verbose     = 0x10,
        Start       = 0x0100,
        Stop        = 0x0200,
        Suspend     = 0x0400,
        Resume      = 0x0800,
        Transfer    = 0x1000
    };
}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::TraceEventType> : EnumTraitTypes<System::Diagnostics::TraceEventType>
{
    static constexpr std::string_view EnumName = "TraceEventType";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Critical",    Diagnostics::TraceEventType::Critical },
            { "Error",       Diagnostics::TraceEventType::Error    },
            { "Warning",     Diagnostics::TraceEventType::Warning  },
            { "Information", Diagnostics::TraceEventType::Information },
            { "Verbose",     Diagnostics::TraceEventType::Verbose  },
            { "Start",       Diagnostics::TraceEventType::Start    },
            { "Stop",        Diagnostics::TraceEventType::Stop     },
            { "Suspend",     Diagnostics::TraceEventType::Suspend  },
            { "Resume",      Diagnostics::TraceEventType::Resume   },
            { "Transfer",    Diagnostics::TraceEventType::Transfer }
        };
};

}