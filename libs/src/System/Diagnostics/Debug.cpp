#include "System/Diagnostics/Debug.hpp"
#include "System/Diagnostics/Private/DebugAndTraceCommon.hpp"
#include <algorithm>

namespace System::Diagnostics
{

void Debug::Close()
{
    Private::DebugAndTraceCommon::Close();
}

void Debug::Flush()
{
    Private::DebugAndTraceCommon::Flush();
}

bool Debug::AutoFlush()
{
    return Private::DebugAndTraceCommon::AutoFlush();
}

void Debug::AutoFlush(bool new_value)
{
    Private::DebugAndTraceCommon::AutoFlush( new_value );
}

int Debug::IndentLevel()
{
    return Private::DebugAndTraceCommon::IndentLevel();
}

void Debug::IndentLevel(int new_value)
{
    Private::DebugAndTraceCommon::IndentLevel( new_value );
}

int Debug::IndentSize()
{
    return Private::DebugAndTraceCommon::IndentSize();
}

void Debug::IndentSize(int new_value)
{
    Private::DebugAndTraceCommon::IndentSize( new_value );
}

void Debug::Indent()
{
    Private::DebugAndTraceCommon::Indent();
}

void Debug::Unindent()
{
    Private::DebugAndTraceCommon::Unindent();
}

void Debug::Write(const std::string_view message)
{
    Private::DebugAndTraceCommon::Write( message );
}

void Debug::Write(const std::string_view message, const std::string_view category)
{
    Private::DebugAndTraceCommon::Write( message, category );
}

void Debug::WriteIf(bool condition, const std::string_view message)
{
    Private::DebugAndTraceCommon::WriteIf( condition, message );
}

void Debug::WriteIf(bool condition, const std::string_view message, const std::string_view category)
{
    Private::DebugAndTraceCommon::WriteIf( condition, message, category );
}

void Debug::WriteLine(const std::string_view message)
{
    Private::DebugAndTraceCommon::WriteLine( message );
}

void Debug::WriteLine(const std::string_view message, const std::string_view category)
{
    Private::DebugAndTraceCommon::WriteLine( message, category );
}

void Debug::WriteLineIf(bool condition, const std::string_view message)
{
    Private::DebugAndTraceCommon::WriteLineIf( condition, message );
}

void Debug::WriteLineIf(bool condition, const std::string_view message, const std::string_view category)
{
    Private::DebugAndTraceCommon::WriteLineIf( condition, message, category );
}

void Debug::Print(const std::string_view message)
{
    Private::DebugAndTraceCommon::Print( message );
}

void Debug::Assert(bool condition, const std::source_location source_location)
{
    Private::DebugAndTraceCommon::Assert( condition, source_location );
}

void Debug::Assert(bool condition, const std::string_view message, const std::source_location source_location)
{
    Private::DebugAndTraceCommon::Assert( condition, message, source_location );
}

void Debug::Assert(bool condition,
                   const std::string_view message,
                   const std::string_view category,
                   const std::source_location source_location)
{
    Private::DebugAndTraceCommon::Assert( condition, message, category, source_location );
}

void Debug::Fail(const std::string_view message)
{
    Private::DebugAndTraceCommon::Fail( message );
}

void Debug::Fail(const std::string_view message, const std::string_view category)
{
    Private::DebugAndTraceCommon::Fail( message, category );
}

TraceListenerCollection &Debug::Listeners()
{
    return Private::DebugAndTraceCommon::Instance().Listeners();
}

}
