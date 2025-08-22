#include "System/IEquatable.hpp"
#include "System/Exception.hpp"
#include "System/Private/private.hpp"
#include <cmath>
#include <limits>
#include <string>
#include <stdexcept>
#include <charconv>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <format>

namespace System::Numerics
{

template <class T>
struct INumberBase : public IEquatable<T>
{
    static constexpr T   One();
    static constexpr T   Zero();
    static constexpr int Radix = 0;

    static T Abs(T value);

    template <class TOther>
    static constexpr T CreateChecked(TOther other);

    template <class TOther>
    static constexpr T CreateSaturating(TOther other);

    template <class TOther>
    static constexpr T CreateTruncating(TOther other);

    static constexpr bool IsCanonical(T value);

    static constexpr bool IsComplexNumber(T value);

    static constexpr bool IsEvenInteger(T value);

    static constexpr bool IsFinite(T value);

    static constexpr bool IsImaginaryNumber(T value);

    static constexpr bool IsInfinity(T value);

    static constexpr bool IsInteger(T value);

    static constexpr bool IsNaN(T value);

    static constexpr bool IsNegative(T value);

    static constexpr bool IsNegativeInfinity(T value);

    static constexpr bool IsNormal(T value);

    static constexpr bool IsOddInteger(T value);

    static constexpr bool IsPositive(T value);

    static constexpr bool IsPositiveInfinity(T value);

    static constexpr bool IsRealNumber(T value);

    static constexpr bool IsSubnormal(T value);

    static constexpr bool IsZero(T value);

    static constexpr T MaxMagnitude(T value1, T value2);

    static constexpr T MaxMagnitudeNumber(T value1, T value2);

    static constexpr T MinMagnitude(T value1, T value2);

    static constexpr T MinMagnitudeNumber(T value1, T value2);

    static constexpr T MultiplyAddEstimate(T value1, T value2);

    static           T Parse(std::string_view s);

    static std::optional<T> TryParse(std::string_view s);
};

namespace Private
{

template <class T>
struct CommonItems
{
    static std::string_view TypeName()
    {
        if constexpr (std::is_same_v<T, bool>)
            return std::string_view{"bool"};
        else if constexpr (std::is_same_v<T, std::int8_t>)
            return std::string_view{"int8_t"};
        else if constexpr (std::is_same_v<T, std::int16_t>)
            return std::string_view{"int16_t"};
        else if constexpr (std::is_same_v<T, std::int32_t>)
            return std::string_view{"int32_t"};
        else if constexpr (std::is_same_v<T, std::int64_t>)
            return std::string_view{"int64_t"};
        else if constexpr (std::is_same_v<T, std::uint8_t>)
            return std::string_view{"uint8_t"};
        else if constexpr (std::is_same_v<T, std::uint16_t>)
            return std::string_view{"uint16_t"};
        else if constexpr (std::is_same_v<T, std::uint32_t>)
            return std::string_view{"uint32_t"};
        else if constexpr (std::is_same_v<T, std::uint64_t>)
            return std::string_view{"uint64_t"};
    }

    static T Parse(std::string_view s)
    {
        using namespace std::literals;

        if ( s.empty() )
            ThrowWithTarget( ArgumentNullException("s"sv) );

        if constexpr (std::is_integral_v<T>)
        {
            if constexpr (std::is_same_v<T, bool>)
            {
                std::uint8_t converted;

                auto [ptr, ec] = std::from_chars( s.data(), s.data() + s.size(), converted, 2);
                
                if ( ec == std::errc::invalid_argument )
                    ThrowWithTarget( System::FormatException{ "Parameter 's' is not in the correct format"sv } );
                else if ( ec == std::errc::result_out_of_range )
                    ThrowWithTarget( System::OverflowException{ "Parameter 's' is not representable by bool"sv } );
                else if ( ec != std::errc() )
                    ThrowWithTarget( System::ArgumentException{ "Argument does not contain bool information", "s" } );

                return converted;

            }
            else
            {
                T converted;

                auto [ptr, ec] = std::from_chars( s.data(), s.data() + s.size(), converted);
                
                if ( ec == std::errc::invalid_argument )
                    ThrowWithTarget( System::FormatException{ "Parameter 's' is not in the correct format"sv } );
                else if ( ec == std::errc::result_out_of_range )
                    ThrowWithTarget( System::OverflowException{ std::format("Parameter 's' is not representable by {}"sv, TypeName()) } );
                else if ( ec != std::errc() )
                    ThrowWithTarget( System::ArgumentException{ "Argument does not contain integer information", "s" } );

                return converted;
            }
        }
    }

