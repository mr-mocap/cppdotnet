#include <cppdotnet/System/Text/StringBuilder.hpp>
#include <iostream>
#include <cassert>

namespace TestStringBuilder
{

void ReplaceSubstrings()
{
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
    {
        System::Text::StringBuilder builder;

        builder.Append("{}", "Test");
        assert( builder.ToString() == "Test" );
    }

    {
        System::Text::StringBuilder builder;

        builder.Append("This is a {}", "Test");
        assert( builder.ToString() == "This is a Test" );
    }

#if 0
    try
    {
        System::Text::StringBuilder builder;


        builder.Append("{} {}", "Test"); // This will fail to compile because we are missing an argument for the second placeholder
        assert( false );
    }
    catch (std::format_error &e)
    {
        // We need as many arguments as markers
        std::cout << e.what() << std::endl;
        assert( true );
    }
#endif

    {
        System::Text::StringBuilder builder;

        builder.Append("{1} {0}", "a test", "This is");
        assert( builder.ToString() == "This is a test" );
    }
#endif
}

void Run()
{
    ReplaceSubstrings();
    AppendFormat();
}

}

int main(void)
{
    TestStringBuilder::Run();

    return EXIT_SUCCESS;
}