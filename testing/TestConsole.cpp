#include "TestConsole.hpp"
#include "System/Console.hpp"
#include "System/IO/StringReader.hpp"
#include "System/IO/StringWriter.hpp"
#include "System/IO/StreamReader.hpp"
#include "System/IO/StreamWriter.hpp"
#include <iostream>
#include <string_view>

namespace TestConsole
{

void TestOut()
{
    using namespace std::literals;

    std::cout << __func__ << std::endl;

    System::Console::WriteLine("This is a line of text!"sv);
    System::Console::WriteLine("Integer Value: {}"sv, 42);
    System::Console::WriteLine("Here is a string: \"{}\""sv, "WaHoo!  We Did It!");

    System::Console::WriteLine("One Argument: {}"sv, 1);
    System::Console::WriteLine("Two Arguments: {}, {}"sv, 1, 2);
    System::Console::WriteLine("Three Arguments: {}, {}, {}"sv, 1, 2, 3);
    System::Console::WriteLine("Four Arguments: {}, {}, {}, {}"sv, 1, "two", 3.14159, "four"sv);

    System::Console::Write("This is a line of text!"sv);
    System::Console::Write( System::Console::Out().NewLine() );

    System::Console::Write("Integer Value: {}"sv, 24);
    System::Console::Write( System::Console::Out().NewLine() );
    System::Console::WriteLine("Here is a string: \"{}\""sv, "WaHoo!  We Also Did It!");
    System::Console::Write( System::Console::Out().NewLine() );
}

void SetIn()
{
    std::cout << __func__ << std::endl;

    std::string initial_data = "This is a line\nThe second line.";

    // It is NOT redirected initially
    assert( !System::Console::IsInputRedirected() );

    // We redirect it
    System::Console::SetIn( std::make_unique<System::IO::StringReader>(initial_data) );

    // And now it IS redirected
    assert( System::Console::IsInputRedirected() );

    System::Console::WriteLine( System::Console::ReadLine() );

    // Set it back to what it is by default
    System::Console::SetIn( std::make_unique<System::IO::StreamReader>(System::Console::OpenStandardInput()) );

    // And now it is NOT redirected
    assert( !System::Console::IsInputRedirected() );
}

void SetOut()
{
    std::cout << __func__ << std::endl;

    // It is NOT redirected initially
    assert( !System::Console::IsOutputRedirected() );

    // We redirect it
    System::Console::SetOut( std::make_unique<System::IO::StringWriter>() );

    // And now it IS redirected
    assert( System::Console::IsOutputRedirected() );

    // Set it back to what it is by default
    System::Console::SetOut( std::make_unique<System::IO::StreamWriter>(System::Console::OpenStandardOutput()) );

    // And now it is NOT redirected
    assert( !System::Console::IsOutputRedirected() );
}

void SetError()
{
    std::cout << __func__ << std::endl;

    // It is NOT redirected initially
    assert( !System::Console::IsErrorRedirected() );

    // We redirect it
    System::Console::SetError( std::make_unique<System::IO::StringWriter>() );

    // And now it IS redirected
    assert( System::Console::IsErrorRedirected() );

    // Set it back to what it is by default
    System::Console::SetError( std::make_unique<System::IO::StreamWriter>(System::Console::OpenStandardError()) );

    // And now it is NOT redirected
    assert( !System::Console::IsErrorRedirected() );
}

void Run()
{
    std::cout << "Running Console Tests..." << std::endl;

    TestOut();
    SetIn();
    SetOut();
    SetError();

    std::cout << "PASSED!" << std::endl;
}

}