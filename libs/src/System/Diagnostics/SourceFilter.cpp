#include "System/Diagnostics/SourceFilter.hpp"


namespace System::Diagnostics
{

bool SourceFilter::ShouldTrace(const TraceEventCache  &cache,
                               std::string_view  source,
                                     TraceEventType    eventType,
                                     int               id,
                               std::string_view  formatOrMessage)
{
    UNUSED(cache);
    UNUSED(eventType);
    UNUSED(id);
    UNUSED(formatOrMessage);

    return source == Source();
}

}