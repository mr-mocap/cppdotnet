#include <cppdotnet/System/Console.hpp>
#include <cppdotnet/System/IO/TextWriter.hpp>
#include <cppdotnet/System/Diagnostics/ActivitySource.hpp>
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
    BasicActivity();
}

}

int main(void)
{
    TestActivity::Run();
    return EXIT_SUCCESS;
}