    static std::optional<T> TryParse(std::string_view s)
    {
        if ( s.empty() )
            return {};

        if constexpr (std::is_integral_v<T>)
        {
            if constexpr (std::is_same_v<T, bool>)
            {
                std::uint8_t converted;

                auto [ptr, ec] = std::from_chars( s.data(), s.data() + s.size(), converted, 2);
                
                if ( ec != std::errc() )
                    return {};

                return converted;
            }
            else
            {
                T converted;

                auto [ptr, ec] = std::from_chars( s.data(), s.data() + s.size(), converted);
                
                if ( ec != std::errc() )
                    return {};

                return converted;
            }
        }
        else
        {
            return {};
        }
    }
};

}

template <>
struct INumberBase<bool> : public IEquatable<bool>
{
    static constexpr bool   One() { return true; }
    static constexpr bool   Zero() { return false; }
    static constexpr int Radix = std::numeric_limits<bool>::radix;

    static           bool Abs(bool value) { return value; }

    template <class TOther>
    static constexpr bool CreateChecked(TOther ) { return bool{}; }

    template <class TOther>
    static constexpr bool CreateSaturating(TOther ) { return bool{}; }

    template <class TOther>
    static constexpr bool CreateTruncating(TOther ) { return bool{}; }

    static constexpr bool IsCanonical(bool ) { return true; }

    static constexpr bool IsComplexNumber(bool ) { return false; }

    static constexpr bool IsEvenInteger(bool value) { return value == false; }

    static constexpr bool IsFinite(bool ) { return true; }

    static constexpr bool IsImaginaryNumber(bool ) { return false; }

    static constexpr bool IsInfinity(bool ) { return false; }

    static constexpr bool IsInteger(bool ) { return false; }

    static constexpr bool IsNaN(bool ) { return false; }

    static constexpr bool IsNegative(bool ) { return false; }

    static constexpr bool IsNegativeInfinity(bool ) { return false; }

    static constexpr bool IsNormal(bool ) { return false; }

    static constexpr bool IsOddInteger(bool value) { return value == true; }

    static constexpr bool IsPositive(bool value) { return value == true; }

    static constexpr bool IsPositiveInfinity(bool ) { return false; }

    static constexpr bool IsRealNumber(bool ) { return false; }

    static constexpr bool IsSubnormal(bool ) { return false; }

    static constexpr bool IsZero(bool value) { return value == Zero(); }

    static constexpr bool MaxMagnitude(bool value1, bool value2) { return std::max(value1, value2); }

    static constexpr bool MaxMagnitudeNumber(bool value1, bool value2) { return MaxMagnitude(value1, value2); }

    static constexpr bool MinMagnitude(bool value1, bool value2) { return std::min(value1, value2); }

    static constexpr bool MinMagnitudeNumber(bool value1, bool value2) { return MinMagnitude(value1, value2); }

    static constexpr bool MultiplyAddEstimate(bool value1, bool value2) { return MinMagnitude(value1, value2); }

    static           bool  Parse(std::string_view s)
    {
        return Private::CommonItems<bool>::Parse(s);
    }

    static std::optional<bool> TryParse(std::string_view s)
    {
        return Private::CommonItems<bool>::TryParse(s);
    }
};


template <>
struct INumberBase<std::int8_t> : public IEquatable<std::int8_t>
{
    static constexpr std::int8_t   One() { return 1; }
    static constexpr std::int8_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::int8_t>::radix;

    static std::int8_t Abs(std::int8_t value) { return std::abs(value); }

    template <class TOther>
    static constexpr std::int8_t CreateChecked(TOther ) { return std::int8_t{}; }

    template <class TOther>
    static constexpr std::int8_t CreateSaturating(TOther ) { return std::int8_t{}; }

    template <class TOther>
    static constexpr std::int8_t CreateTruncating(TOther ) { return std::int8_t{}; }

    static constexpr bool IsCanonical(std::int8_t ) { return true; }

    static constexpr bool IsComplexNumber(std::int8_t ) { return false; }

    static constexpr bool IsEvenInteger(std::int8_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::int8_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::int8_t ) { return false; }

