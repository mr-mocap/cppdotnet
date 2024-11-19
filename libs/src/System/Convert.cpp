#include "System/Convert.hpp"
#include "System/Boolean.hpp"
#include "System/Exception.hpp"
#include <map>
#include <span>
#include <charconv>
#include <cassert>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <ranges>

namespace System
{

// From RFC 4648
static const std::string_view Base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char             Base64PadChar = '=';

std::byte Convert::From2HexCharsToByte(const std::string_view input_string)
{
    assert(input_string.size() == 2);

    uint8_t result;
    auto [ptr, ec] = std::from_chars(input_string.data(), input_string.data() + input_string.size(), result, 16);

    assert(ec != std::errc::invalid_argument);
    assert(ec != std::errc::result_out_of_range);
    assert(ec == std::errc()); // Good!

    return static_cast<std::byte>(result);
}

std::array<char, 2> Convert::FromByteTo2HexChars(std::byte input_byte, bool uppercase)
{
    const uint8_t input_as_uint = static_cast<uint8_t>(input_byte);

    std::array<char, 2> retval;

    auto [ptr, ec] = std::to_chars(retval.begin(), retval.end(), input_as_uint, 16);

    assert(ec == std::errc()); // Good!

    if ( input_as_uint < 16 )
    {
        return { '0', (uppercase) ? static_cast<char>( std::toupper(retval.front()) ) : retval.front() };
    }
    
    if ( uppercase )
        return { static_cast<char>( std::toupper(retval[0]) ), static_cast<char>( std::toupper(retval[1]) ) };
    else
        return retval;
}

const std::string_view Convert::ToString(bool value)
{
    if ( value )
        return Boolean::TrueString;
    else
        return Boolean::FalseString;
}

std::string Convert::ToString(char value)
{
    return std::string{ 1, value };
}

std::string Convert::ToString(float value)
{
    return ToChars(value);
}

std::string Convert::ToString(double value)
{
    return ToChars(value);
}

std::string Convert::ToString(int8_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(int16_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(int32_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase" ) );
    return {};
}

std::string Convert::ToString(int64_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint8_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint16_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint32_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    return {};
}

std::string Convert::ToString(uint64_t value, Base toBase)
{
    switch ( toBase )
    {
    case Base::Binary:
        return ToChars(value, 2);
    case Base::Octal:
        return ToChars(value, 8);
    case Base::Decimal:
        return ToChars(value);
    case Base::Hexadecimal:
        return ToChars(value, 16);
    default:
        break;
    }
    return {};
}

const std::string_view Convert::ToString(Diagnostics::SourceLevels sourcelevels_value)
try
{
    using namespace std::literals;

    static const std::map<Diagnostics::SourceLevels, const std::string_view> sourcelevels_map{
        { Diagnostics::SourceLevels::All,      "All"sv },
        { Diagnostics::SourceLevels::Off,      "Off"sv },
        { Diagnostics::SourceLevels::Critical,        "Critical"sv },
        { Diagnostics::SourceLevels::Error,           "Error"sv },
        { Diagnostics::SourceLevels::Warning,         "Warning"sv },
        { Diagnostics::SourceLevels::Information,     "Information"sv },
        { Diagnostics::SourceLevels::Verbose,         "Verbose"sv },
        { Diagnostics::SourceLevels::ActivityTracing, "ActivityTracing"sv }
    };

    return sourcelevels_map.at( sourcelevels_value );
}
catch (const std::out_of_range &)
{
    using namespace std::literals;

    ThrowWithTarget( ArgumentOutOfRangeException{ "sourcelevels_value"sv } );
    return {};
}

const std::string_view Convert::ToString(Diagnostics::TraceLevel tracelevel_value)
try
{
    using namespace std::literals;

    static const std::map<Diagnostics::TraceLevel, const std::string_view> type_map{
        { Diagnostics::TraceLevel::Off,     "Off"sv     },
        { Diagnostics::TraceLevel::Error,   "Error"sv   },
        { Diagnostics::TraceLevel::Warning, "Warning"sv },
        { Diagnostics::TraceLevel::Info,    "Info"sv    },
        { Diagnostics::TraceLevel::Verbose, "Verbose"sv }
    };

    return type_map.at( tracelevel_value );
}
catch (const std::out_of_range &)
{
    using namespace std::literals;

    ThrowWithTarget( ArgumentOutOfRangeException( "tracelevel_value"sv ) );
    return {};
}

const std::string_view Convert::ToString(Diagnostics::TraceOptions traceoptions_value)
try
{
    using namespace std::literals;

    static const std::map<Diagnostics::TraceOptions, const std::string_view> type_map{
        { Diagnostics::TraceOptions::None,      "None"sv      },
        { Diagnostics::TraceOptions::LogicalOperationStack , "LogicalOperationsStack"sv   },
        { Diagnostics::TraceOptions::DateTime,  "DateTime"sv  },
        { Diagnostics::TraceOptions::Timestamp, "Timestamp"sv },
        { Diagnostics::TraceOptions::ProcessId, "ProcessId"sv },
        { Diagnostics::TraceOptions::ThreadId, "ThreadId"sv   },
        { Diagnostics::TraceOptions::Callstack, "Callstack"sv }
    };

    return type_map.at( traceoptions_value );
}
catch (const std::out_of_range &)
{
    using namespace std::literals;

    ThrowWithTarget( ArgumentOutOfRangeException( "traceoptions_value"sv ) );
    return {};
}

Diagnostics::TraceLevel ToType(const std::string_view string_value, Diagnostics::TraceLevel)
try
{
    using namespace std::literals;

    static const std::map<const std::string_view, Diagnostics::TraceLevel> type_map{
        { "Off"sv,     Diagnostics::TraceLevel::Off },
        { "Error"sv,   Diagnostics::TraceLevel::Error },
        { "Warning"sv, Diagnostics::TraceLevel::Warning },
        { "Info"sv,    Diagnostics::TraceLevel::Info },
        { "Verbose"sv, Diagnostics::TraceLevel::Verbose }
    };

    return type_map.at( string_value );
}
catch (const std::out_of_range &)
{
    using namespace std::literals;

    ThrowWithTarget( ArgumentOutOfRangeException( "string_value"sv ) );
    return {};
}

Diagnostics::TraceOptions ToType(const std::string_view string_value, Diagnostics::TraceOptions)
try
{
    using namespace std::literals;

    static const std::map<const std::string_view, Diagnostics::TraceOptions> type_map{
        { "None"sv,         Diagnostics::TraceOptions::None },
        { "LogicalOperationStack"sv, Diagnostics::TraceOptions::LogicalOperationStack },
        { "DateTime"sv,     Diagnostics::TraceOptions::DateTime },
        { "Timestamp"sv,    Diagnostics::TraceOptions::Timestamp },
        { "ProcessId"sv,    Diagnostics::TraceOptions::ProcessId },
        { "ThreadId"sv,     Diagnostics::TraceOptions::ThreadId },
        { "Callstack"sv,    Diagnostics::TraceOptions::Callstack }
    };

    return type_map.at( string_value );
}
catch (const std::out_of_range &)
{
    using namespace std::literals;

    ThrowWithTarget( ArgumentOutOfRangeException( "string_value"sv ) );
    return {};
}

Diagnostics::SourceLevels ToType(const std::string_view string_value, Diagnostics::SourceLevels)
try
{
    using namespace std::literals;

    static const std::map<const std::string_view, Diagnostics::SourceLevels> type_map{
        { "All"sv,             Diagnostics::SourceLevels::All },
        { "Off"sv,             Diagnostics::SourceLevels::Off },
        { "Critical"sv,        Diagnostics::SourceLevels::Critical },
        { "Error"sv,           Diagnostics::SourceLevels::Error },
        { "Warning"sv,         Diagnostics::SourceLevels::Warning },
        { "Information"sv,     Diagnostics::SourceLevels::Information },
        { "Verbose"sv,         Diagnostics::SourceLevels::Verbose },
        { "ActivityTracing"sv, Diagnostics::SourceLevels::ActivityTracing }
    };

    return type_map.at( string_value );
}
catch(const std::exception& e)
{
    using namespace std::literals;

    ThrowWithTarget( ArgumentOutOfRangeException( "string_value"sv ) );
    return {};
}

std::vector<std::byte> Convert::FromHexString(const std::string_view input_string)
{
    std::vector<std::byte> result;

    if (input_string.empty())
        ThrowWithTarget( FormatException( "Input value is empty" ) );
    else if (input_string.size() % 2 != 0)
        ThrowWithTarget( FormatException( "Input value is not a multiple of 2" ) );
    else if ( std::ranges::find_if_not( input_string, [](unsigned char c) { return std::isxdigit(c); } ) != input_string.end())
        ThrowWithTarget( FormatException( "Input value contains non-hex characters" ) );
    
    result.reserve( input_string.size() / 2 );

    // Proceed byte-by-byte
    for (std::string_view input = input_string; !input.empty(); input.remove_prefix(2))
        result.push_back( From2HexCharsToByte( input.substr(0, 2) ) );

    return result; // This is LITTLE-ENDIAN now!
}

std::string Convert::ToHexString(const std::vector<std::byte> &input_bytes, bool uppercase)
{
    std::string hex_digits;

    hex_digits.reserve(2 * input_bytes.size());

    for (std::byte current_byte : input_bytes)
    {
        std::array<char, 2> hex_conversion{ FromByteTo2HexChars( current_byte, uppercase ) };

        hex_digits.append( hex_conversion.begin(), hex_conversion.end() );
    }

    return hex_digits;
}

std::string Convert::ToBase64String(std::span<const std::byte> input_bytes)
{
    const uint8_t hi_sextet = 0b11111100;
    const uint8_t not_hi_sextet = 0b00000011;
    const uint8_t lo_sextet = 0b00111111;
    const uint8_t not_lo_sextet = 0b11000000;
    const uint8_t hi_nybble = 0b11110000;
    const uint8_t lo_nybble = 0b00001111;
    const size_t chunk_size = 3;
    std::string base64_string;

    for (size_t chunk = 0; (chunk * chunk_size) < input_bytes.size(); ++chunk)
    {
        auto current_range{ std::views::drop( input_bytes, chunk * chunk_size ) };
        auto bytes{ std::views::take( current_range, chunk_size ) };

        if ( bytes.size() == chunk_size )
        {
            uint8_t first  = std::to_integer<uint8_t>( bytes[0] );
            uint8_t second = std::to_integer<uint8_t>( bytes[1] );
            uint8_t third  = std::to_integer<uint8_t>( bytes[2] );

            uint8_t one = (first & hi_sextet) >> 2;
            uint8_t two_h = (first & not_hi_sextet) << 4;
            uint8_t two_l = (second & hi_nybble) >> 4;
            uint8_t three_h = (second & lo_nybble) << 2;
            uint8_t three_l = (third & not_lo_sextet) >> 6;

            uint8_t two = two_h | two_l;
            uint8_t three = three_h | three_l;
            uint8_t four = third & lo_sextet;

            base64_string += Base64Table[ one ];
            base64_string += Base64Table[ two ];
            base64_string += Base64Table[ three ];
            base64_string += Base64Table[ four ];
        }
        else if ( bytes.size() == 2 )
        {
            uint8_t first  = std::to_integer<uint8_t>( bytes[0] );
            uint8_t second = std::to_integer<uint8_t>( bytes[1] );

            uint8_t one = (first & hi_sextet) >> 2;
            uint8_t two_h = (first & not_hi_sextet) << 4;
            uint8_t two_l = (second & hi_nybble) >> 4;
            uint8_t three_h = (second & lo_nybble) << 2;

            uint8_t two = two_h | two_l;
            uint8_t three = three_h;

            base64_string += Base64Table[ one ];
            base64_string += Base64Table[ two ];
            base64_string += Base64Table[ three ];
            base64_string += Base64PadChar;
        }
        else if ( bytes.size() == 1 )
        {
            uint8_t first  = std::to_integer<uint8_t>( bytes[0] );

            uint8_t one = (first & hi_sextet) >> 2;
            uint8_t two_h = (first & not_hi_sextet) << 4;

            uint8_t two = two_h;

            base64_string += Base64Table[ one ];
            base64_string += Base64Table[ two ];
            base64_string += Base64PadChar;
            base64_string += Base64PadChar;
        }
    }

    return base64_string;
}

}