#include "System/Diagnostics/SourceFilter.hpp"


namespace System::Diagnostics
{

bool SourceFilter::ShouldTrace(const TraceEventCache  &cache,
                               const std::string_view  source,
                                     TraceEventType    eventType,
                                     int               id,
                               const std::string_view  formatOrMessage)
{
    UNUSED(cache);
    UNUSED(eventType);
    UNUSED(id);
    UNUSED(formatOrMessage);

    return source == Source();
}

}