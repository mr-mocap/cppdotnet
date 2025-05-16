#pragma once

#include "System/Exception.hpp"
#include "System/Private/private.hpp"
#include <format>
#include <string_view>
#include <variant>
#include <algorithm>

namespace System::Diagnostics
{

enum class TraceLevel
{
    Off = 0,
    Error,
    Warning,
    Info,
    Verbose
};

}

template <>
struct std::formatter<System::Diagnostics::TraceLevel>
{
    // Use {} to print the string form (default)
    // Use {:s} to print the string form and forward to the standard string formatting
    // Use {:i} to print the integer value and forward to the standard integer formatting
    using int_fmt         = std::formatter<int>;
    using string_view_fmt = std::formatter<std::string_view>;
    using underlying_formatter_type = std::variant<string_view_fmt, int_fmt>;

    static const std::string_view ToString(System::Diagnostics::TraceLevel level)
    {
        using namespace std::literals;

        static const std::string_view table[5] =
        {
            "Off"sv,
            "Error"sv,
            "Warning"sv,
            "Info"sv,
            "Verbose"sv
        };

        // Throw if enum is out-of-bounds...
        if ( (level < System::Diagnostics::TraceLevel::Off) ||
                (level > System::Diagnostics::TraceLevel::Verbose) )
            System::ThrowWithTarget( System::ArgumentOutOfRangeException( "level"sv ) );
        
        return table[ static_cast<int>(level) ];
    };

    constexpr auto parse(std::format_parse_context &ctx)
    {
        auto fmt_end = std::find( ctx.begin(), ctx.end(), '}' );

        if ( fmt_end != ctx.begin() )
        {
            // The FIRST character tells us how to format it
            char representation = *ctx.begin();

            if ( representation == 's' )
            {
                ctx.advance_to( std::next( ctx.begin() ) );
                underlying_formatter = string_view_fmt{};
                return std::get<string_view_fmt>(underlying_formatter).parse(ctx);
            }
            else if ( representation == 'i' )
            {
                ctx.advance_to( std::next( ctx.begin() ) );
                underlying_formatter = int_fmt{};
                return std::get<int_fmt>(underlying_formatter).parse(ctx);
            }
        }

        return fmt_end;
    }

    auto format(System::Diagnostics::TraceLevel tracelevel_value, std::format_context &ctx) const
    {
        if ( std::holds_alternative<int_fmt>(underlying_formatter) )
        {
            ctx.advance_to( std::get<int_fmt>(underlying_formatter).format( static_cast<int>(tracelevel_value), ctx) );
        }
        else if ( std::holds_alternative<string_view_fmt>(underlying_formatter) )
        {
            std::string buffer;

            buffer.append( std::formatter<System::Diagnostics::TraceLevel>::ToString(tracelevel_value) );
            ctx.advance_to( std::get<string_view_fmt>(underlying_formatter).format(buffer, ctx) );
        }
        return ctx.out();
    }

protected:
    underlying_formatter_type underlying_formatter{ string_view_fmt{} };
};