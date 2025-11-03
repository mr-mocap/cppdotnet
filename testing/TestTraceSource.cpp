#include <cppdotnet/System/Diagnostics/TraceSource.hpp>
#include <cppdotnet/System/Diagnostics/ConsoleTraceListener.hpp>
#include <cstdlib>
#include <cassert>

namespace TestTraceSource
{

System::Diagnostics::TraceSource SetupTraceSourceWithName(std::string_view name)
{
    System::Diagnostics::TraceSource trace_source(name);
    int index = trace_source.Listeners().Add( std::make_unique<System::Diagnostics::ConsoleTraceListener>() );

    trace_source.Listeners()[index]->Name("console");

    return trace_source;
}

void TraceSourceConstructedWithNameSetsName()
{
    System::Diagnostics::TraceSource trace_source("MyTraceSource");

    assert( trace_source.Name() == "MyTraceSource" );
}

void TraceSourceConstructedWithNameAllOtherValues()
{
    System::Diagnostics::TraceSource trace_source("MyTraceSource");

    assert( trace_source.DefaultLevel() == System::Diagnostics::SourceLevels::Off );
}

void TraceSourceWithConsoleTraceListener()
{
    System::Diagnostics::TraceSource trace_source = SetupTraceSourceWithName("MyTraceSource");

    assert( trace_source.Listeners().Count() == 1 );
    assert( trace_source.Listeners().Contains("console") );

    System::Diagnostics::TraceListener *listener = trace_source.Listeners()["console"];

    listener->TraceOutputOptions( System::Diagnostics::TraceOptions::Callstack );
    trace_source.TraceEvent( System::Diagnostics::TraceEventType::Information, 1 );
}

void TraceSourceWithConsoleTraceListenerTraceInformation()
{
    System::Diagnostics::TraceSource trace_source = SetupTraceSourceWithName("MyTraceSource");

    assert( trace_source.Listeners().Count() == 1 );
    assert( trace_source.Listeners().Contains("console") );

    trace_source.TraceInformation( "This is a trace information message." );
}

void Run()
{
    TraceSourceConstructedWithNameSetsName();
    TraceSourceConstructedWithNameAllOtherValues();
    TraceSourceWithConsoleTraceListener();
    TraceSourceWithConsoleTraceListenerTraceInformation();
}

}

int main(void)
{
    TestTraceSource::Run();
    return EXIT_SUCCESS;
}