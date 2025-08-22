#include "System/Diagnostics/TraceListenerCollection.hpp"
#include "System/Diagnostics/Private/Formatting.hpp"
#include <string>
#include <string_view>
#include <format>
#include <source_location>
#include <concepts>

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

    static void Write(std::string_view message);
    static void Write(std::string_view message, std::string_view category);

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    static void Write(std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        Write( std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }


    static void WriteIf(bool condition, std::string_view message);
    static void WriteIf(bool condition, std::string_view message, std::string_view category);

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    static void WriteIf(bool condition, std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        WriteIf( condition, std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }

    static void WriteLine(std::string_view message);
    static void WriteLine(std::string_view message, std::string_view category);

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    static void WriteLine(std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        WriteLine( std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }

    static void WriteLineIf(bool condition, std::string_view message);
    static void WriteLineIf(bool condition, std::string_view message, std::string_view category);

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    static void WriteLineIf(bool condition, std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        WriteLineIf( condition, std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }

    static void Assert(bool condition, const std::source_location = std::source_location::current());
    static void Assert(bool condition, std::string_view  message, const std::source_location = std::source_location::current());
    static void Assert(bool condition, std::string_view  message, std::string_view detail_message, const std::source_location = std::source_location::current());

    static void Fail(std::string_view message);
    static void Fail(std::string_view message, std::string_view category);

    template <typename T, typename ...Args>
        requires (!std::convertible_to<T, std::string_view> || sizeof...(Args) > 0)
    static void Fail(std::format_string<T, Args...> &&fmt, T &&arg1, Args &&... args)
    {
        Fail( std::string_view( std::vformat( fmt.get(), std::make_format_args( arg1, args... ) ) ) );
    }

    static void TraceError(std::string_view message);
    static void TraceWarning(std::string_view message);
    static void TraceInformation(std::string_view message);

    template <typename ...Args>
        requires (sizeof...(Args) > 0)
    static void TraceError(std::format_string<Args...> &&fmt, Args &&... args)
    {
        TraceError( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }
    template <typename ...Args>
        requires (sizeof...(Args) > 0)
    static void TraceWarning(std::format_string<Args...> &&fmt, Args &&... args)
    {
        TraceWarning( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }
    template <typename ...Args>
        requires (sizeof...(Args) > 0)
    static void TraceInformation(std::format_string<Args...> &&fmt, Args &&... args)
    {
        TraceInformation( std::string_view( std::vformat( fmt.get(), std::make_format_args( args... ) ) ) );
    }

    static TraceListenerCollection &Listeners();
};

}
