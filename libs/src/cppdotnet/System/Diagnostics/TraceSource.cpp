#include <cppdotnet/System/Diagnostics/TraceSource.hpp>
#include <cppdotnet/System/Diagnostics/TraceListener.hpp>

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
    for (TraceListener *listener : _listeners)
        listener->TraceEvent( _eventCache,
                              _name,
                              event_type,
                              id
                            );
}

void TraceSource::TraceEvent(Diagnostics::TraceEventType event_type, int id)
{
    for (TraceListener *listener : _listeners)
        listener->TraceEvent( _eventCache,
                              _name,
                              event_type,
                              id
                            );
}

void TraceSource::TraceInformation(std::string_view message)
{
    for (TraceListener *listener : _listeners)
        listener->WriteLine(message);
}

}