#include "TestStringBuilder.hpp"
#include "System/Text/StringBuilder.hpp"
#include <iostream>
#include <cassert>

namespace TestStringBuilder
{

void ReplaceSubstrings()
{
    std::cout << __func__ << std::endl;

    const char *init = "This is just a test of the ability of the StringBuilder "
                       "to handle the proper replacement of substrings that are "
                       "larger than what is being searched for";

    // With larger substrings
    {
        System::Text::StringBuilder builder{init};

        builder.Replace("is", "WAS");

        std::cout << builder.ToString() << std::endl;
    }
}

void AppendFormat()
{
#ifdef __cpp_lib_format
    std::cout << __func__ << std::endl;

    {
        System::Text::StringBuilder builder;

        builder.AppendFormat("{}", "Test");
        assert( builder.ToString() == "Test" );
    }

    {
        System::Text::StringBuilder builder;

        builder.AppendFormat("This is a {}", "Test");
        assert( builder.ToString() == "This is a Test" );
    }

    try
    {
        System::Text::StringBuilder builder;

        builder.AppendFormat("{} {}", "Test");
        assert( false );
    }
    catch (std::format_error &e)
    {
        // We need as many arguments as markers
        std::cout << e.what() << std::endl;
        assert( true );
    }

    {
        System::Text::StringBuilder builder;

        builder.AppendFormat("{1} {0}", "a test", "This is");
        assert( builder.ToString() == "This is a test" );
    }
#endif
}

void Run()
{
    std::cout << "Running StringBuilder Tests..." << std::endl;

    ReplaceSubstrings();
    AppendFormat();

    std::cout << "PASSED!" << std::endl;
}

}