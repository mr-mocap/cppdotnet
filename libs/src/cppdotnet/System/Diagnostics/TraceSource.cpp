#include <cppdotnet/System/Diagnostics/TraceSource.hpp>
#include <cppdotnet/System/Diagnostics/TraceListener.hpp>
#include <cppdotnet/System/Private/private.hpp>

namespace System::Diagnostics
{

void TraceSource::Close()
{
    for (TraceListener *listener : _listeners)
        listener->Close();
}

void TraceSource::Flush()
{
    for (TraceListener *listener : _listeners)
        listener->Flush();
}

void TraceSource::TraceData(Diagnostics::TraceEventType event_type, int id)
{
    // TODO: Implement Me
    UNUSED(event_type);
    UNUSED(id);
#if 0
    for (TraceListener *listener : _listeners)
        listener->TraceEvent( TraceEventCache{},
                              _name,
                              event_type,
                              id
                            );
#endif
}

void TraceSource::TraceEvent(Diagnostics::TraceEventType event_type, int id)
{
    // TODO: Implement Me
    UNUSED(event_type);
    UNUSED(id);
#if 0
    for (TraceListener *listener : _listeners)
        listener->TraceEvent( TraceEventCache{},
                              _name,
                              event_type,
                              id
                            );
#endif
}

void TraceSource::TraceInformation(std::string_view message)
{
    for (TraceListener *listener : _listeners)
        listener->WriteLine(message);
}

}