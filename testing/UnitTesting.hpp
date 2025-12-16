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
int CheckThrowsException(const auto &function)
try
{
    function();
    return 0;
}
catch(const E &)
{
    return 1;
}
catch (...)
{
    return -1;
}

bool CheckThrowsAnyException(const auto &function)
try
{
    function();
    return false;
}
catch (...)
{
    return true;
}

#define ASSERT_THROWS_EXCEPTION(e, code) assert( CheckThrowsException<e>( [&]{ code; } ) == 1 )

#define ASSERT_THROWS_ANY_EXCEPTION(code) assert( CheckThrowsAnyException( [&]{ code; } ) )

#define ASSERT_DOES_NOT_THROW_EXCEPTION(code) assert( !CheckThrowsAnyException( [&]{ code; } ) )

#define TEST(name) void name()