#pragma once

#include "System/DateTime.hpp"


namespace System::Diagnostics
{

class TraceEventCache
{
public:
    TraceEventCache() = default;

    std::string Callstack() const;

    const System::DateTime &DateTime() const { return _datetime; }

    long Timestamp() const { return _timestamp; }

    std::string_view ThreadId() const;

    int ProcessId() const;

#if 0
    Collections::Stack LogicalOperationStack() const;
#endif
protected:
    System::DateTime _datetime;
    long _timestamp = 0;
};

}