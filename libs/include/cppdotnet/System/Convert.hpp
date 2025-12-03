#pragma once

#include <cppdotnet/System/Exception.hpp>
#include <cppdotnet/System/Base.hpp>
#include <cppdotnet/System/Boolean.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <cppdotnet/System/Enum.hpp>
#include <cppdotnet/System/TypeCode.hpp>
#include <string>
#include <string_view>
#include <span>
#include <vector>
#include <array>
#include <cstdint>
#include <cstddef>
#include <cctype>
#include <cassert>
#include <charconv>
#include <type_traits>

namespace System
{

class Convert
{
public:
    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }

    static std::string_view ToString(bool value);
    static std::string      ToString(char value);
    static std::string      ToString(std::byte value);
    static std::string      ToString(float  value);
    static std::string      ToString(double value);

    static std::string      ToString(int8_t  value, Base toBase = Base::Decimal);
    static std::string      ToString(int16_t value, Base toBase = Base::Decimal);
    static std::string      ToString(int32_t value, Base toBase = Base::Decimal);
    static std::string      ToString(int64_t value, Base toBase = Base::Decimal);

    static std::string      ToString(uint8_t  value, Base toBase = Base::Decimal);
    static std::string      ToString(uint16_t value, Base toBase = Base::Decimal);
    static std::string      ToString(uint32_t value, Base toBase = Base::Decimal);
    static std::string      ToString(uint64_t value, Base toBase = Base::Decimal);

    template <class EnumType>
        requires std::is_enum_v<EnumType>
    static std::string_view ToString(EnumType value)
    {
        // NOTE: Can throw exceptions
        return Enum<EnumPolicy<EnumType>>::GetName(value);
    }

    static std::vector<std::byte> FromHexString(std::string_view input_string); // Returns sequence as LITTLE-ENDIAN
    static std::string            ToHexString(const std::vector<std::byte> &input_bytes, bool uppercase = true)
    {
        return ToHexString( std::span<const std::byte>{input_bytes}, uppercase );
    }
    static std::string            ToHexString(std::span<const std::byte> input_bytes, bool uppercase = true);

    static std::string            ToBase64String(std::string_view input_ascii_string)
    {
        return ToBase64String( std::as_bytes( std::span<const char>(input_ascii_string) ) );
    }
    static std::string            ToBase64String(std::span<const std::byte> input_bytes);

    static std::vector<std::byte> FromBase64String(const char *input_ascii_string)
    {
        return FromBase64String( std::string_view{input_ascii_string} );
    }
    static std::vector<std::byte> FromBase64String(std::span<const char> input_ascii_string);

    static std::string            ToBase85String(std::span<const std::byte> input_bytes);

    static std::vector<std::byte> FromBase85String(std::string_view input_string);
    static std::vector<std::byte> FromBase85String(std::span<const char> input_string);

    // From IConvertable  (move there)
    template <class EnumType>
        requires std::is_enum_v<EnumType>
    static EnumType ToEnum(std::string_view value)
    {
        // NOTE: Can throw exceptions
        return Enum<EnumPolicy<EnumType>>::Parse(value);
    }

    // C++ specific
    static std::string ToChars(auto ...format_args)
    {
        std::array<char, 32> buffer;

        std::to_chars_result result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), format_args...);

        if (result.ec == std::errc::value_too_large)
            ThrowWithTarget( ArgumentOutOfRangeException( "format_args" ) );

        assert( result.ec == std::errc() );

        size_t length = result.ptr - buffer.data();

        return { buffer.data(), length };
    }

    static std::byte           From2HexCharsToByte(std::string_view input_string);
    static std::array<char, 2> FromByteTo2HexChars(std::byte input_byte, bool uppercase = true);

    /** A structure for storing the digits of a number in a particular base
     * 
     *  @note 
     */
    struct BaseConversion32Bit_t
    {
        explicit constexpr BaseConversion32Bit_t(std::array<std::byte, 32> &a, unsigned int d, unsigned int b)
            :
            number_of_digits(d),
            base(b)
        {
            PRECONDITION( base >= 2 );
            PRECONDITION( base <= 256 );

            for (unsigned int i = 0; i < a.size(); ++i)
                output_digits[i] = a[i];
        }

        std::array<std::byte, 32> output_digits; // Base 2 has the most digits, so use that for a 32-bit number
        unsigned int number_of_digits = 0;
        unsigned int base             = 10;
    };

    /** Converts the input number to a sequence of digits in a particular base
     * 
     *  @param input_number The number to convert
     *  @param base The base you want the output in (defaults to base 10)
     */
    static BaseConversion32Bit_t ToBase(std::uint32_t input_number, unsigned int base = 10);
};

}
