#include <cppdotnet/System/Diagnostics/Debug.hpp>
#include <cppdotnet/System/Diagnostics/Private/DebugAndTraceCommon.hpp>

namespace System::Diagnostics
{

void Debug::Close()
{
    Private::GetGlobalTracer()->Close();
}

void Debug::Flush()
{
    Private::GetGlobalTracer()->Flush();
}

bool Debug::AutoFlush()
{
    return Private::GetGlobalTracer()->AutoFlush();
}

void Debug::AutoFlush(bool new_value)
{
    Private::GetGlobalTracer()->AutoFlush( new_value );
}

int Debug::IndentLevel()
{
    return Private::GetGlobalTracer()->IndentLevel();
}

void Debug::IndentLevel(int new_value)
{
    Private::GetGlobalTracer()->IndentLevel( new_value );
}

int Debug::IndentSize()
{
    return Private::GetGlobalTracer()->IndentSize();
}

void Debug::IndentSize(int new_value)
{
    Private::GetGlobalTracer()->IndentSize( new_value );
}

void Debug::Indent()
{
    Private::GetGlobalTracer()->Indent();
}

void Debug::Unindent()
{
    Private::GetGlobalTracer()->Unindent();
}

void Debug::Write(std::string_view message)
{
    Private::GetGlobalTracer()->Write( message );
}

void Debug::Write(std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->Write( message, category );
}

void Debug::WriteIf(bool condition, std::string_view message)
{
    Private::GetGlobalTracer()->WriteIf( condition, message );
}

void Debug::WriteIf(bool condition, std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->WriteIf( condition, message, category );
}

void Debug::WriteLine(std::string_view message)
{
    Private::GetGlobalTracer()->WriteLine( message );
}

void Debug::WriteLine(std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->WriteLine( message, category );
}

void Debug::WriteLineIf(bool condition, std::string_view message)
{
    Private::GetGlobalTracer()->WriteLineIf( condition, message );
}

void Debug::WriteLineIf(bool condition, std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->WriteLineIf( condition, message, category );
}

void Debug::Print(std::string_view message)
{
    Private::GetGlobalTracer()->WriteLine( message );
}

void Debug::Assert(bool condition, const std::source_location source_location)
{
#ifndef NDEBUG
    Private::GetGlobalTracer()->Assert( condition, source_location );
#else
    UNUSED(condition);
    UNUSED(source_location);
#endif
}

void Debug::Assert(bool condition, std::string_view message, const std::source_location source_location)
{
#ifndef NDEBUG
    Private::GetGlobalTracer()->Assert( condition, message, source_location );
#else
    UNUSED(condition);
    UNUSED(message);
    UNUSED(source_location);
#endif
}

void Debug::Assert(bool condition,
                   std::string_view message,
                   std::string_view detail_message,
                   const std::source_location source_location)
{
#ifndef NDEBUG
    Private::GetGlobalTracer()->Assert( condition, message, detail_message, source_location );
#else
    UNUSED(condition);
    UNUSED(message);
    UNUSED(category);
    UNUSED(source_location);
#endif
}

void Debug::Fail(std::string_view message)
{
    Private::GetGlobalTracer()->Fail( message );
}

void Debug::Fail(std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->Fail( message, category );
}

TraceListenerCollection &Debug::Listeners()
{
    return Private::GetGlobalTracer()->Listeners();
}

}
