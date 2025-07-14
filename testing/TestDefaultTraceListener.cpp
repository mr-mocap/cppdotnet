#include "TestDefaultTraceListener.hpp"
#include "Diagnostics.hpp"
#include <iostream>
#include <memory>
#include <cassert>

namespace TestDefaultTraceListener
{

void AccessingListenersFirstTimeCreatesDefaultTraceListener()
{
    std::cout << __func__ << std::endl;

    assert( System::Diagnostics::Trace::Listeners().Count() == 1 );
    assert( System::Diagnostics::Trace::Listeners()["Default"] );

    System::Diagnostics::Trace::WriteLine("This is a test!");
    System::Diagnostics::Trace::WriteLineIf(true, "This is the value {}", 42);
    
    // Doesn't output anything
    System::Diagnostics::Trace::WriteLineIf(false, "This is the value {}", 42);
}

void Run()
{
    std::cout << "Running DefaultTraceListener Tests..." << std::endl;

    AccessingListenersFirstTimeCreatesDefaultTraceListener();

    std::cout << "PASSED!" << std::endl;
}

}