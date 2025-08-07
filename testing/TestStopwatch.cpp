#include "System/Diagnostics/Stopwatch.hpp"
#include "System/Console.hpp"
#include "System/IO/TextWriter.hpp"
#include <iostream>
#include <cassert>


namespace TestStopwatch
{

void DefaultConstructed()
{
    System::Diagnostics::Stopwatch sw;

    assert( !sw.IsRunning() );
    assert( sw.Elapsed() == System::TimeSpan::Zero() );
    assert( sw.ElapsedMilliseconds() == 0 );
    assert( sw.ElapsedTicks() == 0 );

    System::Console::Out().WriteLine("Frequency = {}", sw.Frequency());
}

void StartNewCreatesANewRunningStopwatch()
{
    System::Diagnostics::Stopwatch sw = System::Diagnostics::Stopwatch::StartNew();

    assert( sw.IsRunning() );
    assert( sw.Elapsed() > System::TimeSpan(0) );
}

void StopStopsTheStopwatch()
{
    System::Diagnostics::Stopwatch sw = System::Diagnostics::Stopwatch::StartNew();

    assert( sw.IsRunning() );
    assert( sw.Elapsed() > System::TimeSpan(0) );

    sw.Stop();

    assert( !sw.IsRunning() );

    System::Console::Out().WriteLine("Measured {}", sw);
}

void ResetStopsMeasurementAndClearsElapsedTime()
{
    System::Diagnostics::Stopwatch sw = System::Diagnostics::Stopwatch::StartNew();

    assert( sw.IsRunning() );
    assert( sw.Elapsed() > System::TimeSpan(0) );

    sw.Reset();

    assert( !sw.IsRunning() );
    assert( sw.Elapsed() == System::TimeSpan(0) );
}

void RestartClearsElapsedTimeAndStartsRunning()
{
    System::Diagnostics::Stopwatch sw = System::Diagnostics::Stopwatch::StartNew();

    assert( sw.IsRunning() );
    assert( sw.Elapsed() > System::TimeSpan(0) );

    sw.Restart();

    assert( sw.IsRunning() );
    assert( sw.Elapsed() > System::TimeSpan(0) );
}

void Run()
{
    DefaultConstructed();
    StartNewCreatesANewRunningStopwatch();
    StopStopsTheStopwatch();
    ResetStopsMeasurementAndClearsElapsedTime();
}

}

int main(void)
{
    TestStopwatch::Run();

    return EXIT_SUCCESS;
}