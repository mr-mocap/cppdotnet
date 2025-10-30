#pragma once

#include <cppdotnet/System/TypeCode.hpp>
#include <cppdotnet/System/Private/IntCommon.hpp>
#include <cstdint>
#include <limits>
#include <cmath>
#include <algorithm>
#include <compare>

namespace System
{

class UInt32 : public IntCommon<std::uint32_t, UInt32>
{
public:
    constexpr UInt32() = default;
    constexpr UInt32(const std::uint32_t initial_value) : _value{ initial_value } { }

    static constexpr UInt32 MaxValue() { return std::numeric_limits<std::uint32_t>::max(); }
    static constexpr UInt32 MinValue() { return std::numeric_limits<std::uint32_t>::min(); }

    /** @name IConvertible Interface
     *  @{
     */
    TypeCode GetTypeCode() const { return TypeCode::UInt32; }

    bool ToBoolean() const { return _value; }

    std::byte ToByte() const { return static_cast<std::byte>(_value); }

    char ToChar() const { return static_cast<char>(_value); }

    std::int16_t ToInt16() const { return static_cast<std::int16_t>(_value); }
    std::int32_t ToInt32() const { return static_cast<std::int32_t>(_value); }
    std::int64_t ToInt64() const { return static_cast<std::int64_t>(_value); }

    std::uint16_t ToUInt16() const { return static_cast<std::uint16_t>(_value); }
    std::uint32_t ToUInt32() const { return _value; }
    std::uint64_t ToUInt64() const { return _value; }

    float  ToSingle() const { return static_cast<float>(_value); }
    double ToDouble() const { return static_cast<double>(_value); }

    std::string ToString() const;
    /// @}

    /** @name IComparable Interface
     *  @{
     */
    int CompareTo(const UInt32 &other) const;
    /// @}

    /** @name IEquatable Interface
     *  @{
     */
    constexpr bool Equals(const UInt32 &other) const { return *this == other; }
    /// @}

    constexpr operator std::uint32_t() const { return _value; }

    // C++ specific stuff.
    // NOTE: We need the <=> AND == operators ONLY, if we want all the other relational
    //       operators to be generated automatically for us.
    constexpr std::strong_ordering operator <=>(const UInt32 other) const { return _value <=> other._value; }
    constexpr std::strong_ordering operator <=>(const std::uint32_t other) const { return _value <=> other; }

    constexpr bool operator ==(const UInt32 &other) const { return _value == other._value; }
    constexpr bool operator ==(const std::uint32_t other) const { return _value == other; }

    /** @name Basic Operations
     *  @{
     */
    constexpr UInt32 &operator +=(const UInt32 &other)
    {
        _value += other._value;
        return *this;
    }

    constexpr UInt32 &operator -=(const UInt32 &other)
    {
        _value -= other._value;
        return *this;
    }

    constexpr UInt32 &operator *=(const UInt32 &other)
    {
        _value *= other._value;
        return *this;
    }

    constexpr UInt32 &operator /=(const UInt32 &other)
    {
        _value /= other._value;
        return *this;
    }

    constexpr UInt32 &operator %=(const UInt32 &other)
    {
        _value %= other._value;
        return *this;
    }

    constexpr UInt32 &operator &=(const UInt32 &other)
    {
        _value &= other._value;
        return *this;
    }

    constexpr UInt32 &operator |=(const UInt32 &other)
    {
        _value |= other._value;
        return *this;
    }

    constexpr UInt32 &operator ^=(const UInt32 &other)
    {
        _value ^= other._value;
        return *this;
    }

    constexpr UInt32 &operator <<=(const UInt32 &other)
    {
        _value <<= other._value;
        return *this;
    }

    constexpr UInt32 &operator >>=(const UInt32 &other)
    {
        _value >>= other._value;
        return *this;
    }

    constexpr UInt32 operator +(const UInt32 &right) const
    {
        return UInt32{ _value + right._value };
    }

    constexpr UInt32 operator +(const std::uint32_t right) const
    {
        return UInt32{ _value + right };
    }

    constexpr UInt32 operator -(const UInt32 &right) const
    {
        return UInt32{ _value - right._value };
    }

    constexpr UInt32 operator -(const std::uint32_t right) const
    {
        return UInt32{ _value - right };
    }

    constexpr UInt32 operator *(const UInt32 &right) const
    {
        return UInt32{ _value * right._value };
    }

    constexpr UInt32 operator *(const std::uint32_t right) const
    {
        return UInt32{ _value * right };
    }

    constexpr UInt32 operator /(const UInt32 &right) const
    {
        return UInt32{ _value / right._value };
    }

    constexpr UInt32 operator /(const std::uint32_t right) const
    {
        return UInt32{ _value / right };
    }

    constexpr UInt32 operator %(const UInt32 &right) const
    {
        return UInt32{ _value % right };
    }

    constexpr UInt32 operator %(const std::uint32_t right) const
    {
        return UInt32{ _value % right };
    }

    constexpr UInt32 operator +() const
    {
        return *this;
    }

    constexpr UInt32 operator -() const
    {
        return UInt32{ -_value };
    }

    constexpr UInt32 operator ~() const
    {
        return UInt32{ ~_value };
    }

    constexpr UInt32 operator &(const UInt32 &other)
    {
        return UInt32{ _value & other._value };
    }

    constexpr UInt32 operator |(const UInt32 &other)
    {
        return UInt32{ _value | other._value };
    }

    constexpr UInt32 operator ^(const UInt32 &other)
    {
        return UInt32{ _value ^ other._value };
    }

    constexpr UInt32 operator <<(const UInt32 &other)
    {
        return UInt32{ _value << other._value };
    }

    constexpr UInt32 operator >>(const UInt32 &other)
    {
        return UInt32{ _value >> other._value };
    }
    /// @}

    /** @name Increment/Decrement
     *  @{
     */
    constexpr UInt32 &operator ++() // Pre-increment
    {
        ++_value;
        return *this;
    }

    constexpr UInt32 &operator --() // Pre-decrement
    {
        --_value;
        return *this;
    }

    constexpr UInt32 operator ++(int) // Post-increment
    {
        return UInt32{ _value++ };
    }

    constexpr UInt32 operator --(int) // Post-decrement
    {
        return UInt32{ _value-- };
    }
    /// @}
protected:
    std::uint32_t _value = 0;
};

inline bool operator ==(const std::uint32_t left, const UInt32 &right)
{
    return left == std::uint32_t(right);
}

}
