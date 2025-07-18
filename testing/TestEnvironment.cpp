#include "TestEnvironment.hpp"
#include "System/Environment.hpp"
#include "System/Exception.hpp"
#include "System/Console.hpp"
#include "System/IO/TextWriter.hpp"
#include <iostream>
#include <cassert>
#include <format>


namespace TestEnvironment
{

void GetEnvrionmentVariable()
{
    using namespace std::literals;

    std::cout << __func__ << std::endl;

    assert( System::Environment::GetEnvironmentVariable( "DISPLAY"sv ) == ":0" );
}

void SetEnvironmentVariable()
{
    using namespace std::literals;

    std::cout << __func__ << std::endl;

    assert( System::Environment::GetEnvironmentVariable( "MY_VAR"sv ).empty() );

    System::Environment::SetEnvironmentVariable( "MY_VAR", "22" );

    assert( System::Environment::GetEnvironmentVariable( "MY_VAR"sv ) == "22" );

    {
        bool threw = false;

        try
        {
            System::Environment::SetEnvironmentVariable( nullptr, nullptr );
        }
        catch(const System::Exception &e)
        {
            threw = true;
            std::string m( std::string("Message=\"").append(e.Message()).append("\"\tTargetSite=\"").append(e.TargetSite()).append("'") );

            System::Console::Out().WriteLine( m );
        }
        assert( threw );
    }
}

void GetEnvironmentVariables()
{
    std::cout << __func__ << std::endl;

    auto variables = System::Environment::GetEnvironmentVariables();
}

void Run()
{
    std::cout << "Running Environment Tests..." << std::endl;

    GetEnvrionmentVariable();
    SetEnvironmentVariable();
    GetEnvironmentVariables();

    std::cout << "PASSED!" << std::endl;
}
}