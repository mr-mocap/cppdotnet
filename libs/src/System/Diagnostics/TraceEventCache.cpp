#include "System/Diagnostics/TraceEventCache.hpp"
#include "System/Environment.hpp"


namespace System::Diagnostics
{

std::string TraceEventCache::Callstack() const
{
    return Environment::StackTrace();
}

const System::DateTime &TraceEventCache::DateTime() const
{
    if ( !_datetime.has_value() )
        _datetime.emplace( System::DateTime::UtcNow() );
    return _datetime.value();
}

#if 0
Collections::Stack TraceEventCache::LogicalOperationStack() const
{
}
#endif

std::string_view TraceEventCache::ThreadId() const
{
    using namespace std::literals;

    return "System::Diagnostics::TraceEventCache::ThreadId() IMPLEMENT ME!"sv;
}

int TraceEventCache::ProcessId() const
{
    // TODO: FIXME
    return 0;
}

}