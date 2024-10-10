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

    std::unique_ptr<System::Diagnostics::DefaultTraceListener> defaultListener = std::make_unique<System::Diagnostics::DefaultTraceListener>();

    assert( System::Diagnostics::Debug::Listeners().Count() == 1);

    defaultListener->WriteLine("This is a test!");
}

void Run()
{
    std::cout << "Running DefaultTraceListener Tests..." << std::endl;

    CommonUsage();

    std::cout << "PASSED!" << std::endl;
}

}