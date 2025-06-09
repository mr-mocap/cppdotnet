#include "System/Diagnostics/TraceFilter.hpp"
#include <format>


namespace System::Diagnostics
{

bool TraceFilter::ShouldTrace(const TraceEventCache  &cache,
                                    std::string_view  source,
                                      TraceEventType  eventType,
                                                 int  id,
                                    std::string_view  formatOrMessage)
{
    UNUSED(cache);
    UNUSED(source);
    UNUSED(eventType);
    UNUSED(id);
    UNUSED(formatOrMessage);

    return true;
}

}