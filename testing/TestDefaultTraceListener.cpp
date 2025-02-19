#include "TestDefaultTraceListener.hpp"
#include "Diagnostics.hpp"
#include <iostream>
#include <memory>
#include <cassert>

namespace TestDefaultTraceListener
{

void CommonUsage()
{
    std::cout << __func__ << std::endl;

    assert( System::Diagnostics::Debug::Listeners().Count() == 1 );

    System::Diagnostics::Debug::WriteLine("This is a test!");
}

void Run()
{
    std::cout << "Running DefaultTraceListener Tests..." << std::endl;

    CommonUsage();

    std::cout << "PASSED!" << std::endl;
}

}