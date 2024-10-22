#include "System/Convert.hpp"
#include "System/Boolean.hpp"
#include "System/Exception.hpp"
#include <format>
#include <map>

namespace System
{

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
    return std::format("{}", value);
}

std::string Convert::ToString(double value)
{
    return std::format("{}", value);
}

std::string Convert::ToString(int8_t value, Base toBase)
{
    using namespace std::literals;

    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
    return {};
}

std::string Convert::ToString(int16_t value, Base toBase)
{
    using namespace std::literals;

    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
    return {};
}

std::string Convert::ToString(int32_t value, Base toBase)
{
    using namespace std::literals;

    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
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
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
    return {};
}

std::string Convert::ToString(uint8_t value, Base toBase)
{
    using namespace std::literals;

    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
    return {};
}

std::string Convert::ToString(uint16_t value, Base toBase)
{
    using namespace std::literals;

    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
    return {};
}

std::string Convert::ToString(uint32_t value, Base toBase)
{
    using namespace std::literals;

    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
    return {};
}

std::string Convert::ToString(uint64_t value, Base toBase)
{
    using namespace std::literals;

    switch ( toBase )
    {
    case Base::Binary:
        return std::format("{:b}", value);
    case Base::Octal:
        return std::format("{:o}", value);
    case Base::Decimal:
        return std::format("{}", value);
    case Base::Hexadecimal:
        return std::format("{:X}", value);
    default:
        break;
    }
    ThrowWithTarget( ArgumentOutOfRangeException( "toBase"sv ) );
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

}