#pragma once

#include <cppdotnet/System/DateTime.hpp>
#include <optional>
#include <string>


namespace System::Diagnostics
{

class TraceEventCache
{
public:
    TraceEventCache() = default;

    std::string Callstack() const;

    /** Gets the date and time of the event
     * 
     *  @return const System::DateTime & 
     *   
     *  @note DateTime is in UTC.
     *  @note Caches the value after the first call.
     */
    const System::DateTime &DateTime() const;

#if 0
    Collections::Stack LogicalOperationStack() const;
#endif

    int ProcessId() const;

    std::string_view ThreadId() const;

    long Timestamp() const;

protected:
    mutable std::optional<System::DateTime> _datetime;
    mutable std::optional<std::string>      _thread_id;
    mutable std::optional<int>              _process_id;
};

}