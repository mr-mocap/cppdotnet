module;

export module System:Guid;

import System:BitConverter;
export import System:Span;
export import System:ReadOnlySpan;
import <algorithm>;
import <format>;
import <cctype>;
import <cstdint>;
export import <cstddef>;
export import <string>;
export import <string_view>;
import <compare>;
export import <optional>;
import <uuid/uuid.h>;


namespace System
{

export
class Guid
{
public:
    constexpr Guid() = default;
    Guid(std::int32_t a, std::int16_t b, std::int16_t c,
         std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k);

    Guid(std::uint32_t a, std::uint16_t b, std::uint16_t c,
         std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k);

    Guid(ReadOnlySpan<std::byte> bytes);

    Guid(std::span<const std::byte> bytes)
        :
        // Delegating constructor...
        Guid( ReadOnlySpan<std::byte>(bytes) )
    {
    }
    Guid(std::string_view str_input);
    
    Guid(const Guid &other);

    Guid &operator =(const Guid &);

    static Guid Empty();

    static Guid AllBitsSet();

    int Variant() const { return 0; }
    int Version() const { return 0; }

    ReadOnlySpan<std::byte, 16> ToByteArray() const;

    std::string ToString() const;
    std::string ToString(std::string_view format) const;

    static Guid NewGuid();

    static Guid Parse(std::string_view input);
    static Guid Parse(ReadOnlySpan<char> input);

    static std::optional<Guid> TryParse(std::string_view input);
    static std::optional<Guid> TryParse(ReadOnlySpan<char> input);

    std::strong_ordering operator <=>(const Guid &other) const;

protected:
    uuid_t _data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    Guid(const uuid_t &external_value)
    {
        std::ranges::copy( std::span(external_value),
                           std::ranges::begin(_data) );
    }
};

}

#if 0
SPECIFIER | Format of return value
---------   ----------------------
N           32 digits:
            00000000000000000000000000000000

D           32 digits separated by hyphens:
            00000000-0000-0000-0000-000000000000

B           32 digits separated by hyphens, enclosed in braces:
            {00000000-0000-0000-0000-000000000000}

P           32 digits separated by hyphens, enclosed in parentheses:
            (00000000-0000-0000-0000-000000000000)

X           Four hexadecimal values enclosed in braces, where the fourth value is a subset
            of eight hexadecimal values that is also enclosed in braces:
            {0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}}
#endif

static std::string NStringToDString(std::string_view input)
{
    return std::format("{}-{}-{}-{}-{}", input.substr(0, 8),
                                         input.substr(8, 4),
                                         input.substr(12, 4),
                                         input.substr(16, 4),
                                         input.substr(20, 12));
}

static std::string XStringToDString(std::string_view input)
{
    return std::format("{}-{}-{}-{}{}-{}{}{}{}{}{}",
                       input.substr( 3, 8 ),

                       input.substr( 14, 4 ),

                       input.substr( 21, 4 ),

                       input.substr( 29, 2 ),
                       input.substr( 34, 2 ),

                       input.substr( 39, 2 ),
                       input.substr( 44, 2 ),
                       input.substr( 49, 2 ),
                       input.substr( 54, 2 ),
                       input.substr( 59, 2 ),
                       input.substr( 64, 2 )
                      );
}

static std::string AsDString(const uuid_t &input)
{
    // Two hex chars per byte, four hyphens and a '\0' terminator
    char buffer[ (16 * 2) + 4 + 1];

    uuid_unparse( input, buffer );
    return std::string( buffer, sizeof(buffer) - 1 );
}

static std::string AsNString(const uuid_t &input)
{
    std::string d_str = AsDString( input );

    // Erase the hyphens...
    return d_str.erase( 23, 1 ).erase( 18, 1 ).erase( 13, 1 ).erase( 8, 1 );
}

static std::string AsBString(const uuid_t &input)
{
    std::string d_str = AsDString( input );

    return d_str.insert( 0, 1, '{' ).append( 1, '}' );
}

static std::string AsPString(const uuid_t &input)
{
    std::string d_str = AsDString( input );

    return d_str.insert( 0, 1, '(' ).append( 1, ')' );
}

static std::string AsXString(const uuid_t &input)
{
    std::string d_str = AsDString( input );
    std::string_view view = d_str;

    // Erase the hyphens...
    return std::format("{}0x{},0x{},0x{},{}0x{},0x{},0x{},0x{},0x{},0x{},0x{},0x{}{}{}",
                       '{',
                       view.substr( 0, 8 ),
                       view.substr( 9, 4 ),
                       view.substr( 14, 4 ),
                       '{',
                       view.substr( 19, 2 ),
                       view.substr( 21, 2 ),
                       view.substr( 24, 2 ),
                       view.substr( 26, 2 ),
                       view.substr( 28, 2 ),
                       view.substr( 30, 2 ),
                       view.substr( 32, 2 ),
                       view.substr( 34, 2 ),
                       '}',
                       '}');
}

