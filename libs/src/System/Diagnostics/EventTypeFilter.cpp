#include "System/Diagnostics/EventTypeFilter.hpp"
#include "System/Private/private.hpp"


namespace System::Diagnostics
{

bool EventTypeFilter::ShouldTrace(const TraceEventCache &cache,
                                       std::string_view  source,
                                         TraceEventType  eventType,
                                                    int  id,
                                       std::string_view  formatOrMessage)
{
    //PRECONDITION( is_exactly_one_of(eventType, ) );

    UNUSED(source);
    UNUSED(cache);
    UNUSED(id);
    UNUSED(formatOrMessage);

    unsigned int local_et = static_cast<unsigned int>(EventType());
    unsigned int parameter_et = static_cast<unsigned int>(eventType);

    return parameter_et >= local_et;
}

}