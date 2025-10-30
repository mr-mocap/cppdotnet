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

class Int16 : public IntCommon<std::int16_t, Int16>
{
public:
    constexpr Int16() = default;
    constexpr Int16(const std::int16_t initial_value) : _value{ initial_value } { }

    static constexpr Int16 MaxValue() { return std::numeric_limits<std::int16_t>::max(); }
    static constexpr Int16 MinValue() { return std::numeric_limits<std::int16_t>::min(); }

    /** @name IConvertible Interface
     *  @{
     */
    TypeCode GetTypeCode() const { return TypeCode::Int16; }

    bool ToBoolean() const { return _value; }

    std::byte ToByte() const { return static_cast<std::byte>(_value); }

    char ToChar() const { return static_cast<char>(_value); }

    std::int16_t ToInt16() const { return _value; }
    std::int32_t ToInt32() const { return _value; }
    std::int64_t ToInt64() const { return _value; }

    std::uint16_t ToUInt16() const { return static_cast<std::uint16_t>(_value); }
    std::uint32_t ToUInt32() const { return static_cast<std::uint32_t>(_value); }
    std::uint64_t ToUInt64() const { return _value; }

    float  ToSingle() const { return static_cast<float>(_value); }
    double ToDouble() const { return static_cast<double>(_value); }

    std::string ToString() const;
    /// @}

    /** @name IComparable Interface
     *  @{
     */
    int CompareTo(const Int16 &other) const;
    /// @}

    /** @name IEquatable  Interface
     *  @{
     */
    constexpr bool Equals(const Int16 &other) const { return *this == other; }
    /// @}

    constexpr operator std::int16_t() const { return _value; }

    // C++ specific stuff.
    // NOTE: We need the <=> AND == operators ONLY, if we want all the other relational
    //       operators to be generated automatically for us.
    constexpr std::strong_ordering operator <=>(Int16 other) const { return _value <=> other._value; }
    constexpr std::strong_ordering operator <=>(std::int16_t other) const { return _value <=> other; }

    constexpr bool operator ==(Int16 other) const { return _value == other._value; }
    constexpr bool operator ==(std::int16_t other) const { return _value == other; }

protected:
    std::int16_t _value = 0;
};

inline bool operator ==(std::int16_t left, Int16 right)
{
    return right == left;
}

}