static bool AllDigitsAreHex(std::string_view input)
{
    if ( input.empty() )
        return false;
    return std::ranges::all_of( input, [](unsigned char i) { return std::isxdigit(i); } );
}

static bool IsNFormat(std::string_view input)
{
    if ( input.size() != 32 )
        return false;

    return AllDigitsAreHex( input );
}

static bool IsDFormat(std::string_view input)
{
    if ( input.size() != 36 )
        return false;
    
    // First group of digits...
    if ( !AllDigitsAreHex( input.substr( 0, 8 ) ) )
        return false;

    // Second group of digits...
    if ( !AllDigitsAreHex( input.substr( 9, 4 ) ) )
        return false;

    // Third group of digits...
    if ( !AllDigitsAreHex( input.substr( 14, 4 ) ) )
        return false;

    // Fourth group of digits...
    if ( !AllDigitsAreHex( input.substr( 19, 4 ) ) )
        return false;

    // Fifth group of digits...
    if ( !AllDigitsAreHex( input.substr( 24, 12 ) ) )
        return false;
    
    // Hyphens...
    if ( input[8] != '-' )
        return false;
    if ( input[13] != '-' )
        return false;
    if ( input[18] != '-' )
        return false;
    if ( input[23] != '-' )
        return false;
    return true;
}

static bool IsBFormat(std::string_view input)
{
    if ( input.size() != 38 )
        return false;
    
    if ( (input.front() != '{') || (input.back() != '}') )
        return false;

    // First group of digits...
    if ( !AllDigitsAreHex( input.substr( 1, 8 ) ) )
        return false;

    // Second group of digits...
    if ( !AllDigitsAreHex( input.substr( 10, 4 ) ) )
        return false;

    // Third group of digits...
    if ( !AllDigitsAreHex( input.substr( 15, 4 ) ) )
        return false;

    // Fourth group of digits...
    if ( !AllDigitsAreHex( input.substr( 20, 4 ) ) )
        return false;

    // Fifth group of digits...
    if ( !AllDigitsAreHex( input.substr( 25, 12 ) ) )
        return false;
    
    // Hyphens...
    if ( input[9] != '-' )
        return false;
    if ( input[14] != '-' )
        return false;
    if ( input[19] != '-' )
        return false;
    if ( input[24] != '-' )
        return false;
    return true;
}

static bool IsPFormat(std::string_view input)
{
    if ( input.size() != 38 )
        return false;
    
    if ( (input.front() != '(') || (input.back() != ')') )
        return false;

    // First group of digits...
    if ( !AllDigitsAreHex( input.substr( 1, 8 ) ) )
        return false;

    // Second group of digits...
    if ( !AllDigitsAreHex( input.substr( 10, 4 ) ) )
        return false;

    // Third group of digits...
    if ( !AllDigitsAreHex( input.substr( 15, 4 ) ) )
        return false;

    // Fourth group of digits...
    if ( !AllDigitsAreHex( input.substr( 20, 4 ) ) )
        return false;

    // Fifth group of digits...
    if ( !AllDigitsAreHex( input.substr( 25, 12 ) ) )
        return false;
    
    // Hyphens...
    if ( input[9] != '-' )
        return false;
    if ( input[14] != '-' )
        return false;
    if ( input[19] != '-' )
        return false;
    if ( input[24] != '-' )
        return false;
    return true;
}

