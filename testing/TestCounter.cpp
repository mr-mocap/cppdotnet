#include "TestCounter.hpp"
#include "System/Console.hpp"
#include "System/Diagnostics/Metrics/Meter.hpp"
#include "System/IO/TextWriter.hpp"
#include <cassert>


namespace TestCounter
{

void CreateCounter()
{
    System::Console::Out().WriteLine(__func__);

    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");
}

void CounterName()
{
    System::Console::Out().WriteLine(__func__);

    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");

    assert( counter.Name() == "ExampleCounter" );
}

void CounterDescription()
{
    System::Console::Out().WriteLine(__func__);

    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");

    assert( counter.Description() == "This is just an example" );
}

void CounterUnit()
{
    System::Console::Out().WriteLine(__func__);

    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");

    assert( counter.Unit() == "Ticks" );
}

void CounterContainsExternalMeter()
{
    System::Console::Out().WriteLine(__func__);

    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");

    assert( &counter.Meter() == &meter );
}

void AddingAMeasurement()
{
    System::Console::Out().WriteLine(__func__);

    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");

    counter.Add(1);
}

void Run()
{
    System::Console::Out().WriteLine("Running TestCounter Tests...");

    CreateCounter();
    CounterName();
    CounterUnit();
    CounterContainsExternalMeter();
    AddingAMeasurement();

    System::Console::Out().WriteLine("PASSED!");
}

}