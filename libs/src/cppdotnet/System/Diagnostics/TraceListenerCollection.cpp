#include <cppdotnet/System/Diagnostics/TraceListenerCollection.hpp>
#include <cppdotnet/System/Diagnostics/TraceListener.hpp>
#include <cppdotnet/System/Diagnostics/Private/DebugAndTraceCommon.hpp>

#include <iterator>
#include <utility>


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

int TraceListenerCollection::Add(std::unique_ptr<TraceListener> &&listener)
{
    auto inserted_at = _list.insert( listener.release());

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
        {
            std::unique_ptr<TraceListener> to_delete( iCurrentListener );

            Remove( to_delete.get() );
        }
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

size_t TraceListenerCollection::IndexOf(TraceListener *listener)
{
    auto iter_found = _list.find( listener );

    if ( iter_found == _list.end() )
        return 0; // Not Found

    return std::distance( _list.begin(), iter_found );
}

}