#include "TestTrace.hpp"
#include "System/Diagnostics/Trace.hpp"
#include "System/Diagnostics/TraceLevel.hpp"
#include "System/Diagnostics/ConsoleTraceListener.hpp"
#include <memory>
#include <iostream>
#include <cassert>

namespace TestTrace
{

static std::unique_ptr<System::Diagnostics::ConsoleTraceListener> ConsoleListener;

void TestSetup()
{
    ConsoleListener = std::make_unique<System::Diagnostics::ConsoleTraceListener>();
    
    System::Diagnostics::Trace::Listeners().Add(ConsoleListener.get());
}

void TestTeardown()
{
    System::Diagnostics::Trace::Listeners().Remove(ConsoleListener.get());

    ConsoleListener.reset();
}

void Write()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Write("This is a message\n"); // We have to add newline here
}

void WriteWithCategory()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Write("This is a message\n", "Test.Category"); // We have to add newline here
}

void WriteWithArgs()
{
    std::cout << __func__ << std::endl;
    
    // This will be interpreted as a message and category (cannot resolve the overload)
    System::Diagnostics::Trace::Write( "This is a message with a parameter: '{}', but will be interpreted as a message and category\n", "string parameter"); // We have to add newline here

    // But we can get around it by using FormatCall
    System::Diagnostics::Trace::Write( System::Diagnostics::FormatCall("This is a message with a string parameter: '{}'\n", "string") ); // We have to add newline here

    // Or by having more than one parameter
    System::Diagnostics::Trace::Write( "This is a message with two parameters: '{}' {}\n", "string", 42); // We have to add newline here

    // Or by using a single parameter that is not convertible to std::string_view
    System::Diagnostics::Trace::Write( "This is a message with a parameter: '{}'\n", 42); // We have to add newline here
}

void WriteIf()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::WriteIf(false, "Test message when FALSE\n"); // We have to add newline here
    System::Diagnostics::Trace::WriteIf(true,  "Test message when TRUE\n"); // We have to add newline here
}

void WriteIfWithCategory()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::WriteIf(false, "This is a message when FALSE\n", "Test.Category"); // We have to add newline here
    System::Diagnostics::Trace::WriteIf(true,  "This is a message when TRUE\n",  "Test.Category"); // We have to add newline here
}

void WriteIfWithArgs()
{
    std::cout << __func__ << std::endl;
    
    // Won't be written
    System::Diagnostics::Trace::WriteIf(false, "This is a message with a parameter: '{}', but will be interpreted as a message and category\n", "string parameter"); // We have to add newline here

    // This will be interpreted as a message and category (cannot resolve the overload)
    System::Diagnostics::Trace::WriteIf(true, "This is a message with a parameter: '{}', but will be interpreted as a message and category\n", "string parameter"); // We have to add newline here

    // But we can get around it by using FormatCall
    System::Diagnostics::Trace::WriteIf(true, System::Diagnostics::FormatCall("This is a message with a string parameter: '{}'\n", "string") ); // We have to add newline here

    // Or by having more than one parameter
    System::Diagnostics::Trace::WriteIf(true, "This is a message with two parameters: '{}' {}\n", "string", 42); // We have to add newline here

    // Or by using a single parameter that is not convertible to std::string_view
    System::Diagnostics::Trace::WriteIf(true, "This is a message with a parameter: '{}'\n", 42); // We have to add newline here
}


void WriteLine()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::WriteLine("This is a message");
    System::Diagnostics::Trace::WriteLine("This is a message with a parameter: {}", 42);
}

void WriteLineWithCategory()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::WriteLine("This is a message", "Test.Category");
}

void WriteLineWithArgs()
{
    std::cout << __func__ << std::endl;
    
    // This will be interpreted as a message and category (cannot resolve the overload)
    System::Diagnostics::Trace::WriteLine( "This is a message with a parameter: '{}', but will be interpreted as a message and category\n", "string parameter");

    // But we can get around it by using FormatCall
    System::Diagnostics::Trace::WriteLine( System::Diagnostics::FormatCall("This is a message with a string parameter: '{}'", "string") );

    // Or by having more than one parameter
    System::Diagnostics::Trace::WriteLine( "This is a message with two parameters: '{}' {}", "string", 42);

    // Or by using a single parameter that is not convertible to std::string_view
    System::Diagnostics::Trace::WriteLine( "This is a message with a parameter: '{}'", 42);
}

void WriteLineIf()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::WriteLineIf(false, "This is a single-line message when FALSE");
    System::Diagnostics::Trace::WriteLineIf(true, "This is a single-line message when TRUE");
}

void WriteLineIfWithCategory()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::WriteLineIf(false, "This is a single-line message when FALSE", "Test.Category");
    System::Diagnostics::Trace::WriteLineIf(true, "This is a single-line message when TRUE", "Test.Category");
}

void WriteLineIfWithArgs()
{
    std::cout << __func__ << std::endl;
    
    // Won't be written
    System::Diagnostics::Trace::WriteLineIf(false, "This is a message with a parameter: '{}', but will be interpreted as a message and category", "string parameter");

    // This will be interpreted as a message and category (cannot resolve the overload)
    System::Diagnostics::Trace::WriteLineIf(true, "This is a message with a parameter: '{}', but will be interpreted as a message and category", "string parameter");

    // But we can get around it by using FormatCall
    System::Diagnostics::Trace::WriteLineIf(true, System::Diagnostics::FormatCall("This is a message with a string parameter: '{}'", "string") );

    // Or by having more than one parameter
    System::Diagnostics::Trace::WriteLineIf(true, "This is a message with two parameters: '{}' {}", "string", 42);

    // Or by using a single parameter that is not convertible to std::string_view
    System::Diagnostics::Trace::WriteLineIf(true, "This is a message with a parameter: '{}'", 42);
}

