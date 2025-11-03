#include <cppdotnet/System/Diagnostics/TraceSource.hpp>
#include <cppdotnet/System/Diagnostics/ConsoleTraceListener.hpp>
#include <cstdlib>
#include <cassert>

namespace TestTraceSource
{

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
    System::Diagnostics::TraceSource trace_source("MyTraceSource");

    int index = trace_source.Listeners().Add( std::make_unique<System::Diagnostics::ConsoleTraceListener>() );

    trace_source.Listeners()[index]->Name("console");

    assert( trace_source.Listeners().Count() == 1 );

    System::Diagnostics::TraceListener *listener = trace_source.Listeners()["console"];

    listener->TraceOutputOptions( System::Diagnostics::TraceOptions::Callstack );
    trace_source.TraceEvent( System::Diagnostics::TraceEventType::Information, 1 );
}

void Run()
{
    TraceSourceConstructedWithNameSetsName();
    TraceSourceConstructedWithNameAllOtherValues();
    TraceSourceWithConsoleTraceListener();
}

}

int main(void)
{
    TestTraceSource::Run();
    return EXIT_SUCCESS;
}