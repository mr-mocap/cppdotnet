#include "System/Diagnostics/DefaultTraceListener.hpp"
#include "System/Diagnostics/Trace.hpp"
#include "System/Diagnostics/Debugger.hpp"
#include "System/IO/StreamWriter.hpp"
#include "System/Console.hpp"
#include "System/Convert.hpp"
#include "System/Private/private.hpp"
#include <format>


static std::string GenerateMessage(std::string_view message, std::string_view category)
{
    return std::format("[{}] {}", category, message);
}

static std::string GenerateFailMessage(std::string_view message, std::string_view detail)
{
    return std::format("[Fail] {} [{}]", message, detail);
}

static std::string GenerateFailMessage(std::string_view message)
{
    return std::format("[Fail] {}", message);
}

namespace System::Diagnostics
{

DefaultTraceListener::DefaultTraceListener()
    :
    TraceListener("Default"),
    _log_stream( std::make_unique<System::IO::StreamWriter>( Console::OpenStandardError() ) )
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    _line_buffer.reserve( 512 );
}

DefaultTraceListener::~DefaultTraceListener()
{
}

std::string_view DefaultTraceListener::LogFileName() const
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    return _logFileName;
}

void DefaultTraceListener::LogFileName(std::string_view filename)
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    _logFileName = filename;
    _log_stream = std::make_unique<System::IO::StreamWriter>( _logFileName );
}

void DefaultTraceListener::Close()
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    _log_stream->Close();
}

void DefaultTraceListener::Flush()
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    _log_stream->Flush();
}

void DefaultTraceListener::Write(std::string_view message)
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );
    
    WriteRaw( message );
}

void DefaultTraceListener::Write(std::string_view message, std::string_view category)
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    WriteRaw( GenerateMessage( message, category ) );
}

void DefaultTraceListener::WriteLine(std::string_view message)
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    WriteLineRaw( message );
}

void DefaultTraceListener::WriteLine(std::string_view message, std::string_view category)
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    WriteLineRaw( GenerateMessage( message, category ) );
}

void DefaultTraceListener::Fail(std::string_view message)
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    WriteLineRaw( GenerateFailMessage( message ) );
}

void DefaultTraceListener::Fail(std::string_view message, std::string_view detail)
{
    INVARIANT( Name() == "Default" );
    INVARIANT( _log_stream );

    WriteLineRaw( GenerateFailMessage( message, detail ) );
 }

void DefaultTraceListener::WriteRaw(std::string_view data)
{
    Debugger::Log( 1, "Default", data );
    _log_stream->Write( data );
}

void DefaultTraceListener::WriteLineRaw(std::string_view data)
{
    _line_buffer.clear();

    // Write the indent if needed...
    if ( _needIndent )
        _line_buffer.append( _indentString );

    _log_stream->WriteLine( _line_buffer.append( data ) );

    Debugger::Log( 1, "Default", _line_buffer );

    SetNeedIndent();
}

void DefaultTraceListener::WriteIndent()
{
    INVARIANT( Name() == "Default" );

    if ( _needIndent )
    {
        WriteRaw( _indentString );
        _needIndent = false;
    }
}

}
