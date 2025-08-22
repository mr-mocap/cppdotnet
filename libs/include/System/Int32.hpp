#include "System/Numerics/INumber.hpp"
#include "System/TypeCode.hpp"
#include <cstdint>
#include <cstddef>
#include <limits>
#include <cmath>
#include <algorithm>
#include <string>
#include <optional>
#include <compare>

namespace System
{

class Int32 : public Numerics::INumber<Int32>
{
public:
    constexpr Int32() = default;
    constexpr Int32(const std::int32_t initial_value) : _value{ initial_value } { }

    static constexpr Int32 MaxValue() { return std::numeric_limits<std::int32_t>::max(); }
    static constexpr Int32 MinValue() { return std::numeric_limits<std::int32_t>::min(); }

    // IConvertible Interface
    TypeCode GetTypeCode() const { return TypeCode::Int32; }

    bool ToBoolean() const { return _value; }

    std::byte ToByte() const { return static_cast<std::byte>(_value); }

    char ToChar() const { return static_cast<char>(_value); }

    std::int16_t ToInt16() const { return static_cast<std::int16_t>(_value); }
    std::int32_t ToInt32() const { return _value; }
    std::int64_t ToInt64() const { return _value; }

    std::uint16_t ToUInt16() const { return static_cast<std::uint16_t>(_value); }
    std::uint32_t ToUInt32() const { return static_cast<std::uint32_t>(_value); }
    std::uint64_t ToUInt64() const { return _value; }

    float  ToSingle() const { return static_cast<float>(_value); }
    double ToDouble() const { return static_cast<double>(_value); }

    std::string ToString() const;

    // IComparable Interface
    int CompareTo(const Int32 &other) const;

    // IEquatable Interface
    constexpr bool Equals(const Int32 &other) const { return *this == other; }

    // INumberBase Interface
    static constexpr Int32 One() { return Numerics::INumberBase<std::int32_t>::One(); }
    static constexpr Int32 Zero() { return Numerics::INumberBase<std::int32_t>::Zero(); }
    static constexpr int   Radix = Numerics::INumberBase<std::int32_t>::Radix;

    static Int32 Abs(Int32 input)
    {
        return Numerics::INumberBase<std::int32_t>::Abs(input);
    }

    template <class TOther>
    static constexpr Int32 CreateChecked(TOther other)
    {
        return Numerics::INumberBase<std::int32_t>::CreateChecked(other);
    }

    template <class TOther>
    static constexpr Int32 CreateSaturating(TOther other)
    {
        return Numerics::INumberBase<std::int32_t>::CreateSaturating(other);
    }

    template <class TOther>
    static constexpr Int32 CreateTruncating(TOther other)
    {
        return Numerics::INumberBase<std::int32_t>::CreateTruncating(other);
    }

    static constexpr bool IsCanonical(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsCanonical(value);
    }

    static constexpr bool IsComplexNumber(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsComplexNumber(value);
    }

    static constexpr bool IsEvenInteger(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsEvenInteger(value);
    }

    static constexpr bool IsFinite(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsFinite(value);
    }

    static constexpr bool IsImaginaryNumber(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsImaginaryNumber(value);
    }

    static constexpr bool IsInfinity(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsInfinity(value);
    }

    static constexpr bool IsInteger(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsInteger(value);
    }

    static constexpr bool IsNaN(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsNaN(value);
    }

    static constexpr bool IsNegative(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsNegative(value);
    }

    static constexpr bool IsNegativeInfinity(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsNegativeInfinity(value);
    }

    static constexpr bool IsNormal(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsNormal(value);
    }

    static constexpr bool IsOddInteger(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsOddInteger(value);
    }

    static constexpr bool IsPositive(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsPositive(value);
    }

    static constexpr bool IsPositiveInfinity(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsPositiveInfinity(value);
    }

    static constexpr bool IsRealNumber(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsRealNumber(value);
    }

    static constexpr bool IsSubnormal(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsSubnormal(value);
    }

    static constexpr bool IsZero(Int32 value)
    {
        return Numerics::INumberBase<std::int32_t>::IsZero(value);
    }

    static constexpr Int32 MaxMagnitude(Int32 value1, Int32 value2)
    {
        return Numerics::INumberBase<std::int32_t>::MaxMagnitude(value1, value2);
    }

    static constexpr Int32 MaxMagnitudeNumber(Int32 value1, Int32 value2)
    {
        return Numerics::INumberBase<std::int32_t>::MaxMagnitudeNumber(value1, value2);
    }

    static constexpr Int32 MinMagnitude(Int32 value1, Int32 value2)
    {
        return Numerics::INumberBase<std::int32_t>::MinMagnitude(value1, value2);
    }

    static constexpr Int32 MinMagnitudeNumber(Int32 value1, Int32 value2)
    {
        return Numerics::INumberBase<std::int32_t>::MinMagnitudeNumber(value1, value2);
    }

    static constexpr Int32 MultiplyAddEstimate(Int32 value1, Int32 value2)
    {
        return Numerics::INumberBase<std::int32_t>::MultiplyAddEstimate(value1, value2);
    }

    static Int32 Parse(std::string_view value_string)
    {
        return Numerics::INumberBase<std::int32_t>::Parse(value_string);
    }

    static std::optional<Int32> TryParse(std::string_view value_string)
    {
        return Numerics::INumberBase<std::int32_t>::TryParse(value_string);
    }

