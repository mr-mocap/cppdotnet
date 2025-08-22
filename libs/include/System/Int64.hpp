#include "System/IConvertible.hpp"
#include "System/Numerics/INumber.hpp"
#include <cstdint>
#include <limits>
#include <cmath>
#include <algorithm>
#include <compare>

namespace System
{

class Int64 : public IConvertible,
              public Numerics::INumber<Int64>
{
public:
    constexpr Int64() = default;
    constexpr Int64(const std::int64_t initial_value) : _value{ initial_value } { }

    static constexpr Int64 MaxValue() { return std::numeric_limits<std::int64_t>::max(); }
    static constexpr Int64 MinValue() { return std::numeric_limits<std::int64_t>::min(); }

    // IConvertible Interface
    TypeCode GetTypeCode() const override { return TypeCode::Int64; }

    bool ToBoolean() const override { return _value; }

    std::byte ToByte() const override { return static_cast<std::byte>(_value); }

    char ToChar() const override { return static_cast<char>(_value); }

    std::int16_t ToInt16() const override { return static_cast<std::int16_t>(_value); }
    std::int32_t ToInt32() const override { return static_cast<std::int32_t>(_value); }
    std::int64_t ToInt64() const override { return _value; }

    std::uint16_t ToUInt16() const override { return static_cast<std::uint16_t>(_value); }
    std::uint32_t ToUInt32() const override { return static_cast<std::uint32_t>(_value); }
    std::uint64_t ToUInt64() const override { return _value; }

    float  ToSingle() const override { return static_cast<float>(_value); }
    double ToDouble() const override { return static_cast<double>(_value); }

    std::string ToString() const override;

    // IComparable Interface
    int CompareTo(const Int64 &other) const;

    // IEquatable Interface
    constexpr bool Equals(const Int64 &other) const { return *this == other; }

    // INumberBase Interface
    static constexpr Int64 One() { return Numerics::INumberBase<std::int64_t>::One(); }
    static constexpr Int64 Zero() { return Numerics::INumberBase<std::int64_t>::Zero(); }
    static constexpr int   Radix = Numerics::INumberBase<std::int64_t>::Radix;

    static Int64 Abs(Int64 input)
    {
        return Numerics::INumberBase<std::int64_t>::Abs(input);
    }

    template <class TOther>
    static constexpr Int64 CreateChecked(TOther other)
    {
        return Numerics::INumberBase<std::int64_t>::CreateChecked(other);
    }

    template <class TOther>
    static constexpr Int64 CreateSaturating(TOther other)
    {
        return Numerics::INumberBase<std::int64_t>::CreateSaturating(other);
    }

    template <class TOther>
    static constexpr Int64 CreateTruncating(TOther other)
    {
        return Numerics::INumberBase<std::int64_t>::CreateTruncating(other);
    }

    static constexpr bool IsCanonical(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsCanonical(value);
    }

    static constexpr bool IsComplexNumber(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsComplexNumber(value);
    }

    static constexpr bool IsEvenInteger(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsEvenInteger(value);
    }

    static constexpr bool IsFinite(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsFinite(value);
    }

    static constexpr bool IsImaginaryNumber(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsImaginaryNumber(value);
    }

    static constexpr bool IsInfinity(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsInfinity(value);
    }

    static constexpr bool IsInteger(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsInteger(value);
    }

    static constexpr bool IsNaN(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsNaN(value);
    }

    static constexpr bool IsNegative(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsNegative(value);
    }

    static constexpr bool IsNegativeInfinity(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsNegativeInfinity(value);
    }

    static constexpr bool IsNormal(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsNormal(value);
    }

    static constexpr bool IsOddInteger(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsOddInteger(value);
    }

    static constexpr bool IsPositive(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsPositive(value);
    }

    static constexpr bool IsPositiveInfinity(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsPositiveInfinity(value);
    }

    static constexpr bool IsRealNumber(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsRealNumber(value);
    }

    static constexpr bool IsSubnormal(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsSubnormal(value);
    }

    static constexpr bool IsZero(Int64 value)
    {
        return Numerics::INumberBase<std::int64_t>::IsZero(value);
    }

    static constexpr Int64 MaxMagnitude(Int64 value1, Int64 value2)
    {
        return Numerics::INumberBase<std::int64_t>::MaxMagnitude(value1, value2);
    }

    static constexpr Int64 MaxMagnitudeNumber(Int64 value1, Int64 value2)
    {
        return Numerics::INumberBase<std::int64_t>::MaxMagnitudeNumber(value1, value2);
    }

    static constexpr Int64 MinMagnitude(Int64 value1, Int64 value2)
    {
        return Numerics::INumberBase<std::int64_t>::MinMagnitude(value1, value2);
    }

    static constexpr Int64 MinMagnitudeNumber(Int64 value1, Int64 value2)
    {
        return Numerics::INumberBase<std::int64_t>::MinMagnitudeNumber(value1, value2);
    }

    static constexpr Int64 MultiplyAddEstimate(Int64 value1, Int64 value2)
    {
        return Numerics::INumberBase<std::int64_t>::MultiplyAddEstimate(value1, value2);
    }

    static Int64 Parse(std::string_view value_string)
    {
        return Numerics::INumberBase<std::int64_t>::Parse(value_string);
    }

    static std::optional<Int64> TryParse(std::string_view value_string)
    {
        return Numerics::INumberBase<std::int64_t>::TryParse(value_string);
    }

    // INumber Interface
    static constexpr Int64 Clamp(Int64 value, Int64 min, Int64 max)
    {
        return Numerics::INumber<std::int64_t>::Clamp(value, min, max);
    }

    static Int64 CopySign(Int64 value, Int64 sign)
    {
        return Numerics::INumber<std::int64_t>::CopySign(value, sign);
    }

    static constexpr Int64 Max(Int64 x, Int64 y)
    {
        return Numerics::INumber<std::int64_t>::Max(x, y);
    }

    static constexpr Int64 MaxNumber(Int64 x, Int64 y)
    {
        return Numerics::INumber<std::int64_t>::MaxNumber(x, y);
    }

    static constexpr Int64 Min(Int64 x, Int64 y)
    {
        return Numerics::INumber<std::int64_t>::Min(x, y);
    }

    static constexpr Int64 MinNumber(std::int64_t x, std::int64_t y)
    {
        return Numerics::INumber<std::int64_t>::MinNumber(x, y);
    }

    static constexpr int Sign(Int64 value)
    {
        return Numerics::INumber<std::int64_t>::Sign(value);
    }

    constexpr operator std::int64_t() const { return _value; }

    // C++ specific stuff.
    // NOTE: We need the <=> AND == operators ONLY, if we want all the other relational
    //       operators to be generated automatically for us.
    constexpr std::strong_ordering operator <=>(const Int64 other) const { return _value <=> other._value; }
    constexpr std::strong_ordering operator <=>(const std::int64_t other) const { return _value <=> other; }

    constexpr bool operator ==(const Int64 other) const { return _value == other._value; }
    constexpr bool operator ==(const std::int64_t other) const { return _value == other; }

protected:
    std::int64_t _value = 0;
};

inline bool operator ==(const std::int64_t left, const Int64 right)
{
    return right == left;
}

}
