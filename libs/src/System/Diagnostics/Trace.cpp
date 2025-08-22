#include "System/Diagnostics/Trace.hpp"
#include "System/Diagnostics/Private/DebugAndTraceCommon.hpp"


namespace System::Diagnostics
{

int Trace::IndentLevel()
{
    return Private::DebugAndTraceCommon::IndentLevel();
}

void Trace::IndentLevel(int new_value)
{
    Private::DebugAndTraceCommon::IndentLevel( new_value );
}

int Trace::IndentSize()
{
    return Private::DebugAndTraceCommon::IndentSize();
}

void Trace::IndentSize(int new_value)
{
    Private::DebugAndTraceCommon::IndentSize( new_value );
}

bool Trace::AutoFlush()
{
    return Private::DebugAndTraceCommon::AutoFlush();
}

void Trace::AutoFlush(bool new_value)
{
    Private::DebugAndTraceCommon::AutoFlush( new_value );
}

void Trace::Write(std::string_view message)
{
    Private::DebugAndTraceCommon::Write( message );
}

void Trace::Write(std::string_view message, std::string_view category)
{
    Private::DebugAndTraceCommon::Write( message, category );
}

void Trace::WriteIf(bool condition, std::string_view message)
{
    Private::DebugAndTraceCommon::WriteIf(condition, message);
}

void Trace::WriteIf(bool condition,
                    std::string_view message,
                    std::string_view category)
{
    Private::DebugAndTraceCommon::WriteIf(condition, message, category);
}

void Trace::WriteLine(std::string_view message)
{
    Private::DebugAndTraceCommon::WriteLine( message );
}

void Trace::WriteLine(std::string_view message, std::string_view category)
{
    Private::DebugAndTraceCommon::WriteLine( message, category );
}

void Trace::WriteLineIf(bool condition, std::string_view message)
{
    Private::DebugAndTraceCommon::WriteLineIf( condition, message );
}

void Trace::WriteLineIf(bool condition,
                        std::string_view message,
                        std::string_view category)
{
    Private::DebugAndTraceCommon::WriteLineIf( condition, message, category );
}

void Trace::Assert(bool condition, const std::source_location location)
{
    Private::DebugAndTraceCommon::Assert( condition, location );
}

void Trace::Assert(bool condition,
                   std::string_view message,
                   const std::source_location location)
{
    Private::DebugAndTraceCommon::Assert( condition, message, location);
}

void Trace::Assert(bool condition,
                   std::string_view message,
                   std::string_view detail_message,
                   const std::source_location location)
{
    Private::DebugAndTraceCommon::Assert( condition, message, detail_message, location);
}

void Trace::Fail(std::string_view message)
{
    Private::DebugAndTraceCommon::Fail( message );
}

void Trace::Fail(std::string_view message, std::string_view category)
{
    Private::DebugAndTraceCommon::Fail( message, category );
}

void Trace::TraceError(std::string_view message)
{
    Private::DebugAndTraceCommon::TraceError( message );
}

void Trace::TraceWarning(std::string_view message)
{
    Private::DebugAndTraceCommon::TraceWarning( message );
}

void Trace::TraceInformation(std::string_view message)
{
    Private::DebugAndTraceCommon::TraceInformation( message );
}

void Trace::Flush()
{
    Private::DebugAndTraceCommon::Flush();
}

void Trace::Close()
{
    Private::DebugAndTraceCommon::Close();
}

void Trace::Indent()
{
    Private::DebugAndTraceCommon::Indent();
}

void Trace::Unindent()
{
    Private::DebugAndTraceCommon::Unindent();
}

TraceListenerCollection &Trace::Listeners()
{
    return Private::DebugAndTraceCommon::Instance().Listeners();
}

}
