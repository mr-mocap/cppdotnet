module System;

#include "System/Int64.hpp"
#include "System/Convert.hpp"


namespace System
{

std::string Int64::ToString() const
{
    return Convert::ToString( _value );
}

int Int64::CompareTo(const Int64 &other) const
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