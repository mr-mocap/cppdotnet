#include "TestConsole.hpp"
#include "System/Console.hpp"
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

void Run()
{
    std::cout << "Running Console Tests..." << std::endl;

    TestOut();

    std::cout << "PASSED!" << std::endl;
}

}