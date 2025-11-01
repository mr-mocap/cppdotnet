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
    return Private::GlobalTracer::Instance().IndentLevel();
}

void Trace::IndentLevel(int new_value)
{
    Private::GlobalTracer::Instance().IndentLevel( new_value );
}

int Trace::IndentSize()
{
    return Private::GlobalTracer::Instance().IndentSize();
}

void Trace::IndentSize(int new_value)
{
    Private::GlobalTracer::Instance().IndentSize( new_value );
}

bool Trace::AutoFlush()
{
    return Private::GlobalTracer::Instance().AutoFlush();
}

void Trace::AutoFlush(bool new_value)
{
    Private::GlobalTracer::Instance().AutoFlush( new_value );
}

void Trace::Write(std::string_view message)
{
    Private::GlobalTracer::Instance().Write( message );
}

void Trace::Write(std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().Write( message, category );
}

void Trace::WriteIf(bool condition, std::string_view message)
{
    Private::GlobalTracer::Instance().WriteIf(condition, message);
}

void Trace::WriteIf(bool condition,
                    std::string_view message,
                    std::string_view category)
{
    Private::GlobalTracer::Instance().WriteIf(condition, message, category);
}

void Trace::WriteLine(std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLine( message );
}

void Trace::WriteLine(std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().WriteLine( message, category );
}

void Trace::WriteLineIf(bool condition, std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLineIf( condition, message );
}

void Trace::WriteLineIf(bool condition,
                        std::string_view message,
                        std::string_view category)
{
    Private::GlobalTracer::Instance().WriteLineIf( condition, message, category );
}

void Trace::Assert(bool condition, const std::source_location location)
{
    Private::GlobalTracer::Instance().Assert( condition, location );
}

void Trace::Assert(bool condition,
                   std::string_view message,
                   const std::source_location location)
{
    Private::GlobalTracer::Instance().Assert( condition, message, location);
}

void Trace::Assert(bool condition,
                   std::string_view message,
                   std::string_view detail_message,
                   const std::source_location location)
{
    Private::GlobalTracer::Instance().Assert( condition, message, detail_message, location);
}

void Trace::Fail(std::string_view message)
{
    Private::GlobalTracer::Instance().Fail( message );
}

void Trace::Fail(std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().Fail( message, category );
}

void Trace::TraceError(std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLine( FormatTraceType( TraceLevel::Error, message ) );
}

void Trace::TraceWarning(std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLine( FormatTraceType( TraceLevel::Warning, message ) );
}

void Trace::TraceInformation(std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLine( FormatTraceType( TraceLevel::Info, message ) );
}

void Trace::Flush()
{
    Private::GlobalTracer::Instance().Flush();
}

void Trace::Close()
{
    Private::GlobalTracer::Instance().Close();
}

void Trace::Indent()
{
    Private::GlobalTracer::Instance().Indent();
}

void Trace::Unindent()
{
    Private::GlobalTracer::Instance().Unindent();
}

TraceListenerCollection &Trace::Listeners()
{
    return Private::GlobalTracer::Instance().Listeners();
}

}
