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

void Run()
{
    std::cout << "Running StringBuilder Tests..." << std::endl;

    ReplaceSubstrings();

    std::cout << "PASSED!" << std::endl;
}

}