    static constexpr bool IsInfinity(std::int8_t ) { return false; }

    static constexpr bool IsInteger(std::int8_t ) { return true; }

    static constexpr bool IsNaN(std::int8_t ) { return false; }

    static constexpr bool IsNegative(std::int8_t value) { return value < 0; }

    static constexpr bool IsNegativeInfinity(std::int8_t ) { return false; }

    static constexpr bool IsNormal(std::int8_t ) { return false; }

    static constexpr bool IsOddInteger(std::int8_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::int8_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::int8_t ) { return false; }

    static constexpr bool IsRealNumber(std::int8_t ) { return false; }

    static constexpr bool IsSubnormal(std::int8_t ) { return false; }

    static constexpr bool IsZero(std::int8_t value) { return value == 0; }

    static constexpr std::int8_t MaxMagnitude(std::int8_t value1, std::int8_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::int8_t MaxMagnitudeNumber(std::int8_t value1, std::int8_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::int8_t value1, std::int8_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::int8_t value1, std::int8_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::int8_t MultiplyAddEstimate(std::int8_t value1, std::int8_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::int8_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::int8_t>::Parse(s);
    }

    static std::optional<std::int8_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::int8_t>::TryParse(s);
    }
};

template <>
struct INumberBase<std::int16_t> : public IEquatable<std::int16_t>
{
    static constexpr std::int16_t   One() { return 1; }
    static constexpr std::int16_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::int16_t>::radix;

    static std::int16_t Abs(std::int16_t value) { return std::abs(value); }

    template <class TOther>
    static constexpr std::int16_t CreateChecked(TOther ) { return std::int16_t{}; }

    template <class TOther>
    static constexpr std::int16_t CreateSaturating(TOther ) { return std::int16_t{}; }

    template <class TOther>
    static constexpr std::int16_t CreateTruncating(TOther ) { return std::int16_t{}; }

    static constexpr bool IsCanonical(std::int16_t ) { return true; }

    static constexpr bool IsComplexNumber(std::int16_t ) { return false; }

    static constexpr bool IsEvenInteger(std::int16_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::int16_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::int16_t ) { return false; }

    static constexpr bool IsInfinity(std::int16_t ) { return false; }

    static constexpr bool IsInteger(std::int16_t ) { return true; }

    static constexpr bool IsNaN(std::int16_t ) { return false; }

    static constexpr bool IsNegative(std::int16_t value) { return value < 0; }

    static constexpr bool IsNegativeInfinity(std::int16_t ) { return false; }

    static constexpr bool IsNormal(std::int16_t ) { return false; }

    static constexpr bool IsOddInteger(std::int16_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::int16_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::int16_t ) { return false; }

    static constexpr bool IsRealNumber(std::int16_t ) { return false; }

    static constexpr bool IsSubnormal(std::int16_t ) { return false; }

    static constexpr bool IsZero(std::int16_t value) { return value == 0; }

    static constexpr std::int16_t MaxMagnitude(std::int16_t value1, std::int16_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::int16_t MaxMagnitudeNumber(std::int16_t value1, std::int16_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::int16_t value1, std::int16_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::int16_t value1, std::int16_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::int16_t MultiplyAddEstimate(std::int16_t value1, std::int16_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::int16_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::int16_t>::Parse(s);
    }

    static std::optional<std::int16_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::int16_t>::TryParse(s);
    }
};


template <>
struct INumberBase<std::int32_t> : public IEquatable<std::int32_t>
{
    static constexpr std::int32_t   One() { return 1; }
    static constexpr std::int32_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::int32_t>::radix;

    static std::int32_t Abs(std::int32_t value) { return std::abs(value); }

    template <class TOther>
    static constexpr std::int32_t CreateChecked(TOther ) { return std::int32_t{}; }

    template <class TOther>
    static constexpr std::int32_t CreateSaturating(TOther ) { return std::int32_t{}; }

    template <class TOther>
    static constexpr std::int32_t CreateTruncating(TOther ) { return std::int32_t{}; }

    static constexpr bool IsCanonical(std::int32_t ) { return true; }

    static constexpr bool IsComplexNumber(std::int32_t ) { return false; }

    static constexpr bool IsEvenInteger(std::int32_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::int32_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::int32_t ) { return false; }

    static constexpr bool IsInfinity(std::int32_t ) { return false; }

    static constexpr bool IsInteger(std::int32_t ) { return true; }

