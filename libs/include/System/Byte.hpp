#include "System/TypeCode.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <compare>
#include <bit>
#include <format>

namespace System
{

class Byte
{
public:
    constexpr Byte() noexcept = default;
    constexpr Byte(const std::uint8_t initial_value) noexcept
        :
        _value{ initial_value }
    {
    }
    constexpr Byte(const std::byte initial_value) noexcept
        :
        _value{ initial_value }
    {
    }

    static constexpr Byte MaxValue() { return std::numeric_limits<std::uint8_t>::max(); }
    static constexpr Byte MinValue() { return std::numeric_limits<std::uint8_t>::min(); }

    static constexpr Byte Clamp(const Byte value, const Byte min, const Byte max)
    {
        return std::clamp( std::to_integer<std::uint8_t>(value._value), std::to_integer<std::uint8_t>(min._value), std::to_integer<std::uint8_t>(max._value) );
    }
    
    int CompareTo(const Byte other) const
    {
        std::strong_ordering result( *this <=> other );

        if ( result == std::strong_ordering::less )
            return -1;
        else if ( result == std::strong_ordering::equal )
            return 0;
        
        return 1;
    }

    bool Equals(const Byte other) const { return *this == other; }

    TypeCode GetTypeCode() const { return TypeCode::Byte; }
    
    static constexpr bool IsEvenInteger(const Byte value) { return (std::to_integer<std::uint8_t>(value._value) % 2) == 0; }
    static constexpr bool IsOddInteger(const Byte value)  { return !IsEvenInteger(value); }
    static constexpr bool IsPow2(const Byte value)        { return std::has_single_bit( std::to_integer<std::uint8_t>(value._value) ); }
    static constexpr std::byte LeadingZeroCount(const Byte value)
    {
        return static_cast<std::byte>( std::countl_zero( std::to_integer<std::uint8_t>(value._value) ) );
    }

    static constexpr std::byte Min(const Byte left, const Byte right)
    {
        return static_cast<std::byte>( std::min( std::to_integer<std::uint8_t>(left._value),
                                                 std::to_integer<std::uint8_t>(right._value) ) );
    }

    static constexpr std::byte Max(const Byte left, const Byte right)
    {
        return static_cast<std::byte>( std::max( std::to_integer<std::uint8_t>(left._value),
                                                 std::to_integer<std::uint8_t>(right._value) ) );
    }

    static constexpr std::byte PopCount(const Byte value)
    {
        return static_cast<std::byte>( std::popcount( std::to_integer<std::uint8_t>(value._value) ) );
    }

    static constexpr std::byte RotateLeft(const Byte value, int bit_count_to_shift)
    {
        return static_cast<std::byte>( std::rotl( std::to_integer<std::uint8_t>(value._value), bit_count_to_shift ) );
    }

    static constexpr std::byte RotateRight(const Byte value, int bit_count_to_shift)
    {
        return static_cast<std::byte>( std::rotr( std::to_integer<std::uint8_t>(value._value), bit_count_to_shift ) );
    }

    static constexpr int Sign(const Byte value)
    {
        std::int8_t cast_value = std::to_integer<std::int8_t>( value._value );

        if ( cast_value < 0 )
            return -1;
        else if ( cast_value > 0 )
            return 1;
        return 0;
    }

    std::string ToString() const { return std::format("{}", std::to_integer<std::uint8_t>(_value)); }

    static constexpr std::byte TrailingZeroCount(const Byte value)
    {
        return static_cast<std::byte>( std::countr_zero( std::to_integer<std::uint8_t>(value._value) ) );
    }

    constexpr operator std::byte() const { return _value; }
protected:
    std::byte _value{0};

    friend std::strong_ordering operator <=>(const Byte left, const Byte right)
    {
        return left <=> right;
    }
};

}