#include "TestStopwatch.hpp"
#include "System/Diagnostics/Stopwatch.hpp"
#include "System/Console.hpp"
#include <iostream>
#include <cassert>


namespace TestStopwatch
{

void DefaultConstructed()
{
    std::cout << __func__ << std::endl;

    System::Diagnostics::Stopwatch sw;

    assert( !sw.IsRunning() );
    assert( sw.Elapsed() == System::TimeSpan::Zero() );
    assert( sw.ElapsedMilliseconds() == 0 );
    assert( sw.ElapsedTicks() == 0 );

    System::Console::Out().WriteLine("Frequency = {}", sw.Frequency());
}

void StartNewCreatesANewRunningStopwatch()
{
    std::cout << __func__ << std::endl;

    System::Diagnostics::Stopwatch sw = System::Diagnostics::Stopwatch::StartNew();

    assert( sw.IsRunning() );
    assert( sw.Elapsed() > System::TimeSpan(0) );
}

void StopStopsTheStopwatch()
{
    std::cout << __func__ << std::endl;

    System::Diagnostics::Stopwatch sw = System::Diagnostics::Stopwatch::StartNew();

    assert( sw.IsRunning() );
    assert( sw.Elapsed() > System::TimeSpan(0) );

    sw.Stop();

    assert( !sw.IsRunning() );

    System::Console::Out().WriteLine("Elapsed Time = {}", sw.Elapsed());
}

void Run()
{
    std::cout << "Running Stopwatch Tests..." << std::endl;

    DefaultConstructed();
    StartNewCreatesANewRunningStopwatch();
    StopStopsTheStopwatch();

    std::cout << "PASSED!" << std::endl;
}

}