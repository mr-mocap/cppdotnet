#pragma once

#include <cppdotnet/System/Private/IntCommon.hpp>
#include <cppdotnet/System/TypeCode.hpp>
#include <cstdint>
#include <limits>
#include <cmath>
#include <algorithm>
#include <compare>

namespace System
{

class UInt16 : public IntCommon<std::uint16_t, UInt16>
{
public:
    constexpr UInt16() = default;
    constexpr UInt16(const std::uint16_t initial_value) : _value{ initial_value } { }

    static constexpr UInt16 MaxValue() { return std::numeric_limits<std::uint16_t>::max(); }
    static constexpr UInt16 MinValue() { return std::numeric_limits<std::uint16_t>::min(); }

    /** @name IConvertible Interface
     *  @{
     */
    TypeCode GetTypeCode() const { return TypeCode::UInt16; }

    bool ToBoolean() const { return _value; }

    std::byte ToByte() const { return static_cast<std::byte>(_value); }

    char ToChar() const { return static_cast<char>(_value); }

    std::int16_t ToInt16() const { return static_cast<std::int16_t>(_value); }
    std::int32_t ToInt32() const { return static_cast<std::int32_t>(_value); }
    std::int64_t ToInt64() const { return static_cast<std::int64_t>(_value); }

    std::uint16_t ToUInt16() const { return _value; }
    std::uint32_t ToUInt32() const { return _value; }
    std::uint64_t ToUInt64() const { return _value; }

    float  ToSingle() const { return static_cast<float>(_value); }
    double ToDouble() const { return static_cast<double>(_value); }

    std::string ToString() const;
    /// @}

    /** @name IComparable Interface
     *  @{
     */
    int CompareTo(const UInt16 &other) const;
    /// @}

    /** @name IEquatable  Interface
     *  @{
     */
    constexpr bool Equals(const UInt16 &other) const { return *this == other; }
    /// @}

    constexpr operator std::uint16_t() const { return _value; }

    // C++ specific stuff.
    // NOTE: We need the <=> AND == operators ONLY, if we want all the other relational
    //       operators to be generated automatically for us.
    constexpr std::strong_ordering operator <=>(const UInt16 other) const { return _value <=> other._value; }
    constexpr std::strong_ordering operator <=>(const std::uint16_t other) const { return _value <=> other; }

    constexpr bool operator ==(const UInt16 other) const { return _value == other._value; }
    constexpr bool operator ==(const std::uint16_t other) const { return _value == other; }

    /** @name Increment/Decrement
     *  @{
     */
    constexpr UInt16 &operator ++() // Pre-increment
    {
        ++_value;
        return *this;
    }

    constexpr UInt16 &operator --() // Pre-decrement
    {
        --_value;
        return *this;
    }

    constexpr UInt16 operator ++(int) // Post-increment
    {
        return UInt16{ _value++ };
    }

    constexpr UInt16 operator --(int) // Post-decrement
    {
        return UInt16{ _value-- };
    }
    /// @}
protected:
    std::uint16_t _value = 0;
};

inline bool operator ==(const std::uint16_t left, const UInt16 right)
{
    return right == left;
}

}
