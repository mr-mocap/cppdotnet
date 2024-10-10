#pragma once

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