#include "System/Diagnostics/DefaultTraceListener.hpp"
#include "System/Diagnostics/Trace.hpp"
#include "System/Diagnostics/Debugger.hpp"
#include "System/Convert.hpp"
#include "System/Private/private.hpp"


namespace System::Diagnostics
{

DefaultTraceListener::DefaultTraceListener()
    :
    TraceListener("Default")
{
    INVARIANT( Name() == "Default" );
}

DefaultTraceListener::~DefaultTraceListener()
{
}

const std::string_view DefaultTraceListener::LogFileName() const
{
    INVARIANT( Name() == "Default" );

    return _logFileName;
}

void DefaultTraceListener::LogFileName(const std::string_view filename)
{
    INVARIANT( Name() == "Default" );

    _logFileName = filename;
}

void DefaultTraceListener::Close()
{
    INVARIANT( Name() == "Default" );
}

void DefaultTraceListener::Flush()
{
    INVARIANT( Name() == "Default" );
}

void DefaultTraceListener::Write(const std::string_view message)
{
    INVARIANT( Name() == "Default" );
    
    WriteRaw( message );
}

void DefaultTraceListener::Write(const std::string_view message, const std::string_view category)
{
    INVARIANT( Name() == "Default" );

    WriteRaw( std::string("[").append(category).append("] ").append(message) );
}

void DefaultTraceListener::WriteLine(const std::string_view message)
{
    INVARIANT( Name() == "Default" );

    WriteLineRaw( message );
}

void DefaultTraceListener::WriteLine(const std::string_view message, const std::string_view category)
{
    INVARIANT( Name() == "Default" );

    WriteLineRaw( std::string("[").append(category).append("] ").append(message) );
}

void DefaultTraceListener::Fail(const std::string_view message)
{
    INVARIANT( Name() == "Default" );

    WriteLineRaw( message );
}

void DefaultTraceListener::Fail(const std::string_view message, const std::string_view detail)
{
    INVARIANT( Name() == "Default" );

    WriteLineRaw( std::string("Fail: ").append(message).append(" [Detail: ").append(detail).append("]") );
}

void DefaultTraceListener::WriteRaw(const std::string_view data)
{
    INVARIANT( Name() == "Default" );

    UNUSED(data);

    Debugger::Log( data );
}

void DefaultTraceListener::WriteLineRaw(const std::string_view data)
{
    INVARIANT( Name() == "Default" );

    UNUSED(data);
    
    WriteIndent();
    WriteRaw( data );
    WriteRaw( "\n" );
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
