#include "System/Convert.hpp"
#include "System/Boolean.hpp"
#include "System/Exception.hpp"
#include "System/BitConverter.hpp"
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
static       std::string_view Base64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char             Base64PadChar = '=';

static       std::string_view Base85Table = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstu";
static const char             Base85SpecialCase1 = 'z';
static const char             Base85SpecialCase2 = 'y';
static const std::uint32_t    Base85SpecialCaseValue1 = 0u;
static const std::uint32_t    Base85SpecialCaseValue2 = 0x20202020u; // All spaces

static       std::string_view Ascii85_RFC_1924 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

inline bool IsValidBase64(const char input)
{
    return Base64Table.find( input ) != std::string_view::npos;
}

inline char EncodeBase64(const uint8_t input)
{
    PRECONDITION( input < Base64Table.size() );

    return Base64Table[ input ];
}

inline std::byte DecodeBase64(char input)
{
    PRECONDITION( IsValidBase64(input) );

    return static_cast<std::byte>(Base64Table.find( input ));
}

inline bool IsValidBase85(const char input)
{
    return Base85Table.find( input ) != std::string_view::npos;
}

inline char EncodeBase85(const uint8_t input)
{
    PRECONDITION( input < Base85Table.size() );

    return Base85Table[ input ];
}

inline std::byte DecodeBase85(char input)
{
    PRECONDITION( IsValidBase85(input) );

    return static_cast<std::byte>(Base85Table.find( input ));
}

static std::string From4Base64Chars(std::span<const char, 4> input)
{
    PRECONDITION( IsValidBase64(input[0]) );
    PRECONDITION( IsValidBase64(input[1]) );
    PRECONDITION( IsValidBase64(input[2]) || (input[2] == Base64PadChar) );
    PRECONDITION( IsValidBase64(input[3]) || (input[3] == Base64PadChar) );

    char first  = std::bit_cast<char>( DecodeBase64( input[0] ) );
    char second = std::bit_cast<char>( DecodeBase64( input[1] ) );

    char one = (first << 2) | (second >> 4);

    if ( input[3] == Base64PadChar )
    {
        // There will be at most TWO bytes output...
        if ( input[2] == Base64PadChar )
            return std::string( 1, one ); // But only one in this case
        
        char third  = std::bit_cast<char>( DecodeBase64( input[2] ) );
        char two = ((second & 0x0F) << 4) | (third >> 2);

        return std::string().append(1, one).append(1, two); // ...aaaaand two bytes
    }
    char third  = std::bit_cast<char>( DecodeBase64( input[2] ) );
    char fourth = std::bit_cast<char>( DecodeBase64( input[3] ) );

    char two = ((second & 0x0F) << 4) | (third >> 2);
    char three = ((third & 0b00000011) << 6) | fourth;

    return std::string().append(1, one).append(1, two).append(1, three); // The full three bytes
}

