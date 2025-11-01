#include <cppdotnet/System/Diagnostics/Private/DebugAndTraceCommon.hpp>
#include <cppdotnet/System/Diagnostics/TraceListener.hpp>
#include <cppdotnet/System/Diagnostics/TraceLevel.hpp>
#include <cppdotnet/System/Diagnostics/Debug.hpp>
#include <cstdlib>
#include <format>


static std::string FormatAssert(const std::source_location location)
{
    return std::format("[Assert] [File: \"{}\"] [Function: \"{}\"]", location.file_name(), location.function_name());
}

static std::string FormatAssertMessage(const std::source_location location, std::string_view message)
{
    return std::format("[Assert] [Message: \"{}\"]\t[File: \"{}\"]\t[Function: \"{}\"]", message, location.file_name(), location.function_name());
}

static std::string FormatAssertMessageCategory(const std::source_location location,
                                               std::string_view message,
                                               std::string_view category)
{
    return std::format("[Assert] [Category: \"{}\"]\t[Message: \"{}\"]\t[File: \"{}\"]\t[Function: \"{}\"]", category, message, location.file_name(), location.function_name());
}

static std::string FormatFailMessage(std::string_view message)
{
    return std::format("[Fail] [Message: \"{}\"]", message);
}

static std::string FormatFailMessageCategory(std::string_view message,
                                             std::string_view category)
{
    return std::format("[Fail] [Message: \"{}\"]\t[Category: \"{}\"]", message, category);
}

namespace System::Diagnostics::Private
{

bool ITracer::UseGlobalLock()
{
    return _useGlobalLock;
}

void ITracer::UseGlobalLock(bool new_value)
{
    _useGlobalLock = new_value;
}

void ITracer::WriteIf(bool condition, std::string_view message)
{
    if ( condition )
        Write( message );
}

void ITracer::WriteIf(bool condition, std::string_view message, std::string_view category)
{
    if ( condition )
        Write( message, category );
}

void ITracer::WriteLineIf(bool condition, std::string_view message)
{
    if ( condition )
        WriteLine( message );
}
void ITracer::WriteLineIf(bool condition, std::string_view message, std::string_view category)
{
    if ( condition )
        WriteLine( message, category );
}

GlobalTracer::GlobalTracer()
{
    _indentString.resize( _indentLevel * _indentSize, ' ' );

    // Potential memory leak! TODO: FIXME
    DefaultTraceListener *dtl = new DefaultTraceListener();

    Listeners().Add( dtl );
}

GlobalTracer::GlobalTracer(std::string_view name)
    :
    ITracer(name)
{
    _indentString.resize( _indentLevel * _indentSize, ' ' );

    // Potential memory leak! TODO: FIXME
    DefaultTraceListener *dtl = new DefaultTraceListener();

    Listeners().Add( dtl );
}

ITracer &GlobalTracer::Instance()
{
    static std::unique_ptr<GlobalTracer>  instance{ std::make_unique<GlobalTracer>() };

    return *instance;
}

int GlobalTracer::IndentLevel()
{
    return _indentLevel;
}

void GlobalTracer::IndentLevel(int new_value)
{
    if ( new_value != _indentLevel )
    {
        _indentLevel = std::max( new_value, 0 );
        _indentString.resize( _indentLevel * _indentSize, ' ' );
        // TODO: emit provider's OnIndentLevelChanged()
    }
}

int GlobalTracer::IndentSize()
{
    return _indentSize;
}

void GlobalTracer::IndentSize(int new_value)
{
    if ( new_value != _indentSize )
    {
        _indentSize = std::max( new_value, 0 );
        _indentString.resize( _indentLevel * _indentSize, ' ' );
        // TODO: emit provider's OnIndentSizeChanged()
    }
}

void GlobalTracer::Indent()
{
    IndentLevel( IndentLevel() + 1 );
}

void GlobalTracer::Unindent()
{
    IndentLevel( IndentLevel() - 1 );
}

bool GlobalTracer::AutoFlush()
{
    return _autoFlush;
}

void GlobalTracer::AutoFlush(bool new_value)
{
    _autoFlush = new_value;
}

void GlobalTracer::Flush()
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->Flush();
}

void GlobalTracer::Close()
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->Close();
}

void GlobalTracer::Write(std::string_view message)
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->Write( message );
    
    if ( AutoFlush() )
        Flush();
}

void GlobalTracer::Write(std::string_view message, std::string_view category)
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->Write( message, category );
    
    if ( AutoFlush() )
        Flush();
}

void GlobalTracer::WriteLine(std::string_view message)
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->WriteLine( message );
    
    if ( AutoFlush() )
        Flush();
}

void GlobalTracer::WriteLine(std::string_view message, std::string_view category)
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->WriteLine( message, category );
    
    if ( AutoFlush() )
        Flush();
}

void GlobalTracer::Assert(bool condition, const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssert(location) );
}

void GlobalTracer::Assert(bool condition,
                          std::string_view message,
                          const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssertMessage(location, message) );
}

void GlobalTracer::Assert(bool condition,
                          std::string_view message,
                          std::string_view detail_message,
                          const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssertMessageCategory(location, message, detail_message) );
}

void GlobalTracer::Fail(std::string_view message)
{
    WriteLine( FormatFailMessage( message ) );
}

void GlobalTracer::Fail(std::string_view message, std::string_view category)
{
    WriteLine( FormatFailMessageCategory( message, category ) );
}

bool GlobalTracer::NeedIndent()
{
    return ( IndentLevel() > 0) && ( IndentSize() > 0);
}

}