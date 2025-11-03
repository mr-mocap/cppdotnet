#include <cppdotnet/System/Diagnostics/TraceEventCache.hpp>
#include <cppdotnet/System/Diagnostics/Stopwatch.hpp>
#include <cppdotnet/System/Environment.hpp>
#include <thread>
#include <format>
#include <sstream>
#include <unistd.h> // For getpid() (NOTE: Can we use this under Windows?)

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
    if ( !_thread_id.has_value() )
    {
        std::thread::id thread_id = std::this_thread::get_id();

#ifdef __cpp_lib_formatters
        _thread_id = std::format( "{}", thread_id );
#else
        std::ostringstream oss;

        oss << thread_id;
        _thread_id = oss.str();
#endif
    }

    return _thread_id.value();
}

int TraceEventCache::ProcessId() const
{
    if ( !_process_id.has_value() )
        _process_id = static_cast<int>( ::getpid() );

    return _process_id.value();
}

long TraceEventCache::Timestamp() const
{
    return Stopwatch::GetTimestamp();
}

}