module System;

#include "System/Boolean.hpp"


namespace System
{

std::string_view Boolean::FalseString = "False";
std::string_view Boolean::TrueString  = "True";

int Boolean::CompareTo(const Boolean &other) const
{
    auto result{ *this <=> other };

    if ( result == std::strong_ordering::less )
        return -1;
    else if ( result == std::strong_ordering::equal )
        return 0;
    else
        return 1;
}

}