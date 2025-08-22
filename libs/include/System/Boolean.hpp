#include "System/IConvertible.hpp"
#include "System/Numerics/INumber.hpp"
#include <string_view>
#include <compare>

namespace System
{

class Boolean : public IConvertible,
                public Numerics::INumber<Boolean>
{
public:
    constexpr Boolean() { }
    constexpr Boolean(bool value) : _value{ value } { }

    static constexpr Boolean True() { return Boolean(true); }
    static constexpr Boolean False() { return Boolean(false); }

    static std::string_view FalseString;
    static std::string_view TrueString;

    bool Value() const { return _value; }
    void Value(bool new_value) { new_value = new_value; }

    // IConvertible Interface
    TypeCode GetTypeCode() const override { return TypeCode::Boolean; }

    bool ToBoolean() const override { return _value; }

    std::byte ToByte() const override { return std::byte{_value}; }

    char ToChar() const override { return {_value}; }

    std::int16_t ToInt16() const override { return {_value}; }
    std::int32_t ToInt32() const override { return {_value}; }
    std::int64_t ToInt64() const override { return {_value}; }

    std::uint16_t ToUInt16() const override { return {_value}; }
    std::uint32_t ToUInt32() const override { return {_value}; }
    std::uint64_t ToUInt64() const override { return {_value}; }

    float  ToSingle() const override { return static_cast<float>(_value); }
    double ToDouble() const override { return static_cast<double>(_value); }

    std::string ToString() const override { return (_value) ? std::string{TrueString} : std::string{FalseString}; }

    // IComparable Interface
    int CompareTo(const Boolean &other) const;

    // IEquatable Interface
    constexpr bool Equals(const Boolean &other) const { return *this == other; }

    // INumberBase Interface
    static constexpr Boolean One() { return Numerics::INumberBase<bool>::One(); }
    static constexpr Boolean Zero() { return Numerics::INumberBase<bool>::Zero(); }
    static constexpr int   Radix = Numerics::INumberBase<bool>::Radix;

    static Boolean Abs(Boolean input)
    {
        return Numerics::INumberBase<bool>::Abs(input);
    }

    template <class TOther>
    static constexpr Boolean CreateChecked(TOther other)
    {
        return Numerics::INumberBase<bool>::CreateChecked(other);
    }

    template <class TOther>
    static constexpr Boolean CreateSaturating(TOther other)
    {
        return Numerics::INumberBase<bool>::CreateSaturating(other);
    }

    template <class TOther>
    static constexpr Boolean CreateTruncating(TOther other)
    {
        return Numerics::INumberBase<bool>::CreateTruncating(other);
    }

    static constexpr bool IsCanonical(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsCanonical(value);
    }

    static constexpr bool IsComplexNumber(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsComplexNumber(value);
    }

    static constexpr bool IsEvenInteger(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsEvenInteger(value);
    }

    static constexpr bool IsFinite(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsFinite(value);
    }

    static constexpr bool IsImaginaryNumber(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsImaginaryNumber(value);
    }

    static constexpr bool IsInfinity(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsInfinity(value);
    }

    static constexpr bool IsInteger(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsInteger(value);
    }

    static constexpr bool IsNaN(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsNaN(value);
    }

    static constexpr bool IsNegative(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsNegative(value);
    }

    static constexpr bool IsNegativeInfinity(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsNegativeInfinity(value);
    }

    static constexpr bool IsNormal(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsNormal(value);
    }

    static constexpr bool IsOddInteger(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsOddInteger(value);
    }

    static constexpr bool IsPositive(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsPositive(value);
    }

    static constexpr bool IsPositiveInfinity(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsPositiveInfinity(value);
    }

    static constexpr bool IsRealNumber(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsRealNumber(value);
    }

    static constexpr bool IsSubnormal(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsSubnormal(value);
    }

    static constexpr bool IsZero(Boolean value)
    {
        return Numerics::INumberBase<bool>::IsZero(value);
    }

    static constexpr Boolean MaxMagnitude(Boolean value1, Boolean value2)
    {
        return Numerics::INumberBase<bool>::MaxMagnitude(value1, value2);
    }

    static constexpr Boolean MaxMagnitudeNumber(Boolean value1, Boolean value2)
    {
        return Numerics::INumberBase<bool>::MaxMagnitudeNumber(value1, value2);
    }

    static constexpr Boolean MinMagnitude(Boolean value1, Boolean value2)
    {
        return Numerics::INumberBase<bool>::MinMagnitude(value1, value2);
    }

    static constexpr Boolean MinMagnitudeNumber(Boolean value1, Boolean value2)
    {
        return Numerics::INumberBase<bool>::MinMagnitudeNumber(value1, value2);
    }

    static constexpr Boolean MultiplyAddEstimate(Boolean value1, Boolean value2)
    {
        return Numerics::INumberBase<bool>::MultiplyAddEstimate(value1, value2);
    }

    static Boolean Parse(std::string_view value_string)
    {
        return Numerics::INumberBase<bool>::Parse(value_string);
    }

    static std::optional<Boolean> TryParse(std::string_view value_string)
    {
        return Numerics::INumberBase<bool>::TryParse(value_string);
    }

    // INumber Interface
    static constexpr Boolean Clamp(Boolean value, Boolean min, Boolean max)
    {
        return Numerics::INumber<bool>::Clamp(value, min, max);
    }

    static constexpr Boolean CopySign(Boolean value, Boolean sign)
    {
        return Numerics::INumber<bool>::CopySign(value, sign);
    }

    static constexpr Boolean Max(Boolean x, Boolean y)
    {
        return Numerics::INumber<bool>::Max(x, y);
    }

    static constexpr Boolean MaxNumber(Boolean x, Boolean y)
    {
        return Numerics::INumber<bool>::MaxNumber(x, y);
    }

    static constexpr Boolean Min(Boolean x, Boolean y)
    {
        return Numerics::INumber<bool>::Min(x, y);
    }

    static constexpr Boolean MinNumber(Boolean x, Boolean y)
    {
        return Numerics::INumber<bool>::MinNumber(x, y);
    }

    static constexpr int Sign(Boolean value)
    {
        return Numerics::INumber<bool>::Sign(value);
    }

    constexpr operator bool() const { return _value; }

    constexpr std::strong_ordering operator <=>(const Boolean other) const { return _value <=> other._value; }
    constexpr std::strong_ordering operator <=>(const bool other) const { return _value <=> other; }

    constexpr bool operator ==(const Boolean other) const { return _value == other._value; }
    constexpr bool operator ==(const bool other) const { return _value == other; }
protected:
    bool _value = false;
};

inline bool operator ==(const bool left, const Boolean right)
{
    return right == left;
}

}