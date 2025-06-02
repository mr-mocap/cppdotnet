#pragma once

#include "System/Diagnostics/TraceListenerCollection.hpp"
#include <string>
#include <format>
#include <source_location>

namespace System::Diagnostics
{
    
class Debug final
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

    static void Write(std::string_view message);
    static void Write(std::string_view message, std::string_view category);

    template <typename ...Args>
    static void Write(std::format_string<Args...> &&fmt, Args &&... args)
    {
        Write( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void WriteIf(bool condition, std::string_view message);
    static void WriteIf(bool condition, std::string_view message, std::string_view category);

    template <typename ...Args>
    static void WriteIf(bool condition, std::format_string<Args...> &&fmt, Args &&... args)
    {
        WriteIf( condition, std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void WriteLine(std::string_view message);
    static void WriteLine(std::string_view message, std::string_view category);

    template <typename ...Args>
    static void WriteLine(std::format_string<Args...> &&fmt, Args &&... args)
    {
        WriteLine( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void WriteLineIf(bool condition, std::string_view message);
    static void WriteLineIf(bool condition, std::string_view message, std::string_view category);

    template <typename ...Args>
    static void WriteLineIf(bool condition, std::format_string<Args...> &&fmt, Args &&... args)
    {
        WriteLineIf( condition, std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void Print(std::string_view message);

    template <typename ...Args>
    static void Print(std::format_string<Args...> &&fmt, Args &&... args)
    {
        Print( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static void Assert(bool condition, const std::source_location = std::source_location::current());
    static void Assert(bool condition, std::string_view message,
                       const std::source_location = std::source_location::current());
    static void Assert(bool condition, std::string_view message, std::string_view category,
                       const std::source_location = std::source_location::current());
#if 0
    template <typename ...Args>
    static void Assert(bool condition, std::format_string<Args...> &&fmt, Args &&... args)
    {
        Assert( condition, std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ), std::source_location::current() );
    }
#endif

    static void Fail(std::string_view message);
    static void Fail(std::string_view message, std::string_view category);

    template <typename ...Args>
    static void Fail(std::format_string<Args...> &&fmt, Args &&... args)
    {
        Fail( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static TraceListenerCollection &Listeners();
};

}
