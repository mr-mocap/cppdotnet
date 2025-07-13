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
    Debug::Assert(false, "Assert with message and category", "Test.Category");
    Debug::Assert(false, System::Diagnostics::FormatCall("Assert with parameter in message: '{}'", "std::string") );
    Debug::Assert(true, System::Diagnostics::FormatCall("Assert with parameter in message: '{}'", "std::string") );

    Debug::Fail("Debug::Fail()"sv);
    Debug::Fail("Debug::Fail()", "Test.Category");
    Debug::Fail("Debug::Fail()", std::string("Test.Category"));
    Debug::Fail("Debug::Fail() with parameter #{}", 42);
    Debug::Fail("Debug::Fail() with parameter #{} {}", 42, "param");

    // This will be interpreted as a message and category (cannot resolve the overload)
    Debug::Fail("Debug::Fail() with parameter #{}", "param");

    // But we can get around it by using FormatCall
    Debug::Fail( System::Diagnostics::FormatCall("Debug::Fail() with parameter #{}", "param") );

    // Or by having more than one parameter
    Debug::Fail("Debug::Fail() with parameter {} ${}", "param", 16 );

    Debug::WriteLineIf(true, "Debug::WriteLineIf(true, ...)");
    Debug::WriteLineIf(false, "Debug::WriteLineIf(false, ...)");
    Debug::WriteLineIf(true, "Debug::WriteLineIf(true, ...)", "Debug.Category");

    // This will be interpreted as a message and category (cannot resolve the overload)
    Debug::WriteLineIf(true, "Debug::WriteLineIf(true, ...) With Parameter '{}'", "Example Parameter");

    Debug::Listeners().Remove(consoleListener.get());
}

void Run()
{
    std::cout << "Running Debug Tests..." << std::endl;

    CommonUsage();

    std::cout << "PASSED!" << std::endl;
}

}