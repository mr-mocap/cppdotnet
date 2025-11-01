#include <cppdotnet/System/Diagnostics/Debug.hpp>
#include <cppdotnet/System/Diagnostics/Private/DebugAndTraceCommon.hpp>

namespace System::Diagnostics
{

void Debug::Close()
{
    Private::GlobalTracer::Instance().Close();
}

void Debug::Flush()
{
    Private::GlobalTracer::Instance().Flush();
}

bool Debug::AutoFlush()
{
    return Private::GlobalTracer::Instance().AutoFlush();
}

void Debug::AutoFlush(bool new_value)
{
    Private::GlobalTracer::Instance().AutoFlush( new_value );
}

int Debug::IndentLevel()
{
    return Private::GlobalTracer::Instance().IndentLevel();
}

void Debug::IndentLevel(int new_value)
{
    Private::GlobalTracer::Instance().IndentLevel( new_value );
}

int Debug::IndentSize()
{
    return Private::GlobalTracer::Instance().IndentSize();
}

void Debug::IndentSize(int new_value)
{
    Private::GlobalTracer::Instance().IndentSize( new_value );
}

void Debug::Indent()
{
    Private::GlobalTracer::Instance().Indent();
}

void Debug::Unindent()
{
    Private::GlobalTracer::Instance().Unindent();
}

void Debug::Write(std::string_view message)
{
    Private::GlobalTracer::Instance().Write( message );
}

void Debug::Write(std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().Write( message, category );
}

void Debug::WriteIf(bool condition, std::string_view message)
{
    Private::GlobalTracer::Instance().WriteIf( condition, message );
}

void Debug::WriteIf(bool condition, std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().WriteIf( condition, message, category );
}

void Debug::WriteLine(std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLine( message );
}

void Debug::WriteLine(std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().WriteLine( message, category );
}

void Debug::WriteLineIf(bool condition, std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLineIf( condition, message );
}

void Debug::WriteLineIf(bool condition, std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().WriteLineIf( condition, message, category );
}

void Debug::Print(std::string_view message)
{
    Private::GlobalTracer::Instance().WriteLine( message );
}

void Debug::Assert(bool condition, const std::source_location source_location)
{
#ifndef NDEBUG
    Private::GlobalTracer::Instance().Assert( condition, source_location );
#else
    UNUSED(condition);
    UNUSED(source_location);
#endif
}

void Debug::Assert(bool condition, std::string_view message, const std::source_location source_location)
{
#ifndef NDEBUG
    Private::GlobalTracer::Instance().Assert( condition, message, source_location );
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
    Private::GlobalTracer::Instance().Assert( condition, message, detail_message, source_location );
#else
    UNUSED(condition);
    UNUSED(message);
    UNUSED(category);
    UNUSED(source_location);
#endif
}

void Debug::Fail(std::string_view message)
{
    Private::GlobalTracer::Instance().Fail( message );
}

void Debug::Fail(std::string_view message, std::string_view category)
{
    Private::GlobalTracer::Instance().Fail( message, category );
}

TraceListenerCollection &Debug::Listeners()
{
    return Private::GlobalTracer::Instance().Listeners();
}

}
