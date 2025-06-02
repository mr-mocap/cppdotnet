#include "System/Diagnostics/TraceListenerCollection.hpp"
#include "System/Diagnostics/TraceListener.hpp"
#include "System/Diagnostics/Private/DebugAndTraceCommon.hpp"

#include <iterator>


namespace System::Diagnostics
{

TraceListener *TraceListenerCollection::operator [](size_t index)
{
    if ( index >= _list.size() )
        return nullptr;

    auto iter = _list.begin();

    std::advance( iter, index );
    return *iter;
}

TraceListener *TraceListenerCollection::operator [](std::string_view name)
{
    for (TraceListener *iCurrentListener : _list)
    {
        if ( iCurrentListener->Name() == name )
            return iCurrentListener;
    }
    return nullptr;
}

int TraceListenerCollection::Add(TraceListener *listener)
{
    auto inserted_at = _list.insert( listener );

    return (inserted_at.second) ? std::distance( _list.begin(), inserted_at.first ) : -1;
}

void TraceListenerCollection::Remove(TraceListener *listener)
{
    _list.erase( listener );
}

void TraceListenerCollection::Remove(std::string_view name)
{
    for (TraceListener *iCurrentListener : _list)
    {
        if ( iCurrentListener->Name() == name )
            Remove( iCurrentListener );
    }
}

void TraceListenerCollection::Clear()
{
    _list.clear();
}

bool TraceListenerCollection::Contains(TraceListener *listener)
{
    return _list.contains( listener );
}

void TraceListenerCollection::InitializeListener(TraceListener *listener)
{
    listener->IndentSize( Private::DebugAndTraceCommon::IndentSize() );
    listener->IndentLevel( Private::DebugAndTraceCommon::IndentLevel() );
}

size_t TraceListenerCollection::IndexOf(TraceListener *listener)
{
    auto iter_found = _list.find( listener );

    if ( iter_found == _list.end() )
        return 0; // Not Found

    return std::distance( _list.begin(), iter_found );
}

}