#include "TestConsoleTraceListener.hpp"
#include "Diagnostics.hpp"
#include <iostream>
#include <cassert>

namespace TestConsoleTraceListener
{

void CommonUsage()
{
    using namespace std::literals;

    std::cout << __func__ << std::endl;

    std::unique_ptr<System::Diagnostics::ConsoleTraceListener> consoleListener = std::make_unique<System::Diagnostics::ConsoleTraceListener>();

    assert( System::Diagnostics::Trace::Listeners().Count() == 1);
    
    System::Diagnostics::Trace::Listeners().Add( consoleListener.get() );

    assert( System::Diagnostics::Trace::Listeners().Count() == 2);

    consoleListener->WriteLine("This is a test!"sv);
    consoleListener->IndentSize(4);
    consoleListener->IndentLevel(1);

    consoleListener->WriteLine("This is indented once"sv);
    consoleListener->IndentLevel(2);
    consoleListener->WriteLine("This is indented twice"sv);

    consoleListener->Fail("This is a failure!"sv);

    System::Diagnostics::Debug::Assert(false);
    System::Diagnostics::Trace::Listeners().Remove( consoleListener.get() );
}

void Run()
{
    std::cout << "Running ConsoleTraceListener Tests..." << std::endl;

    CommonUsage();

    std::cout << "PASSED!" << std::endl;
}

}