#include "TestCounter.hpp"
#include "System/Console.hpp"
#include "System/Diagnostics/Metrics/Meter.hpp"


namespace TestCounter
{

void CreateCounter()
{
    System::Console::Out().WriteLine(__func__);

    System::Diagnostics::Metrics::Meter meter("ExampleMeter");
    System::Diagnostics::Metrics::Counter<int> counter = meter.CreateCounter<int>("ExampleCounter", "Ticks", "This is just an example");
}

void Run()
{
    System::Console::Out().WriteLine("Running TestCounter Tests...");

    CreateCounter();

    System::Console::Out().WriteLine("PASSED!");
}

}