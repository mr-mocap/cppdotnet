#include "System/Diagnostics/TraceListener.hpp"
#include "System/Diagnostics/TraceEventCache.hpp"
#include "System/Convert.hpp"


namespace System::Diagnostics
{

TraceListener::TraceListener()
{
}

TraceListener::TraceListener(std::string_view name)
    :
    _name{ name }
{
}

bool TraceListener::IsThreadSafe() const
{
    return false;
}

std::string_view TraceListener::Name() const
{
    return _name;
}

int TraceListener::IndentLevel() const
{
    return _indentLevel;
}

void TraceListener::IndentLevel(int new_level)
{
    _indentLevel = std::max(new_level, 0);
    _indentString.resize( _indentLevel * _indentSize, ' ' );
    SetNeedIndent();
}

int TraceListener::IndentSize() const
{
    return _indentSize;
}

void TraceListener::IndentSize(int new_size)
{
    _indentSize = std::max(new_size, 0);
    _indentString.resize( _indentLevel * _indentSize, ' ' );
    SetNeedIndent();
}

void TraceListener::SetNeedIndent()
{
    _needIndent = (_indentSize > 0) && (_indentLevel > 0);
}

void TraceListener::TraceData(System::Diagnostics::TraceEventCache &event_cache,
                                                  std::string_view  source,
                               System::Diagnostics::TraceEventType  event_type,
                                                               int  id
                          )
{
    // Treat as a partial function and really call the same method, but with an empty message
    TraceData( event_cache, source, event_type, id, std::string() );
}

void TraceListener::TraceData(System::Diagnostics::TraceEventCache &event_cache,
                                                  std::string_view  source,
                               System::Diagnostics::TraceEventType  event_type,
                                                               int  id,
                                                  std::string_view  message
                          )
{
    if ( !Filter() || (Filter() && Filter()->ShouldTrace( event_cache, source, event_type, id, message ) ) )
    {
        WriteLine("[Trace Header: Source=\"{}\" EventType=\"{}\" ID=\"{}\"]", source, event_type, id);
        WriteLine(message);
        WriteLine("[Trace Footer: Time=\"{}\" PID=\"{}\" TID=\"{}\" Timestamp=\"{}\"]",
                  event_cache.DateTime().ToString(),
                  event_cache.ProcessId(),
                  event_cache.ThreadId(),
                  event_cache.Timestamp()
                 );
    }
}

}
