#include <cppdotnet/System/UInt16.hpp>
#include <cppdotnet/System/Convert.hpp>


namespace System
{

std::string UInt16::ToString() const
{
    return Convert::ToString( _value );
}

int UInt16::CompareTo(const UInt16 &other) const
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
