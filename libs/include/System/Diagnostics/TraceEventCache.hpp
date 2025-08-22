#include "System/DateTime.hpp"
#include <optional>
#include <string>


namespace System::Diagnostics
{

class TraceEventCache
{
public:
    TraceEventCache() = default;

    std::string Callstack() const;

    const System::DateTime &DateTime() const;

#if 0
    Collections::Stack LogicalOperationStack() const;
#endif

    int ProcessId() const;

    std::string_view ThreadId() const;

    long Timestamp() const { return DateTime().Ticks(); }

protected:
    mutable std::optional<System::DateTime> _datetime;
};

}