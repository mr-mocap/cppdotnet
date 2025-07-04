#pragma once

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
struct EnumPolicy<System::Diagnostics::TraceOptions>
{
public:
    using value_type = System::Diagnostics::TraceOptions;
    using name_value_pair_type = std::pair<const char *, value_type>;

    static constexpr std::string_view EnumName = "TraceOptions";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",      Diagnostics::TraceOptions::None },
            { "LogicalOperationStack", Diagnostics::TraceOptions::LogicalOperationStack },
            { "DateTime",  Diagnostics::TraceOptions::DateTime },
            { "Timestamp", Diagnostics::TraceOptions::Timestamp },
            { "ProcessId", Diagnostics::TraceOptions::ProcessId },
            { "ThreadId",  Diagnostics::TraceOptions::ThreadId },
            { "Callstack", Diagnostics::TraceOptions::Callstack }
        };
};

}