static bool IsXFormat(std::string_view input)
{
    if ( input.size() != 68 )
        return false;
    
    if ( (input.front() != '{') || (input.back() != '}') )
        return false;

    if ( (input[26] != '{') || (input[66] != '}') )
        return false;

    // Commas...
    if ( input[11] != ',' )
        return false;
    if ( input[18] != ',' )
        return false;
    if ( input[25] != ',' )
        return false;
    if ( input[31] != ',' )
        return false;
    if ( input[36] != ',' )
        return false;
    if ( input[41] != ',' )
        return false;
    if ( input[46] != ',' )
        return false;
    if ( input[51] != ',' )
        return false;
    if ( input[56] != ',' )
        return false;
    if ( input[61] != ',' )
        return false;

    // First group of digits...
    if ( !AllDigitsAreHex( input.substr( 3, 8 ) ) )
        return false;

    // Second group of digits...
    if ( !AllDigitsAreHex( input.substr( 14, 4 ) ) )
        return false;

    // Third group of digits...
    if ( !AllDigitsAreHex( input.substr( 21, 4 ) ) )
        return false;

    // Fourth group of digits...
    if ( !AllDigitsAreHex( input.substr( 29, 2 ) ) )
        return false;
    if ( !AllDigitsAreHex( input.substr( 34, 2 ) ) )
        return false;
    if ( !AllDigitsAreHex( input.substr( 39, 2 ) ) )
        return false;
    if ( !AllDigitsAreHex( input.substr( 44, 2 ) ) )
        return false;
    if ( !AllDigitsAreHex( input.substr( 49, 2 ) ) )
        return false;
    if ( !AllDigitsAreHex( input.substr( 54, 2 ) ) )
        return false;
    if ( !AllDigitsAreHex( input.substr( 59, 2 ) ) )
        return false;
    if ( !AllDigitsAreHex( input.substr( 64, 2 ) ) )
        return false;

    // The hex prefixes...
    if ( input.substr( 1, 2 ) != "0x" )
        return false;
    if ( input.substr( 12, 2 ) != "0x" )
        return false;
    if ( input.substr( 19, 2 ) != "0x" )
        return false;

    if ( input.substr( 27, 2 ) != "0x" )
        return false;
    if ( input.substr( 32, 2 ) != "0x" )
        return false;
    if ( input.substr( 37, 2 ) != "0x" )
        return false;
    if ( input.substr( 42, 2 ) != "0x" )
        return false;
    if ( input.substr( 47, 2 ) != "0x" )
        return false;
    if ( input.substr( 52, 2 ) != "0x" )
        return false;
    if ( input.substr( 57, 2 ) != "0x" )
        return false;
    if ( input.substr( 62, 2 ) != "0x" )
        return false;
    return true;
}

namespace System
{

Guid::Guid(std::int32_t a, std::int16_t b, std::int16_t c,
           std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k)
{
    auto put_iter = std::begin(_data);

    for (std::byte i : BitConverter::GetBytes(a))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(b))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(c))
        *put_iter++ = static_cast<unsigned char>(i);
    
    *put_iter++ = static_cast<unsigned char>(d);
    *put_iter++ = static_cast<unsigned char>(e);
    *put_iter++ = static_cast<unsigned char>(f);
    *put_iter++ = static_cast<unsigned char>(g);
    *put_iter++ = static_cast<unsigned char>(h);
    *put_iter++ = static_cast<unsigned char>(i);
    *put_iter++ = static_cast<unsigned char>(j);
    *put_iter++ = static_cast<unsigned char>(k);
}

Guid::Guid(std::uint32_t a, std::uint16_t b, std::uint16_t c,
           std::byte d, std::byte e, std::byte f, std::byte g, std::byte h, std::byte i, std::byte j, std::byte k)
{
    auto put_iter = std::begin(_data);

    for (std::byte i : BitConverter::GetBytes(a))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(b))
        *put_iter++ = static_cast<unsigned char>(i);
    for (std::byte i : BitConverter::GetBytes(c))
        *put_iter++ = static_cast<unsigned char>(i);
    
    *put_iter++ = static_cast<unsigned char>(d);
    *put_iter++ = static_cast<unsigned char>(e);
    *put_iter++ = static_cast<unsigned char>(f);
    *put_iter++ = static_cast<unsigned char>(g);
    *put_iter++ = static_cast<unsigned char>(h);
    *put_iter++ = static_cast<unsigned char>(i);
    *put_iter++ = static_cast<unsigned char>(j);
    *put_iter++ = static_cast<unsigned char>(k);
}

Guid::Guid(ReadOnlySpan<std::byte> bytes)
{
    using namespace std::literals::string_view_literals;

    if ( bytes.Length() != 16 )
        ThrowWithTarget( ArgumentOutOfRangeException( "bytes"sv, "Does not have exactly 16 bytes"sv ) );

    bytes.CopyTo( std::as_writable_bytes( std::span(_data) ) );
}

Guid::Guid(const Guid &other)
{
    uuid_copy( _data, other._data );
}

Guid::Guid(std::string_view str_input)
{
    Guid temp = Parse(str_input);

    std::ranges::copy( std::span(temp._data), std::ranges::begin(_data) );
}

ReadOnlySpan<std::byte, 16> Guid::ToByteArray() const
{
    return ReadOnlySpan<std::byte, 16>( std::as_bytes( std::span(_data) ) );
}

Guid Guid::NewGuid()
{
    uuid_t uuid;

    uuid_generate( uuid );
    return Guid( std::as_bytes( std::span(uuid) ) );
}

