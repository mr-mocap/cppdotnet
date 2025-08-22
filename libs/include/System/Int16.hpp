#include "System/Numerics/INumber.hpp"
#include "System/TypeCode.hpp"
#include <cstdint>
#include <cstddef>
#include <limits>
#include <string>
#include <cmath>
#include <algorithm>
#include <optional>
#include <utility>
#include <compare>

namespace System
{

class Int16 : public Numerics::INumber<Int16>
{
public:
    constexpr Int16() = default;
    constexpr Int16(const std::int16_t initial_value) : _value{ initial_value } { }

    static constexpr Int16 MaxValue() { return std::numeric_limits<std::int16_t>::max(); }
    static constexpr Int16 MinValue() { return std::numeric_limits<std::int16_t>::min(); }

    // IConvertible Interface
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

    // IComparable Interface
    int CompareTo(const Int16 &other) const;

    // IEquatable Interface
    constexpr bool Equals(const Int16 &other) const { return *this == other; }

    // INumberBase Interface
    static constexpr Int16 One() { return Numerics::INumberBase<std::int16_t>::One(); }
    static constexpr Int16 Zero() { return Numerics::INumberBase<std::int16_t>::Zero(); }
    static constexpr int   Radix = Numerics::INumberBase<std::int16_t>::Radix;

    static Int16 Abs(Int16 input)
    {
        return Numerics::INumberBase<std::int16_t>::Abs(input);
    }

    template <class TOther>
    static constexpr Int16 CreateChecked(TOther other)
    {
        return Numerics::INumberBase<std::int16_t>::CreateChecked(other);
    }

    template <class TOther>
    static constexpr Int16 CreateSaturating(TOther other)
    {
        return Numerics::INumberBase<std::int16_t>::CreateSaturating(other);
    }

    template <class TOther>
    static constexpr Int16 CreateTruncating(TOther other)
    {
        return Numerics::INumberBase<std::int16_t>::CreateTruncating(other);
    }

    static constexpr bool IsCanonical(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsCanonical(value);
    }

    static constexpr bool IsComplexNumber(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsComplexNumber(value);
    }

    static constexpr bool IsEvenInteger(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsEvenInteger(value);
    }

    static constexpr bool IsFinite(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsFinite(value);
    }

    static constexpr bool IsImaginaryNumber(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsImaginaryNumber(value);
    }

    static constexpr bool IsInfinity(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsInfinity(value);
    }

    static constexpr bool IsInteger(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsInteger(value);
    }

    static constexpr bool IsNaN(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsNaN(value);
    }

    static constexpr bool IsNegative(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsNegative(value);
    }

    static constexpr bool IsNegativeInfinity(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsNegativeInfinity(value);
    }

    static constexpr bool IsNormal(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsNormal(value);
    }

    static constexpr bool IsOddInteger(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsOddInteger(value);
    }

    static constexpr bool IsPositive(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsPositive(value);
    }

    static constexpr bool IsPositiveInfinity(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsPositiveInfinity(value);
    }

    static constexpr bool IsRealNumber(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsRealNumber(value);
    }

    static constexpr bool IsSubnormal(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsSubnormal(value);
    }

    static constexpr bool IsZero(Int16 value)
    {
        return Numerics::INumberBase<std::int16_t>::IsZero(value);
    }

    static constexpr Int16 MaxMagnitude(Int16 value1, Int16 value2)
    {
        return Numerics::INumberBase<std::int16_t>::MaxMagnitude(value1, value2);
    }

    static constexpr Int16 MaxMagnitudeNumber(Int16 value1, Int16 value2)
    {
        return Numerics::INumberBase<std::int16_t>::MaxMagnitudeNumber(value1, value2);
    }

    static constexpr Int16 MinMagnitude(Int16 value1, Int16 value2)
    {
        return Numerics::INumberBase<std::int16_t>::MinMagnitude(value1, value2);
    }

    static constexpr Int16 MinMagnitudeNumber(Int16 value1, Int16 value2)
    {
        return Numerics::INumberBase<std::int16_t>::MinMagnitudeNumber(value1, value2);
    }

    static constexpr Int16 MultiplyAddEstimate(Int16 value1, Int16 value2)
    {
        return Numerics::INumberBase<std::int16_t>::MultiplyAddEstimate(value1, value2);
    }

    static Int16 Parse(std::string_view value_string)
    {
        return Numerics::INumberBase<std::int16_t>::Parse(value_string);
    }

    static std::optional<Int16> TryParse(std::string_view value_string)
    {
        return Numerics::INumberBase<std::int16_t>::TryParse(value_string);
    }

    // INumber Interface
    static constexpr Int16 Clamp(Int16 value, Int16 min, Int16 max)
    {
        return Numerics::INumber<std::int16_t>::Clamp(value, min, max);
    }

    static Int16 CopySign(Int16 value, Int16 sign)
    {
        return Numerics::INumber<std::int16_t>::CopySign(value, sign);
    }

    static constexpr Int16 Max(Int16 x, Int16 y)
    {
        return Numerics::INumber<std::int16_t>::Max(x, y);
    }

    static constexpr Int16 MaxNumber(Int16 x, Int16 y)
    {
        return Numerics::INumber<std::int16_t>::MaxNumber(x, y);
    }

    static constexpr Int16 Min(Int16 x, Int16 y)
    {
        return Numerics::INumber<std::int16_t>::Min(x, y);
    }

    static constexpr Int16 MinNumber(std::int16_t x, std::int16_t y)
    {
        return Numerics::INumber<std::int16_t>::MinNumber(x, y);
    }

    static constexpr int Sign(Int16 value)
    {
        return Numerics::INumber<std::int16_t>::Sign(value);
    }

    constexpr operator std::int16_t() const { return _value; }

    // C++ specific stuff.
    // NOTE: We need the <=> AND == operators ONLY, if we want all the other relational
    //       operators to be generated automatically for us.
    constexpr std::strong_ordering operator <=>(const Int16 other) const { return _value <=> other._value; }
    constexpr std::strong_ordering operator <=>(const std::int16_t other) const { return _value <=> other; }

    constexpr bool operator ==(const Int16 other) const { return _value == other._value; }
    constexpr bool operator ==(const std::int16_t other) const { return _value == other; }

protected:
    std::int16_t _value = 0;
};

inline bool operator ==(const std::int16_t left, const Int16 right)
{
    return right == left;
}

}
