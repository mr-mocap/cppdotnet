#include <cppdotnet/System/Int32.hpp>
#include <cppdotnet/System/Convert.hpp>


namespace System
{

std::string Int32::ToString() const
{
    return Convert::ToString( _value );
}

int Int32::CompareTo(const Int32 &other) const
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