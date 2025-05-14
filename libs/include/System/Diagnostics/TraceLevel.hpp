#pragma once

#include "System/Exception.hpp"
#include <format>
#include <string_view>

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
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(System::Diagnostics::TraceLevel tracelevel_value, FormatContext &ctx) const
    {
        using namespace std::literals;

        static const std::string_view string_mapping[5] =
        {
            "Off"sv,
            "Error"sv,
            "Warning"sv,
            "Info"sv,
            "Verbose"sv
        };

        if ( (tracelevel_value < System::Diagnostics::TraceLevel::Off) ||
             (tracelevel_value > System::Diagnostics::TraceLevel::Verbose) )
            System::ThrowWithTarget( System::ArgumentOutOfRangeException( "tracelevel_value"sv ) );

        return std::format_to( ctx.out(), "{}", string_mapping[ static_cast<int>(tracelevel_value) ] );
    }
};