    static constexpr bool IsNaN(std::int32_t ) { return false; }

    static constexpr bool IsNegative(std::int32_t value) { return value < 0; }

    static constexpr bool IsNegativeInfinity(std::int32_t ) { return false; }

    static constexpr bool IsNormal(std::int32_t ) { return false; }

    static constexpr bool IsOddInteger(std::int32_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::int32_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::int32_t ) { return false; }

    static constexpr bool IsRealNumber(std::int32_t ) { return false; }

    static constexpr bool IsSubnormal(std::int32_t ) { return false; }

    static constexpr bool IsZero(std::int32_t value) { return value == 0; }

    static constexpr std::int32_t MaxMagnitude(std::int32_t value1, std::int32_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::int32_t MaxMagnitudeNumber(std::int32_t value1, std::int32_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::int32_t value1, std::int32_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::int32_t value1, std::int32_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::int32_t MultiplyAddEstimate(std::int32_t value1, std::int32_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::int32_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::int32_t>::Parse(s);
    }

    static std::optional<std::int32_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::int32_t>::TryParse(s);
    }
};


template <>
struct INumberBase<std::int64_t> : public IEquatable<std::int64_t>
{
    static constexpr std::int64_t   One() { return 1; }
    static constexpr std::int64_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::int64_t>::radix;

    static std::int64_t Abs(std::int64_t value) { return std::abs(value); }

    template <class TOther>
    static constexpr std::int64_t CreateChecked(TOther ) { return std::int64_t{}; }

    template <class TOther>
    static constexpr std::int64_t CreateSaturating(TOther ) { return std::int64_t{}; }

    template <class TOther>
    static constexpr std::int64_t CreateTruncating(TOther ) { return std::int64_t{}; }

    static constexpr bool IsCanonical(std::int64_t ) { return true; }

    static constexpr bool IsComplexNumber(std::int64_t ) { return false; }

    static constexpr bool IsEvenInteger(std::int64_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::int64_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::int64_t ) { return false; }

    static constexpr bool IsInfinity(std::int64_t ) { return false; }

    static constexpr bool IsInteger(std::int64_t ) { return true; }

    static constexpr bool IsNaN(std::int64_t ) { return false; }

    static constexpr bool IsNegative(std::int64_t value) { return value < 0; }

    static constexpr bool IsNegativeInfinity(std::int64_t ) { return false; }

    static constexpr bool IsNormal(std::int64_t ) { return false; }

    static constexpr bool IsOddInteger(std::int64_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::int64_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::int64_t ) { return false; }

    static constexpr bool IsRealNumber(std::int64_t ) { return false; }

    static constexpr bool IsSubnormal(std::int64_t ) { return false; }

    static constexpr bool IsZero(std::int64_t value) { return value == 0; }

    static constexpr std::int64_t MaxMagnitude(std::int64_t value1, std::int64_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::int64_t MaxMagnitudeNumber(std::int64_t value1, std::int64_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::int64_t value1, std::int64_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::int64_t value1, std::int64_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::int64_t MultiplyAddEstimate(std::int64_t value1, std::int64_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::int64_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::int64_t>::Parse(s);
    }

    static std::optional<std::int64_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::int64_t>::TryParse(s);
    }
};


template <>
struct INumberBase<std::uint8_t> : public IEquatable<std::uint8_t>
{
    static constexpr std::uint8_t   One() { return 1; }
    static constexpr std::uint8_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::uint8_t>::radix;

    static std::uint8_t Abs(std::uint8_t value) { return value; }

    template <class TOther>
    static constexpr std::uint8_t CreateChecked(TOther ) { return std::uint8_t{}; }

    template <class TOther>
    static constexpr std::uint8_t CreateSaturating(TOther ) { return std::uint8_t{}; }

    template <class TOther>
    static constexpr std::uint8_t CreateTruncating(TOther ) { return std::uint8_t{}; }

    static constexpr bool IsCanonical(std::uint8_t ) { return true; }

    static constexpr bool IsComplexNumber(std::uint8_t ) { return false; }

    static constexpr bool IsEvenInteger(std::uint8_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::uint8_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::uint8_t ) { return false; }

    static constexpr bool IsInfinity(std::uint8_t ) { return false; }

    static constexpr bool IsInteger(std::uint8_t ) { return true; }

    static constexpr bool IsNaN(std::uint8_t ) { return false; }

