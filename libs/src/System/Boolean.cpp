#include "System/Boolean.hpp"

using namespace std::literals;

namespace System
{

const std::string_view Boolean::FalseString = "False"sv;
const std::string_view Boolean::TrueString  = "True"sv;

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