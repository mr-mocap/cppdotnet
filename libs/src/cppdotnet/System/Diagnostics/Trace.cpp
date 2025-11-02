#include <cppdotnet/System/Diagnostics/Trace.hpp>
#include <cppdotnet/System/Diagnostics/TraceLevel.hpp>
#include <cppdotnet/System/Diagnostics/Private/DebugAndTraceCommon.hpp>
#include <format>

static std::string FormatTraceType(System::Diagnostics::TraceLevel level, std::string_view message)
{
    return std::format("[{}] [Message: \"{}\"]", level, message);
}

namespace System::Diagnostics
{

int Trace::IndentLevel()
{
    return Private::GetGlobalTracer()->IndentLevel();
}

void Trace::IndentLevel(int new_value)
{
    Private::GetGlobalTracer()->IndentLevel( new_value );
}

int Trace::IndentSize()
{
    return Private::GetGlobalTracer()->IndentSize();
}

void Trace::IndentSize(int new_value)
{
    Private::GetGlobalTracer()->IndentSize( new_value );
}

bool Trace::AutoFlush()
{
    return Private::GetGlobalTracer()->AutoFlush();
}

void Trace::AutoFlush(bool new_value)
{
    Private::GetGlobalTracer()->AutoFlush( new_value );
}

void Trace::Write(std::string_view message)
{
    Private::GetGlobalTracer()->Write( message );
}

void Trace::Write(std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->Write( message, category );
}

void Trace::WriteIf(bool condition, std::string_view message)
{
    Private::GetGlobalTracer()->WriteIf(condition, message);
}

void Trace::WriteIf(bool condition,
                    std::string_view message,
                    std::string_view category)
{
    Private::GetGlobalTracer()->WriteIf(condition, message, category);
}

void Trace::WriteLine(std::string_view message)
{
    Private::GetGlobalTracer()->WriteLine( message );
}

void Trace::WriteLine(std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->WriteLine( message, category );
}

void Trace::WriteLineIf(bool condition, std::string_view message)
{
    Private::GetGlobalTracer()->WriteLineIf( condition, message );
}

void Trace::WriteLineIf(bool condition,
                        std::string_view message,
                        std::string_view category)
{
    Private::GetGlobalTracer()->WriteLineIf( condition, message, category );
}

void Trace::Assert(bool condition, const std::source_location location)
{
    Private::GetGlobalTracer()->Assert( condition, location );
}

void Trace::Assert(bool condition,
                   std::string_view message,
                   const std::source_location location)
{
    Private::GetGlobalTracer()->Assert( condition, message, location);
}

void Trace::Assert(bool condition,
                   std::string_view message,
                   std::string_view detail_message,
                   const std::source_location location)
{
    Private::GetGlobalTracer()->Assert( condition, message, detail_message, location);
}

void Trace::Fail(std::string_view message)
{
    Private::GetGlobalTracer()->Fail( message );
}

void Trace::Fail(std::string_view message, std::string_view category)
{
    Private::GetGlobalTracer()->Fail( message, category );
}

void Trace::TraceError(std::string_view message)
{
    Private::GetGlobalTracer()->WriteLine( FormatTraceType( TraceLevel::Error, message ) );
}

void Trace::TraceWarning(std::string_view message)
{
    Private::GetGlobalTracer()->WriteLine( FormatTraceType( TraceLevel::Warning, message ) );
}

void Trace::TraceInformation(std::string_view message)
{
    Private::GetGlobalTracer()->WriteLine( FormatTraceType( TraceLevel::Info, message ) );
}

void Trace::Flush()
{
    Private::GetGlobalTracer()->Flush();
}

void Trace::Close()
{
    Private::GetGlobalTracer()->Close();
}

void Trace::Indent()
{
    Private::GetGlobalTracer()->Indent();
}

void Trace::Unindent()
{
    Private::GetGlobalTracer()->Unindent();
}

TraceListenerCollection &Trace::Listeners()
{
    return Private::GetGlobalTracer()->Listeners();
}

}
