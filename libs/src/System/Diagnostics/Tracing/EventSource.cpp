import "System/Diagnostics/Tracing/EventSource.hpp";
import "System/Exception.hpp";


namespace System::Diagnostics::Tracing
{

void EventSource::Write(std::string_view event_name)
{
    if ( event_name.empty() )
        ThrowWithTarget( ArgumentNullException( "event_name" ) );
}

}