Guid Guid::Empty()
{
    return Guid( std::as_bytes( std::span( std::initializer_list<unsigned char>{0, 0, 0, 0,
                                                                                0, 0, 0, 0,
                                                                                0, 0, 0, 0,
                                                                                0, 0, 0, 0} ) ) );
}

Guid Guid::AllBitsSet()
{
    return Guid( std::as_bytes( std::span( std::initializer_list<unsigned char>{0xFF, 0xFF, 0xFF, 0xFF,
                                                                                0xFF, 0xFF, 0xFF, 0xFF,
                                                                                0xFF, 0xFF, 0xFF, 0xFF,
                                                                                0xFF, 0xFF, 0xFF, 0xFF} ) ) );
}

std::string Guid::ToString() const
{
    return AsDString( _data );
}

std::string Guid::ToString(std::string_view format) const
{
    using namespace std::literals::string_view_literals;

    if ( format.empty() )
        return AsDString( _data );

    if ( format == "N" )
        return AsNString( _data );
    else if ( format == "D" )
        return AsDString( _data );
    else if ( format == "B" )
        return AsBString( _data );
    else if ( format == "P" )
        return AsPString( _data );
    else if ( format == "X" )
        return AsXString( _data );
    else
        ThrowWithTarget( FormatException{ "'format' is not an available format type"sv } );

    return {}; // Should never reach this!
}

Guid Guid::Parse(std::string_view input)
{
    using namespace std::literals::string_view_literals;

    if ( input.empty() )
        ThrowWithTarget( ArgumentNullException{ "input"sv } );
    
    std::string d_format_string;

    // Transform all other formats to D format, because that is what uuid_parse/uuid_parse_range understands
    do
    {
        if ( IsNFormat( input ) )
        {
            d_format_string = NStringToDString( input );
            break;
        }
        else if ( IsDFormat( input ) )
        {
            // Already in the correct format
            d_format_string = input;
            break;
        }
        else if ( IsBFormat( input ) )
        {
            d_format_string = input.substr( 1, 36 );
            break;
        }
        else if ( IsPFormat( input ) )
        {
            d_format_string = input.substr( 1, 36 );
            break;
        }
        else if ( IsXFormat( input ) )
        {
            d_format_string = XStringToDString( input );
            break;
        }

        ThrowWithTarget( FormatException{ "String is not in one of the expected formats (N, D, B, P, or X)"sv } );
    } while (false);
    
    // We should now have a D format string to parse, so parse it!
    uuid_t output_uuid;

    int result = uuid_parse_range( d_format_string.data(), d_format_string.data() + d_format_string.size(), output_uuid );

    if ( result == -1 )
    {
        // Something went wrong
        ThrowWithTarget( FormatException{ "String is not in expected format"sv } );
    }

    return Guid( output_uuid );
}

Guid Guid::Parse(ReadOnlySpan<char> input)
{
    return Parse( std::string_view( input.begin(), input.end() ) );
}

std::optional<Guid> Guid::TryParse(std::string_view input)
{
    using namespace std::literals::string_view_literals;

    if ( input.empty() )
        return { };
    
    std::string d_format_string;

    // Transform all other formats to D format, because that is what uuid_parse/uuid_parse_range understands
    do
    {
        if ( IsNFormat( input ) )
        {
            d_format_string = NStringToDString( input );
            break;
        }
        else if ( IsDFormat( input ) )
        {
            // Already in the correct format
            d_format_string = input;
            break;
        }
        else if ( IsBFormat( input ) )
        {
            d_format_string = input.substr( 1, 36 );
            break;
        }
        else if ( IsPFormat( input ) )
        {
            d_format_string = input.substr( 1, 36 );
            break;
        }
        else if ( IsXFormat( input ) )
        {
            d_format_string = XStringToDString( input );
            break;
        }

        return { };
    } while (false);
    
    // We should now have a D format string to parse, so parse it!
    uuid_t output_uuid;

    int result = uuid_parse_range( d_format_string.data(), d_format_string.data() + d_format_string.size(), output_uuid );

    if ( result == -1 )
    {
        // Something went wrong
        return { };
    }

    return Guid( output_uuid );
}

std::optional<Guid> Guid::TryParse(ReadOnlySpan<char> input)
{
    return TryParse( std::string_view( input.begin(), input.end() ) );
}

Guid &Guid::operator =(const Guid &other)
{
    std::ranges::copy( other._data, _data );
    return *this;
}

std::strong_ordering Guid::operator <=>(const Guid &other) const
{
    int result = uuid_compare( _data, other._data );

    if ( result < 0 )
        return std::strong_ordering::less;
    if ( result > 0 )
        return std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

}