    // INumber Interface
    static constexpr Int32 Clamp(Int32 value, Int32 min, Int32 max)
    {
        return Numerics::INumber<std::int32_t>::Clamp(value, min, max);
    }

    static Int32 CopySign(Int32 value, Int32 sign)
    {
        return Numerics::INumber<std::int32_t>::CopySign(value, sign);
    }

    static constexpr Int32 Max(Int32 x, Int32 y)
    {
        return Numerics::INumber<std::int32_t>::Max(x, y);
    }

    static constexpr Int32 MaxNumber(Int32 x, Int32 y)
    {
        return Numerics::INumber<std::int32_t>::MaxNumber(x, y);
    }

    static constexpr Int32 Min(Int32 x, Int32 y)
    {
        return Numerics::INumber<std::int32_t>::Min(x, y);
    }

    static constexpr Int32 MinNumber(std::int32_t x, std::int32_t y)
    {
        return Numerics::INumber<std::int32_t>::MinNumber(x, y);
    }

    static constexpr int Sign(Int32 value)
    {
        return Numerics::INumber<std::int32_t>::Sign(value);
    }

    constexpr operator std::int32_t() const { return _value; }

    // C++ specific stuff.
    // NOTE: We need the <=> AND == operators ONLY, if we want all the other relational
    //       operators to be generated automatically for us.
    constexpr std::strong_ordering operator <=>(const Int32 other) const { return _value <=> other._value; }
    constexpr std::strong_ordering operator <=>(const std::int32_t other) const { return _value <=> other; }

    constexpr bool operator ==(const Int32 &other) const { return _value == other._value; }
    constexpr bool operator ==(const std::int32_t other) const { return _value == other; }

    // Basic Operations
    constexpr Int32 &operator +=(const Int32 &other)
    {
        _value += other._value;
        return *this;
    }

    constexpr Int32 &operator -=(const Int32 &other)
    {
        _value -= other._value;
        return *this;
    }

    constexpr Int32 &operator *=(const Int32 &other)
    {
        _value *= other._value;
        return *this;
    }

    constexpr Int32 &operator /=(const Int32 &other)
    {
        _value /= other._value;
        return *this;
    }

    constexpr Int32 &operator %=(const Int32 &other)
    {
        _value %= other._value;
        return *this;
    }

    constexpr Int32 &operator &=(const Int32 &other)
    {
        _value &= other._value;
        return *this;
    }

    constexpr Int32 &operator |=(const Int32 &other)
    {
        _value |= other._value;
        return *this;
    }

    constexpr Int32 &operator ^=(const Int32 &other)
    {
        _value ^= other._value;
        return *this;
    }

    constexpr Int32 &operator <<=(const Int32 &other)
    {
        _value <<= other._value;
        return *this;
    }

    constexpr Int32 &operator >>=(const Int32 &other)
    {
        _value >>= other._value;
        return *this;
    }

    constexpr Int32 operator +(const Int32 &right) const
    {
        return Int32{ _value + right._value };
    }

    constexpr Int32 operator +(const std::int32_t right) const
    {
        return Int32{ _value + right };
    }

    constexpr Int32 operator -(const Int32 &right) const
    {
        return Int32{ _value - right._value };
    }

    constexpr Int32 operator -(const std::int32_t right) const
    {
        return Int32{ _value - right };
    }

    constexpr Int32 operator *(const Int32 &right) const
    {
        return Int32{ _value * right._value };
    }

    constexpr Int32 operator *(const std::int32_t right) const
    {
        return Int32{ _value * right };
    }

    constexpr Int32 operator /(const Int32 &right) const
    {
        return Int32{ _value / right._value };
    }

    constexpr Int32 operator /(const std::int32_t right) const
    {
        return Int32{ _value / right };
    }

    constexpr Int32 operator %(const Int32 &right) const
    {
        return Int32{ _value % right };
    }

    constexpr Int32 operator %(const std::int32_t right) const
    {
        return Int32{ _value % right };
    }

    constexpr Int32 operator +() const
    {
        return *this;
    }

    constexpr Int32 operator -() const
    {
        return Int32{ -_value };
    }

    constexpr Int32 operator ~() const
    {
        return Int32{ ~_value };
    }

    constexpr Int32 operator &(const Int32 &other)
    {
        return Int32{ _value & other._value };
    }

    constexpr Int32 operator |(const Int32 &other)
    {
        return Int32{ _value | other._value };
    }

    constexpr Int32 operator ^(const Int32 &other)
    {
        return Int32{ _value ^ other._value };
    }

    constexpr Int32 operator <<(const Int32 &other)
    {
        return Int32{ _value << other._value };
    }

    constexpr Int32 operator >>(const Int32 &other)
    {
        return Int32{ _value >> other._value };
    }

    // Increment/Decrement
    constexpr Int32 &operator ++() // Pre-increment
    {
        ++_value;
        return *this;
    }

    constexpr Int32 &operator --() // Pre-decrement
    {
        --_value;
        return *this;
    }

    constexpr Int32 operator ++(int) // Post-increment
    {
        return Int32{ _value++ };
    }

    constexpr Int32 operator --(int) // Post-decrement
    {
        return Int32{ _value-- };
    }
protected:
    std::int32_t _value = 0;
};

inline bool operator ==(const std::int32_t left, const Int32 &right)
{
    return left == std::int32_t(right);
}

}