std::byte Convert::From2HexCharsToByte(std::string_view input_string)
{
    PRECONDITION(input_string.size() == 2);
    PRECONDITION( std::isxdigit( input_string.front() ) );
    PRECONDITION( std::isxdigit( input_string.back() ) );

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

std::string_view Convert::ToString(bool value)
{
    return Boolean{value}.ToString();
}

std::string Convert::ToString(std::byte value)
{
    return std::string{ 1, static_cast<char>(value) };
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

std::string_view Convert::ToString(Diagnostics::SourceLevels sourcelevels_value)
try
{
    using namespace std::literals;

    static const std::map<Diagnostics::SourceLevels, std::string_view> sourcelevels_map{
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

std::string_view Convert::ToString(Diagnostics::TraceOptions traceoptions_value)
try
{
    using namespace std::literals;

    static const std::map<Diagnostics::TraceOptions, std::string_view> type_map{
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

Diagnostics::TraceLevel ToType(std::string_view string_value, Diagnostics::TraceLevel)
try
{
    using namespace std::literals;

    static const std::map<std::string_view, Diagnostics::TraceLevel> type_map{
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

Diagnostics::TraceOptions ToType(std::string_view string_value, Diagnostics::TraceOptions)
try
{
    using namespace std::literals;

    static const std::map<std::string_view, Diagnostics::TraceOptions> type_map{
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

Diagnostics::SourceLevels ToType(std::string_view string_value, Diagnostics::SourceLevels)
try
{
    using namespace std::literals;

    static const std::map<std::string_view, Diagnostics::SourceLevels> type_map{
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

std::vector<std::byte> Convert::FromHexString(std::string_view input_string)
{
    std::vector<std::byte> result;

    if (input_string.size() % 2 != 0)
        ThrowWithTarget( FormatException( "Input value is not empty and not a multiple of 2" ) );
    else if ( std::ranges::find_if_not( input_string, [](unsigned char c) { return std::isxdigit(c); } ) != input_string.end())
        ThrowWithTarget( FormatException( "Input value contains non-hex characters" ) );
    
    result.reserve( input_string.size() / 2 );

    // Proceed byte-by-byte
    for (std::string_view input = input_string; !input.empty(); input.remove_prefix(2))
        result.push_back( From2HexCharsToByte( input.substr(0, 2) ) );

    return result; // This is LITTLE-ENDIAN now!
}

//std::string Convert::ToHexString(const std::vector<std::byte> &input_bytes, bool uppercase)
std::string Convert::ToHexString(std::span<const std::byte> input_bytes, bool uppercase)
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

            base64_string += EncodeBase64( one );
            base64_string += EncodeBase64( two );
            base64_string += EncodeBase64( three );
            base64_string += EncodeBase64( four );
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

            base64_string += EncodeBase64( one );
            base64_string += EncodeBase64( two );
            base64_string += EncodeBase64( three );
            base64_string += Base64PadChar;
        }
        else if ( bytes.size() == 1 )
        {
            uint8_t first  = std::to_integer<uint8_t>( bytes[0] );

            uint8_t one = (first & hi_sextet) >> 2;
            uint8_t two_h = (first & not_hi_sextet) << 4;

            uint8_t two = two_h;

            base64_string += EncodeBase64( one );
            base64_string += EncodeBase64( two );
            base64_string += Base64PadChar;
            base64_string += Base64PadChar;
        }
    }

    return base64_string;
}

std::vector<std::byte> Convert::FromBase64String(std::span<const char> input_ascii_string)
{
    if ( input_ascii_string.size() % 4 != 0)
        ThrowWithTarget( FormatException( "Input value length is not a multiple of 4" ) );

    const size_t chunk_size = 4;
    std::vector<std::byte> result_bytes;

    result_bytes.reserve( (input_ascii_string.size() / 4) * 3 ); // Will be AT MOST this size!
    for (size_t chunk = 0; (chunk * chunk_size) < input_ascii_string.size(); ++chunk)
    {
        auto current_range{ std::views::drop( input_ascii_string, chunk * chunk_size ) };
        auto bytes{ std::views::take( current_range, chunk_size ) };

        {
            std::string converted{ From4Base64Chars( std::span<const char, 4>{ bytes.begin(), bytes.size() } ) };

            std::ranges::transform( converted, std::back_inserter( result_bytes ), [](char input) { return static_cast<std::byte>(input); } );
        }
    }

    return result_bytes;
}

std::string Convert::ToBase85String(std::span<const std::byte> input_bytes)
{
    const size_t chunk_size = 4;
    std::string base85_string;

    base85_string.reserve( 5 );
    for (size_t chunk = 0; (chunk * chunk_size) < input_bytes.size(); ++chunk)
    {
        std::span<const std::byte> current_range{ std::views::drop( input_bytes, chunk * chunk_size ) };
        std::span<const std::byte> bytes{ std::views::take( current_range, chunk_size ) };

        if ( bytes.size() == chunk_size )
        {
            std::uint32_t value = BitConverter::To<std::uint32_t, std::endian::big>(bytes);
            const std::uint32_t upper_encoding_limit = 0b01111111111111111111111111111111u; // 2^32 - 1

            // Encoding error!  (Unrepresentable value)
            // TODO: FIXME
            if ( value > upper_encoding_limit )
                continue; // Skip these 4 bytes

            // All zeros encodes to 'z', so check for that...
            if ( value == Base85SpecialCaseValue1 )
            {
                base85_string.push_back( Base85SpecialCase1 );
                continue;
            }
            if ( value == Base85SpecialCaseValue2 )
            {
                base85_string.push_back( Base85SpecialCase2 );
                continue;
            }

            for (;
                    value;
                    value /= 85)
            {
                base85_string.push_back( EncodeBase85( value % 85 ) );
            }
            continue;
        }

        // Non-chunk-size ...
        {
            std::array<std::byte, 4> padded_chunk{ std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0} };

            std::copy( bytes.begin(), bytes.end(), padded_chunk.begin() );
            std::uint32_t value = BitConverter::To<std::uint32_t, std::endian::big>( padded_chunk );
            std::size_t skip_first_n_items = 5 - (bytes.size() + 1);

            for (std::size_t item_number = 1; value; ++item_number, value /= 85 )
            {
                if ( item_number <= skip_first_n_items )
                    continue;

                base85_string.push_back( EncodeBase85( value % 85 ) );
            }
        }
    }

    return { base85_string.rbegin(), base85_string.rend() };
}

std::vector<std::byte> Convert::FromBase85String(std::string_view input_ascii_string)
{
    UNUSED(input_ascii_string);

    return {};
}

std::vector<std::byte> Convert::FromBase85String(std::span<const char> input_ascii_string)
{
    UNUSED(input_ascii_string);

    return {};
}

Convert::BaseConversion32Bit_t Convert::ToBase(std::uint32_t input_number, unsigned int base)
{
    PRECONDITION( base >= 2 );
    PRECONDITION( base <= 256 );

    std::array<std::byte, 32> output_array;
    unsigned int num_digits = 0;

    do
    {
        output_array[ num_digits ] = std::byte( input_number % base );

        ++num_digits;
        input_number /= base;
    } while ( input_number );
    
    return BaseConversion32Bit_t( output_array, num_digits, base );
}

}