#include <cppdotnet/Diagnostics.hpp>
#include <iostream>
#include <cassert>

namespace TestConsoleTraceListener
{

void CommonUsage()
{
    using namespace std::literals;

    std::unique_ptr<System::Diagnostics::ConsoleTraceListener> consoleListener = std::make_unique<System::Diagnostics::ConsoleTraceListener>();
    System::Diagnostics::ConsoleTraceListener *consoleListenerPtr = consoleListener.get();

    assert( System::Diagnostics::Trace::Listeners().Count() == 1);
    
    System::Diagnostics::Trace::Listeners().Add( std::move( consoleListener ) );

    assert( System::Diagnostics::Trace::Listeners().Count() == 2);

    consoleListenerPtr->WriteLine("This is a test!"sv);
    consoleListenerPtr->IndentSize(4);
    consoleListenerPtr->IndentLevel(1);

    consoleListenerPtr->WriteLine("This is indented once"sv);
    consoleListenerPtr->IndentLevel(2);
    consoleListenerPtr->WriteLine("This is indented twice"sv);

    consoleListenerPtr->Fail("This is a failure!"sv);

    System::Diagnostics::Debug::Assert(false);
    System::Diagnostics::Trace::Listeners().Remove( consoleListenerPtr );
}

void Run()
{
    CommonUsage();
}

}

int main(void)
{
    TestConsoleTraceListener::Run();

    return EXIT_SUCCESS;
}