#pragma once

#include <string_view>
#include <iostream>
#include <format>
#include <cmath>


inline bool is_approximately_equal_to(float input, float near_to, float tolerance = 0.0002f )
{
    return std::abs(near_to - input) <= tolerance;
}

inline bool is_approximately_equal_to(double input, double near_to, float tolerance = 0.0002f )
{
    return std::abs(near_to - input) <= tolerance;
}

bool CheckEqual(std::string_view actual, std::string_view expected)
{
    if ( actual == expected )
        return true;
    
    std::cerr << std::format("Strings are not equal.\nactual   = '{}'\nexpected ='{}'", actual, expected) << '\n';
    return false;
}

template <class E>
bool CheckThrowsException(const auto &function)
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

#define ASSERT_THROWS_EXCEPTION(e, code) assert( CheckThrowsException<e>( [&]{ code; } ) )

#define TEST(name) void name()