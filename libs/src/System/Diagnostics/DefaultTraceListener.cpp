#include "System/Diagnostics/DefaultTraceListener.hpp"
#include "System/Diagnostics/Trace.hpp"
#include "System/Diagnostics/Debugger.hpp"
#include "System/Convert.hpp"


namespace System::Diagnostics
{

DefaultTraceListener::DefaultTraceListener()
    :
    TraceListener("Default")
{
    Trace::Listeners().Add( this );
}

DefaultTraceListener::~DefaultTraceListener()
{
    Trace::Listeners().Remove( this );
}

const std::string_view DefaultTraceListener::LogFileName() const
{
    return _logFileName;
}

void DefaultTraceListener::LogFileName(const std::string_view filename)
{
    _logFileName = filename;
}

void DefaultTraceListener::Close()
{
}

void DefaultTraceListener::Flush()
{
}

void DefaultTraceListener::Write(const std::string_view message)
{
    Debugger::Log( message );
    WriteRaw( message );
}

void DefaultTraceListener::Write(const std::string_view message, const std::string_view category)
{
    Debugger::Log( message );
    WriteRaw( std::string("[").append(category).append("] ").append(message) );
}

void DefaultTraceListener::WriteLine(const std::string_view message)
{
    Debugger::Log( message );
    WriteIndent();
    WriteLineRaw( message );
    SetNeedIndent();
}

void DefaultTraceListener::WriteLine(const std::string_view message, const std::string_view category)
{
    Debugger::Log( message );
    WriteIndent();
    WriteLineRaw( std::string("[").append(category).append("] ").append(message) );
    SetNeedIndent();
}

void DefaultTraceListener::Fail(const std::string_view message)
{
    Debugger::Log( message );
    WriteLineRaw( message );
}

void DefaultTraceListener::Fail(const std::string_view message, const std::string_view detail)
{
    Debugger::Log( message );
    WriteLineRaw( std::string("Fail: ").append(message).append(" [Detail: ").append(detail).append("]") );
}

void DefaultTraceListener::WriteRaw(const std::string_view data)
{
}

void DefaultTraceListener::WriteLineRaw(const std::string_view data)
{
}

void DefaultTraceListener::WriteIndent()
{
    if ( _needIndent )
    {
        WriteRaw( _indentString );
        _needIndent = false;
    }
}

}
