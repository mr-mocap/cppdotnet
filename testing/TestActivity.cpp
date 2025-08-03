#include "System/Console.hpp"
#include "System/IO/TextWriter.hpp"
#include "System/Diagnostics/ActivitySource.hpp"
#include <cstdlib>

namespace TestActivity
{

void BasicActivity()
{
    System::Diagnostics::ActivitySource source("Example Activity Source");
    std::optional<System::Diagnostics::Activity> activity = source.StartActivity("Example Operation");

    if ( activity )
    {

    }
}

void Run()
{
    System::Console::Out().WriteLine("Running Activity Tests...");

    BasicActivity();
}

}

int main(void)
{
    TestActivity::Run();
    return EXIT_SUCCESS;
}