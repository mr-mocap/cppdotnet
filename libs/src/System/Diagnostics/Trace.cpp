#include "System/Diagnostics/Trace.hpp"
#include "System/Diagnostics/DebugAndTraceCommon.hpp"


namespace System::Diagnostics
{

int Trace::IndentLevel()
{
    return DebugAndTraceCommon::IndentLevel();
}

void Trace::IndentLevel(int new_value)
{
    DebugAndTraceCommon::IndentLevel( new_value );
}

int Trace::IndentSize()
{
    return DebugAndTraceCommon::IndentSize();
}

void Trace::IndentSize(int new_value)
{
    DebugAndTraceCommon::IndentSize( new_value );
}

bool Trace::AutoFlush()
{
    return DebugAndTraceCommon::AutoFlush();
}

void Trace::AutoFlush(bool new_value)
{
    DebugAndTraceCommon::AutoFlush( new_value );
}

void Trace::Write(const std::string_view message)
{
    DebugAndTraceCommon::Write( message );
}

void Trace::Write(const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::Write( message, category );
}

void Trace::WriteIf(bool condition, const std::string_view message)
{
    DebugAndTraceCommon::WriteIf(condition, message);
}

void Trace::WriteIf(bool condition,
                    const std::string_view message,
                    const std::string_view category)
{
    DebugAndTraceCommon::WriteIf(condition, message, category);
}

void Trace::WriteLine(const std::string_view message)
{
    DebugAndTraceCommon::WriteLine( message );
}

void Trace::WriteLine(const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::WriteLine( message, category );
}

void Trace::WriteLineIf(bool condition, const std::string_view message)
{
    DebugAndTraceCommon::WriteLineIf( condition, message );
}

void Trace::WriteLineIf(bool condition,
                        const std::string_view message,
                        const std::string_view category)
{
    DebugAndTraceCommon::WriteLineIf( condition, message, category );
}

void Trace::Assert(bool condition, const std::source_location location)
{
    DebugAndTraceCommon::Assert( condition, location );
}

void Trace::Assert(bool condition,
                   const std::string_view message,
                   const std::source_location location)
{
    DebugAndTraceCommon::Assert( condition, message, location);
}

void Trace::Assert(bool condition,
                   const std::string_view message,
                   const std::string_view category,
                   const std::source_location location)
{
    DebugAndTraceCommon::Assert( condition, message, category, location);
}

void Trace::Fail(const std::string_view message)
{
    DebugAndTraceCommon::Fail( message );
}

void Trace::Fail(const std::string_view message, const std::string_view category)
{
    DebugAndTraceCommon::Fail( message, category );
}

void Trace::TraceError(const std::string_view message)
{
    DebugAndTraceCommon::TraceError( message );
}

void Trace::TraceWarning(const std::string_view message)
{
    DebugAndTraceCommon::TraceWarning( message );
}

void Trace::TraceInformation(const std::string_view message)
{
    DebugAndTraceCommon::TraceInformation( message );
}

void Trace::Flush()
{
    DebugAndTraceCommon::Flush();
}

void Trace::Close()
{
    DebugAndTraceCommon::Close();
}

void Trace::Indent()
{
    DebugAndTraceCommon::Indent();
}

void Trace::Unindent()
{
    DebugAndTraceCommon::Unindent();
}

TraceListenerCollection &Trace::Listeners()
{
    return DebugAndTraceCommon::Instance().Listeners();
}

}
