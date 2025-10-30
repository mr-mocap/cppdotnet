#pragma once

#include <concepts>
#include <cppdotnet/System/Numerics/INumber.hpp>

namespace System
{

template <std::integral UnderlyingType, typename DerivedType>
struct IntCommon : public Numerics::INumber<UnderlyingType>
{
    /** @name INumberBase Interface
     *  @{
     */
    //static constexpr Int32 One() { return Numerics::INumberBase<std::int32_t>::One(); }
    //static constexpr Int32 Zero() { return Numerics::INumberBase<std::int32_t>::Zero(); }
    //static constexpr int   Radix = Numerics::INumberBase<std::int32_t>::Radix;

    static DerivedType Abs(DerivedType input)
    {
        return Numerics::INumberBase<UnderlyingType>::Abs(input);
    }

    template <class TOther>
    static constexpr DerivedType CreateChecked(TOther other)
    {
        return Numerics::INumberBase<UnderlyingType>::CreateChecked(other);
    }

    template <class TOther>
    static constexpr DerivedType CreateSaturating(TOther other)
    {
        return Numerics::INumberBase<UnderlyingType>::CreateSaturating(other);
    }

    template <class TOther>
    static constexpr DerivedType CreateTruncating(TOther other)
    {
        return Numerics::INumberBase<UnderlyingType>::CreateTruncating(other);
    }

    static constexpr bool IsCanonical(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsCanonical(value);
    }

    static constexpr bool IsComplexNumber(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsComplexNumber(value);
    }

    static constexpr bool IsEvenInteger(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsEvenInteger(value);
    }

    static constexpr bool IsFinite(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsFinite(value);
    }

    static constexpr bool IsImaginaryNumber(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsImaginaryNumber(value);
    }

    static constexpr bool IsInfinity(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsInfinity(value);
    }

    static constexpr bool IsInteger(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsInteger(value);
    }

    static constexpr bool IsNaN(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsNaN(value);
    }

    static constexpr bool IsNegative(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsNegative(value);
    }

    static constexpr bool IsNegativeInfinity(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsNegativeInfinity(value);
    }

    static constexpr bool IsNormal(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsNormal(value);
    }

    static constexpr bool IsOddInteger(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsOddInteger(value);
    }

    static constexpr bool IsPositive(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsPositive(value);
    }

    static constexpr bool IsPositiveInfinity(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsPositiveInfinity(value);
    }

    static constexpr bool IsRealNumber(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsRealNumber(value);
    }

    static constexpr bool IsSubnormal(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsSubnormal(value);
    }

    static constexpr bool IsZero(DerivedType value)
    {
        return Numerics::INumberBase<UnderlyingType>::IsZero(value);
    }

    static constexpr DerivedType MaxMagnitude(DerivedType value1, DerivedType value2)
    {
        return Numerics::INumberBase<UnderlyingType>::MaxMagnitude(value1, value2);
    }

    static constexpr DerivedType MaxMagnitudeNumber(DerivedType value1, DerivedType value2)
    {
        return Numerics::INumberBase<UnderlyingType>::MaxMagnitudeNumber(value1, value2);
    }

    static constexpr DerivedType MinMagnitude(DerivedType value1, DerivedType value2)
    {
        return Numerics::INumberBase<UnderlyingType>::MinMagnitude(value1, value2);
    }

    static constexpr DerivedType MinMagnitudeNumber(DerivedType value1, DerivedType value2)
    {
        return Numerics::INumberBase<UnderlyingType>::MinMagnitudeNumber(value1, value2);
    }

    static constexpr DerivedType MultiplyAddEstimate(DerivedType value1, DerivedType value2)
    {
        return Numerics::INumberBase<UnderlyingType>::MultiplyAddEstimate(value1, value2);
    }

    static DerivedType Parse(std::string_view value_string)
    {
        return Numerics::INumberBase<UnderlyingType>::Parse(value_string);
    }

    static std::optional<DerivedType> TryParse(std::string_view value_string)
    {
        return Numerics::INumberBase<UnderlyingType>::TryParse(value_string);
    }
    /// @}

    /** @name INumber Interface
     *  @{
     */
    static constexpr DerivedType Clamp(DerivedType value, DerivedType min, DerivedType max)
    {
        return Numerics::INumber<UnderlyingType>::Clamp(value, min, max);
    }

    static DerivedType CopySign(DerivedType value, DerivedType sign)
    {
        return Numerics::INumber<UnderlyingType>::CopySign(value, sign);
    }

    static constexpr DerivedType Max(DerivedType x, DerivedType y)
    {
        return Numerics::INumber<UnderlyingType>::Max(x, y);
    }

    static constexpr DerivedType MaxNumber(DerivedType x, DerivedType y)
    {
        return Numerics::INumber<UnderlyingType>::MaxNumber(x, y);
    }

    static constexpr DerivedType Min(DerivedType x, DerivedType y)
    {
        return Numerics::INumber<UnderlyingType>::Min(x, y);
    }

    static constexpr DerivedType MinNumber(DerivedType x, DerivedType y)
    {
        return Numerics::INumber<UnderlyingType>::MinNumber(x, y);
    }

    static constexpr int Sign(DerivedType value)
    {
        return Numerics::INumber<UnderlyingType>::Sign(value);
    }
    /// @}
};

}