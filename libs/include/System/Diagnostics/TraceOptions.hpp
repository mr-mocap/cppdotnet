#include "System/Private/enum.hpp"

namespace System::Diagnostics
{

enum class TraceOptions
{
    None = 0,
    LogicalOperationStack = 1,
    DateTime = 2,
    Timestamp = 4,
    ProcessId = 8,
    ThreadId = 16,
    Callstack = 32
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::TraceOptions> : EnumTraitTypes<System::Diagnostics::TraceOptions>
{
    static constexpr std::string_view EnumName = "TraceOptions";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",      Diagnostics::TraceOptions::None      },
            { "LogicalOperationStack", Diagnostics::TraceOptions::LogicalOperationStack },
            { "DateTime",  Diagnostics::TraceOptions::DateTime  },
            { "Timestamp", Diagnostics::TraceOptions::Timestamp },
            { "ProcessId", Diagnostics::TraceOptions::ProcessId },
            { "ThreadId",  Diagnostics::TraceOptions::ThreadId  },
            { "Callstack", Diagnostics::TraceOptions::Callstack }
        };
};

}