#include "System/Convert.hpp"
#include "System/Boolean.hpp"
#include "System/Exception.hpp"
#include <map>
#include <charconv>
#include <cassert>
#include <cctype>
#include <algorithm>

namespace System
{

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
    using namespace std::literals;

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
    using namespace std::literals;

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
    using namespace std::literals;

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
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
    return {};
}

std::string Convert::ToString(int64_t value, Base toBase)
{
    using namespace std::literals;

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
    using namespace std::literals;

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
    using namespace std::literals;

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
    using namespace std::literals;

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
    using namespace std::literals;

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

    ThrowWithTarget( ArgumentOutOfRangeException( "string_value" ) );
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

}