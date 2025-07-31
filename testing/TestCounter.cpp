#include "System/Console.hpp"
#include "System/Diagnostics/Metrics/Meter.hpp"
#include "System/IO/TextWriter.hpp"
#include <cassert>


namespace TestCounter
{

void CreateCounter()
{
    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");

    assert( counter.Name() == "ExampleCounter" );
    assert( counter.Unit() == "Ticks" );
    assert( counter.Description() == "This is just an example" );
    assert( !counter.Enabled() );
    assert( counter.Meter().Name() == meter.Name() );
    assert( &counter.Meter() == &meter );
    assert( !counter.IsObservable() );
}

void AddingAMeasurement()
{
    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");

    counter.Add(1);
}

void Run()
{
    CreateCounter();
    AddingAMeasurement();
}

}

int main(void)
{
    TestCounter::Run();

    return EXIT_SUCCESS;
}