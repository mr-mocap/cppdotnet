#include "System/Diagnostics/TraceEventCache.hpp"


namespace System::Diagnostics
{

std::string TraceEventCache::Callstack() const
{
    return "System::Diagnostics::TraceEventCache::Callstack() IMPLEMENT ME!";
}

const std::string_view TraceEventCache::ThreadId() const
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