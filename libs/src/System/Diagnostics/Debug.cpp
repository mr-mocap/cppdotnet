#include "System/Diagnostics/Debug.hpp"
#include "System/Diagnostics/DebugAndTraceCommon.hpp"
#include <algorithm>

namespace System::Diagnostics
{

void Debug::Close()
{
    DebugAndTraceCommon::Close();
}

void Debug::Flush()
{
    DebugAndTraceCommon::Flush();
}

bool Debug::AutoFlush()
{
    return DebugAndTraceCommon::AutoFlush();
}

void Debug::AutoFlush(bool new_value)
{
    DebugAndTraceCommon::AutoFlush( new_value );
}

int Debug::IndentLevel()
{
    return DebugAndTraceCommon::IndentLevel();
}

void Debug::IndentLevel(int new_value)
{
    DebugAndTraceCommon::IndentLevel( new_value );
}

int Debug::IndentSize()
{
    return DebugAndTraceCommon::IndentSize();
}

void Debug::IndentSize(int new_value)
{
    DebugAndTraceCommon::IndentSize( new_value );
}

void Debug::Indent()
{
    DebugAndTraceCommon::Indent();
}

void Debug::Unindent()
{
    DebugAndTraceCommon::Unindent();
}

void Debug::Write(const std::string_view message)
{
    DebugAndTraceCommon::Write( message );
}

void Debug::Write(const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::Write( message, category );
}

void Debug::WriteIf(bool condition, const std::string_view message)
{
    DebugAndTraceCommon::WriteIf( condition, message );
}

void Debug::WriteIf(bool condition, const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::WriteIf( condition, message, category );
}

void Debug::WriteLine(const std::string_view message)
{
    DebugAndTraceCommon::WriteLine( message );
}

void Debug::WriteLine(const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::WriteLine( message, category );
}

void Debug::WriteLineIf(bool condition, const std::string_view message)
{
    DebugAndTraceCommon::WriteLineIf( condition, message );
}

void Debug::WriteLineIf(bool condition, const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::WriteLineIf( condition, message, category );
}

void Debug::Print(const std::string_view message)
{
    DebugAndTraceCommon::Print( message );
}

void Debug::Assert(bool condition, const std::source_location source_location)
{
    DebugAndTraceCommon::Assert( condition, source_location );
}

void Debug::Assert(bool condition, const std::string_view message, const std::source_location source_location)
{
    DebugAndTraceCommon::Assert( condition, message, source_location );
}

void Debug::Assert(bool condition,
                   const std::string_view message,
                   const std::string_view category,
                   const std::source_location source_location)
{
    DebugAndTraceCommon::Assert( condition, message, category, source_location );
}

void Debug::Fail(const std::string_view message)
{
    DebugAndTraceCommon::Fail( message );
}

void Debug::Fail(const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::Fail( message, category );
}

TraceListenerCollection &Debug::Listeners()
{
    return DebugAndTraceCommon::Instance().Listeners();
}

}
