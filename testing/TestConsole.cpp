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

    System::Console::Out().WriteLine("This is a line of text!"sv);
}

void Run()
{
    std::cout << "Running Console Tests..." << std::endl;

    TestOut();

    std::cout << "PASSED!" << std::endl;
}

}