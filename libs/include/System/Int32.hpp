#pragma once

#include "System/IComparable.hpp"
#include "System/IConvertible.hpp"
#include "System/IEquatable.hpp"
#include <cstdint>
#include <limits>
#include <cmath>
#include <algorithm>

namespace System
{

class Int32 : public IComparable<Int32>,
              public IConvertible,
              public IEquatable<Int32>
{
public:
    constexpr Int32() = default;
    constexpr Int32(const std::int32_t initial_value) : _value{ initial_value } { }

    static constexpr Int32 MaxValue() { return std::numeric_limits<std::int32_t>::max(); }
    static constexpr Int32 MinValue() { return std::numeric_limits<std::int32_t>::min(); }

    static constexpr Int32 Abs(const Int32 input) { return std::abs( input._value ); }
    static constexpr Int32 Clamp(const Int32 value, const Int32 min, const Int32 max) { return std::clamp( value, min, max ); }

    // IConvertible Interface
    TypeCode GetTypeCode() const override { return TypeCode::Int32; }

    bool ToBoolean() const override { return _value; }

    std::byte ToByte() const override { return static_cast<std::byte>(_value); }

    char ToChar() const override { return static_cast<char>(_value); }

    std::int16_t ToInt16() const override { return static_cast<std::int16_t>(_value); }
    std::int32_t ToInt32() const override { return _value; }
    std::int64_t ToInt64() const override { return _value; }

    std::uint16_t ToUInt16() const override { return static_cast<std::uint16_t>(_value); }
    std::uint32_t ToUInt32() const override { return static_cast<std::uint32_t>(_value); }
    std::uint64_t ToUInt64() const override { return _value; }

    float  ToSingle() const override { return static_cast<float>(_value); }
    double ToDouble() const override { return static_cast<double>(_value); }

    std::string ToString() const override;

    // IComparable Interface
    int CompareTo(const Int32 &other) const override;

    // IEquatable Interface
    bool Equals(const Int32 &other) const override;

    operator std::int32_t() const { return _value; }

    std::strong_ordering operator <=>(const Int32 other) const { return _value <=> other._value; }
    std::strong_ordering operator <=>(const std::int32_t other) const { return _value <=> other; }

    bool operator ==(const Int32 other) const { return _value == other._value; }
    bool operator ==(const std::int32_t other) const { return _value == other; }
protected:
    std::int32_t _value = 0;
};

}