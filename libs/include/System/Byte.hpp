#pragma once

#include <cstddef>
#include <limits>
#include <algorithm>

namespace Byte
{

class Byte
{
public:
    constexpr Byte() noexcept = default;
    constexpr Byte(const unsigned char initial_value) noexcept
        :
        _value{ initial_value }
    {
    }
    constexpr Byte(const std::byte initial_value) noexcept
        :
        _value{ initial_value }
    {
    }

    static constexpr Byte MaxValue() { return std::numeric_limits<unsigned char>::max(); }
    static constexpr Byte MinValue() { return std::numeric_limits<unsigned char>::min(); }

    static constexpr Byte Clamp(const Byte value, const Byte min, const Byte max)
    {
        return std::clamp( std::uint8_t{value}, std::uint8_t{min}, std::uint8_t{max} );
    }
    
    constexpr operator std::byte() const { return _value; }
protected:
    std::byte _value = 0;
}

}