    static constexpr bool IsNegative(std::uint8_t ) { return false; }

    static constexpr bool IsNegativeInfinity(std::uint8_t ) { return false; }

    static constexpr bool IsNormal(std::uint8_t ) { return false; }

    static constexpr bool IsOddInteger(std::uint8_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::uint8_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::uint8_t ) { return false; }

    static constexpr bool IsRealNumber(std::uint8_t ) { return false; }

    static constexpr bool IsSubnormal(std::uint8_t ) { return false; }

    static constexpr bool IsZero(std::uint8_t value) { return value == 0; }

    static constexpr std::uint8_t MaxMagnitude(std::uint8_t value1, std::uint8_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::uint8_t MaxMagnitudeNumber(std::uint8_t value1, std::uint8_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::uint8_t value1, std::uint8_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::uint8_t value1, std::uint8_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::uint8_t MultiplyAddEstimate(std::uint8_t value1, std::uint8_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::uint8_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::uint8_t>::Parse(s);
    }

    static std::optional<std::uint8_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::uint8_t>::TryParse(s);
    }
};


template <>
struct INumberBase<std::uint16_t> : public IEquatable<std::uint16_t>
{
    static constexpr std::uint16_t   One() { return 1; }
    static constexpr std::uint16_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::uint16_t>::radix;

    static std::uint16_t Abs(std::uint16_t value) { return value; }

    template <class TOther>
    static constexpr std::uint16_t CreateChecked(TOther ) { return std::uint16_t{}; }

    template <class TOther>
    static constexpr std::uint16_t CreateSaturating(TOther ) { return std::uint16_t{}; }

    template <class TOther>
    static constexpr std::uint16_t CreateTruncating(TOther ) { return std::uint16_t{}; }

    static constexpr bool IsCanonical(std::uint16_t ) { return true; }

    static constexpr bool IsComplexNumber(std::uint16_t ) { return false; }

    static constexpr bool IsEvenInteger(std::uint16_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::uint16_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::uint16_t ) { return false; }

    static constexpr bool IsInfinity(std::uint16_t ) { return false; }

    static constexpr bool IsInteger(std::uint16_t ) { return true; }

    static constexpr bool IsNaN(std::uint16_t ) { return false; }

    static constexpr bool IsNegative(std::uint16_t ) { return false; }

    static constexpr bool IsNegativeInfinity(std::uint16_t ) { return false; }

    static constexpr bool IsNormal(std::uint16_t ) { return false; }

    static constexpr bool IsOddInteger(std::uint16_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::uint16_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::uint16_t ) { return false; }

    static constexpr bool IsRealNumber(std::uint16_t ) { return false; }

    static constexpr bool IsSubnormal(std::uint16_t ) { return false; }

    static constexpr bool IsZero(std::uint16_t value) { return value == 0; }

    static constexpr std::uint16_t MaxMagnitude(std::uint16_t value1, std::uint16_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::uint16_t MaxMagnitudeNumber(std::uint16_t value1, std::uint16_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::uint16_t value1, std::uint16_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::uint16_t value1, std::uint16_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::uint16_t MultiplyAddEstimate(std::uint16_t value1, std::uint16_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::uint16_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::uint16_t>::Parse(s);
    }

    static std::optional<std::uint16_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::uint16_t>::TryParse(s);
    }
};


template <>
struct INumberBase<std::uint32_t> : public IEquatable<std::uint32_t>
{
    static constexpr std::uint32_t   One() { return 1; }
    static constexpr std::uint32_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::uint32_t>::radix;

    static std::uint32_t Abs(std::uint32_t value) { return value; }

    template <class TOther>
    static constexpr std::uint32_t CreateChecked(TOther ) { return std::uint32_t{}; }

    template <class TOther>
    static constexpr std::uint32_t CreateSaturating(TOther ) { return std::uint32_t{}; }

    template <class TOther>
    static constexpr std::uint32_t CreateTruncating(TOther ) { return std::uint32_t{}; }

    static constexpr bool IsCanonical(std::uint32_t ) { return true; }

    static constexpr bool IsComplexNumber(std::uint32_t ) { return false; }

    static constexpr bool IsEvenInteger(std::uint32_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::uint32_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::uint32_t ) { return false; }

    static constexpr bool IsInfinity(std::uint32_t ) { return false; }

    static constexpr bool IsInteger(std::uint32_t ) { return true; }

