#pragma once

#include "System/Diagnostics/TraceListenerCollection.hpp"
#include <string>
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

    static void WriteIf(bool condition, const std::string_view message);
    static void WriteIf(bool condition, const std::string_view message, const std::string_view category);

    static void WriteLine(const std::string_view message);
    static void WriteLine(const std::string_view message, const std::string_view category);

    static void WriteLineIf(bool condition, const std::string_view message);
    static void WriteLineIf(bool condition, const std::string_view message, const std::string_view category);

    

    static void Assert(bool condition, const std::source_location = std::source_location::current());
    static void Assert(bool condition, const std::string_view message,
                       const std::source_location = std::source_location::current());
    static void Assert(bool condition, const std::string_view message, const std::string_view category,
                       const std::source_location = std::source_location::current());

    static void Fail(const std::string_view message);
    static void Fail(const std::string_view message, const std::string_view category);

    static void TraceError(const std::string_view message);
    static void TraceWarning(const std::string_view message);
    static void TraceInformation(const std::string_view message);

    static TraceListenerCollection &Listeners();
};

}