void TraceAssert()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Assert(false);
    System::Diagnostics::Trace::Assert(true);
}

void TraceAssertWithMessage()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Assert(false, "Trace Assert custom message (FALSE)");
    System::Diagnostics::Trace::Assert(true, "Trace Assert custom message (TRUE)");
}

void TraceAssertWithMessageAndCategory()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Assert(false, "Trace Assert custom message (FALSE)", "Custom.Category");
    System::Diagnostics::Trace::Assert(true, "Trace Assert custom message (TRUE)", "Custom.Category");
}

void TraceAssertWithMessageAndArgs()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Assert(false, System::Diagnostics::FormatCall("This is an Assert message with a string parameter: '{}'", "string") );
}

void TraceFail()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Fail("This is a message for Fail");
}

void TraceFailWithCategory()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::Fail("This is a message for Fail", "Some.Category");
}

void TraceFailWithArgs()
{
    std::cout << __func__ << std::endl;
    
    // This will be interpreted as a message and category (cannot resolve the overload)
    System::Diagnostics::Trace::Fail( "This is a Fail message with a parameter: '{}', but will be interpreted as a message and category\n", "string parameter");

    // But we can get around it by using FormatCall
    System::Diagnostics::Trace::Fail( System::Diagnostics::FormatCall("This is a Fail message with a string parameter: '{}'", "string") );

    // Or by having more than one parameter
    System::Diagnostics::Trace::Fail( "This is a Fail message with two parameters: '{}' {}", "string", 42);

    // Or by using a single parameter that is not convertible to std::string_view
    System::Diagnostics::Trace::Fail( "This is a Fail message with a parameter: '{}'", 42);
}

void TraceError()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::TraceError("This is a Trace Error message");
}

void TraceErrorWithArgs()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::TraceError("This is a Trace Error message with a parameter: {}", 42);
}

void TraceWarning()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::TraceWarning("This is a Trace Warning message");
}

void TraceWarningWithArgs()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::TraceWarning("This is a Trace Warning message with a parameter: {}", 42);
}

void TraceInformation()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::TraceInformation("This is a Trace Information message");
}

void TraceInformationWithArgs()
{
    std::cout << __func__ << std::endl;
    
    System::Diagnostics::Trace::TraceInformation("This is a Trace Information message with a parameter: {}", 42);
}

void IndentLevel()
{
    std::cout << __func__ << std::endl;

    assert( System::Diagnostics::Trace::IndentLevel() == 0 );

    System::Diagnostics::Trace::WriteLine("Indent Level 0");
    System::Diagnostics::Trace::Indent();

    assert( System::Diagnostics::Trace::IndentLevel() == 1 );

    System::Diagnostics::Trace::WriteLine("Indent Level 1");
    System::Diagnostics::Trace::Indent();

    assert( System::Diagnostics::Trace::IndentLevel() == 2 );

    System::Diagnostics::Trace::WriteLine("Indent Level 2");

    System::Diagnostics::Trace::Unindent();

    assert( System::Diagnostics::Trace::IndentLevel() == 1 );

    System::Diagnostics::Trace::WriteLine("Back to Indent Level 1");

    System::Diagnostics::Trace::Unindent();

    assert( System::Diagnostics::Trace::IndentLevel() == 0 );

    System::Diagnostics::Trace::WriteLine("Back to Indent Level 0");
}

void TestTraceLevel()
{
    std::cout << __func__ << std::endl;

    System::Diagnostics::Trace::WriteLine( std::format("As string \"{:s}\"", System::Diagnostics::TraceLevel::Off) );
    System::Diagnostics::Trace::WriteLine( std::format("As int \"{:i}\"", System::Diagnostics::TraceLevel::Off) );

    System::Diagnostics::Trace::WriteLine( std::format("As string \"{:s*<10}\"", System::Diagnostics::TraceLevel::Off) );
    System::Diagnostics::Trace::WriteLine( std::format("As int \"{:i#6x}\"", System::Diagnostics::TraceLevel::Off) );
}

void Run()
{
    std::cout << "Running Trace Tests..." << std::endl;

    TestSetup();
    {
        Write();
        WriteWithCategory();
        WriteWithArgs();
        WriteIf();
        WriteIfWithCategory();
        WriteIfWithArgs();
        WriteLine();
        WriteLineWithCategory();
        WriteLineWithArgs();
        WriteLineIf();
        WriteLineIfWithCategory();
        WriteLineIfWithArgs();
        TraceAssert();
        TraceAssertWithMessage();
        TraceAssertWithMessageAndCategory();
        TraceAssertWithMessageAndArgs();
        TraceFail();
        TraceFailWithCategory();
        TraceFailWithArgs();
        TraceError();
        TraceErrorWithArgs();
        TraceWarning();
        TraceWarningWithArgs();
        TraceInformation();
        TraceInformationWithArgs();
        IndentLevel();
        TestTraceLevel();
    }
    TestTeardown();

    std::cout << "PASSED!" << std::endl;
}

}