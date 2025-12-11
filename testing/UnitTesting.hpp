#pragma once

#include <string_view>
#include <iostream>
#include <format>


bool CheckEqual(std::string_view actual, std::string_view expected)
{
    if ( actual == expected )
        return true;
    
    std::cerr << std::format("Strings are not equal.\nactual   = '{}'\nexpected ='{}'", actual, expected) << '\n';
    return false;
}

template <class E>
bool CheckThrowsException(const auto &function)
{
    try
    {
        function();
        return false;
    }
    catch(const E &)
    {
        return true;
    }
    catch (...)
    {
        return false;
    }
}

#define ASSERT_THROWS_EXCEPTION(e, code) assert( CheckThrowsException<e>( [&]{ code; } ) )

#define TEST(name) void name()