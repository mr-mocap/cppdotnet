#include "TestDebug.hpp"
#include "System/Diagnostics/ConsoleTraceListener.hpp"
#include "System/Diagnostics/Debug.hpp"
#include <string_view>

namespace TestDebug
{

void CommonUsage()
{
    using namespace std::literals;
    using namespace System::Diagnostics;

    std::cout << __func__ << std::endl;

    std::unique_ptr<System::Diagnostics::ConsoleTraceListener> consoleListener = std::make_unique<System::Diagnostics::ConsoleTraceListener>();
    
    Debug::Listeners().Add(consoleListener.get());

    Debug::Print("Debug::Print()"sv);
    Debug::Indent();
    Debug::Print("Debug::Print()"sv);
    Debug::Unindent();

    Debug::Print("The number is {}", 6);

    Debug::Write("Debug::Write()"sv);
    Debug::WriteLine("Debug::Write()"sv);

    Debug::Assert(false);
    Debug::Assert(false, "Assert with message");
    Debug::Assert(false, "Assert with parameter in message: '{}'", "std::string");

    Debug::Fail("Debug::Fail()"sv);
    Debug::Fail("Debug::Fail() #{}", 42);

    Debug::WriteLineIf(true, "Debug::WriteLineIf(true, ...)"sv);
    Debug::WriteLineIf(false, "Debug::WriteLineIf(false, ...)"sv);

    Debug::Listeners().Remove(consoleListener.get());
}

void Run()
{
    std::cout << "Running Debug Tests..." << std::endl;

    CommonUsage();

    std::cout << "PASSED!" << std::endl;
}

}