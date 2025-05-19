#pragma once

#include "System/Diagnostics/TraceListenerCollection.hpp"
#include <string>
#include <string_view>
#include <format>
#include <source_location>

namespace System::Diagnostics
{

class Trace final
{
public:

    static void Close();
    static void Flush();
    static bool AutoFlush();
    static void AutoFlush(bool new_value);

    static int  IndentLevel();
    static void IndentLevel(int new_value);

    static int  IndentSize();
    static void IndentSize(int new_value);

    static void Indent();
    static void Unindent();

    static void Write(const std::string_view message);
    static void Write(const std::string_view message, const std::string_view category);

    template <typename ...Args>
    static void Write(std::format_string<Args...> &&fmt, Args &&... args)
    {
        Write( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void WriteIf(bool condition, const std::string_view message);
    static void WriteIf(bool condition, const std::string_view message, const std::string_view category);

    template <typename ...Args>
    static void WriteIf(bool condition, std::format_string<Args...> &&fmt, Args &&... args)
    {
        WriteIf( condition, std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void WriteLine(const std::string_view message);
    static void WriteLine(const std::string_view message, const std::string_view category);

    template <typename ...Args>
    static void WriteLine(std::format_string<Args...> &&fmt, Args &&... args)
    {
        WriteLine( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void WriteLineIf(bool condition, const std::string_view message);
    static void WriteLineIf(bool condition, const std::string_view message, const std::string_view category);

    template <typename ...Args>
    static void WriteLineIf(bool condition, std::format_string<Args...> &&fmt, Args &&... args)
    {
        WriteLineIf( condition, std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    

    static void Assert(bool condition, const std::source_location = std::source_location::current());
    static void Assert(bool condition, const std::string_view message,
                       const std::source_location = std::source_location::current());
    static void Assert(bool condition, const std::string_view message, const std::string_view category,
                       const std::source_location = std::source_location::current());

    static void Fail(const std::string_view message);
    static void Fail(const std::string_view message, const std::string_view category);

    template <typename ...Args>
    static void Fail(std::format_string<Args...> &&fmt, Args &&... args)
    {
        Fail( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void TraceError(const std::string_view message);
    static void TraceWarning(const std::string_view message);
    static void TraceInformation(const std::string_view message);

    template <typename ...Args>
    static void TraceError(std::format_string<Args...> &&fmt, Args &&... args)
    {
        TraceError( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }
    template <typename ...Args>
    static void TraceWarning(std::format_string<Args...> &&fmt, Args &&... args)
    {
        TraceWarning( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }
    template <typename ...Args>
    static void TraceInformation(std::format_string<Args...> &&fmt, Args &&... args)
    {
        TraceInformation( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static TraceListenerCollection &Listeners();
};

}