    static constexpr bool IsNaN(std::uint32_t ) { return false; }

    static constexpr bool IsNegative(std::uint32_t ) { return false; }

    static constexpr bool IsNegativeInfinity(std::uint32_t ) { return false; }

    static constexpr bool IsNormal(std::uint32_t ) { return false; }

    static constexpr bool IsOddInteger(std::uint32_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::uint32_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::uint32_t ) { return false; }

    static constexpr bool IsRealNumber(std::uint32_t ) { return false; }

    static constexpr bool IsSubnormal(std::uint32_t ) { return false; }

    static constexpr bool IsZero(std::uint32_t value) { return value == 0; }

    static constexpr std::uint32_t MaxMagnitude(std::uint32_t value1, std::uint32_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::uint32_t MaxMagnitudeNumber(std::uint32_t value1, std::uint32_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::uint32_t value1, std::uint32_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::uint32_t value1, std::uint32_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::uint32_t MultiplyAddEstimate(std::uint32_t value1, std::uint32_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::uint32_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::uint32_t>::Parse(s);
    }

    static std::optional<std::uint32_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::uint32_t>::TryParse(s);
    }
};


template <>
struct INumberBase<std::uint64_t> : public IEquatable<std::uint64_t>
{
    static constexpr std::uint64_t   One() { return 1; }
    static constexpr std::uint64_t   Zero() { return 0; }
    static constexpr int Radix = std::numeric_limits<std::uint64_t>::radix;

    static std::uint64_t Abs(std::uint64_t value) { return value; }

    template <class TOther>
    static constexpr std::uint64_t CreateChecked(TOther ) { return std::uint64_t{}; }

    template <class TOther>
    static constexpr std::uint64_t CreateSaturating(TOther ) { return std::uint64_t{}; }

    template <class TOther>
    static constexpr std::uint64_t CreateTruncating(TOther ) { return std::uint64_t{}; }

    static constexpr bool IsCanonical(std::uint64_t ) { return true; }

    static constexpr bool IsComplexNumber(std::uint64_t ) { return false; }

    static constexpr bool IsEvenInteger(std::uint64_t value) { return (value % 2) == 0; }

    static constexpr bool IsFinite(std::uint64_t ) { return true; }

    static constexpr bool IsImaginaryNumber(std::uint64_t ) { return false; }

    static constexpr bool IsInfinity(std::uint64_t ) { return false; }

    static constexpr bool IsInteger(std::uint64_t ) { return true; }

    static constexpr bool IsNaN(std::uint64_t ) { return false; }

    static constexpr bool IsNegative(std::uint64_t ) { return false; }

    static constexpr bool IsNegativeInfinity(std::uint64_t ) { return false; }

    static constexpr bool IsNormal(std::uint64_t ) { return false; }

    static constexpr bool IsOddInteger(std::uint64_t value) { return (value % 2) != 0; }

    static constexpr bool IsPositive(std::uint64_t value) { return value > 0; }

    static constexpr bool IsPositiveInfinity(std::uint64_t ) { return false; }

    static constexpr bool IsRealNumber(std::uint64_t ) { return false; }

    static constexpr bool IsSubnormal(std::uint64_t ) { return false; }

    static constexpr bool IsZero(std::uint64_t value) { return value == 0; }

    static constexpr std::uint64_t MaxMagnitude(std::uint64_t value1, std::uint64_t value2)
    {
        return std::max(value1, value2);
    }

    static constexpr std::uint64_t MaxMagnitudeNumber(std::uint64_t value1, std::uint64_t value2)
    {
        return MaxMagnitude(value1, value2);
    }

    static constexpr bool MinMagnitude(std::uint64_t value1, std::uint64_t value2)
    {
        return std::min(value1, value2);
    }

    static constexpr bool MinMagnitudeNumber(std::uint64_t value1, std::uint64_t value2)
    {
        return MinMagnitude(value1, value2);
    }

    static constexpr std::uint64_t MultiplyAddEstimate(std::uint64_t value1, std::uint64_t value2)
    {
        return MinMagnitude(value1, value2); // TODO: FIX
    }

    static std::uint64_t Parse(std::string_view s)
    {
        return Private::CommonItems<std::uint64_t>::Parse(s);
    }

    static std::optional<std::uint64_t> TryParse(std::string_view s)
    {
        return Private::CommonItems<std::uint64_t>::TryParse(s);
    }
};

}