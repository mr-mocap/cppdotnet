#include <cppdotnet/System/Diagnostics/Private/DebugAndTraceCommon.hpp>
#include <cppdotnet/System/Diagnostics/TraceListener.hpp>
#include <cppdotnet/System/Diagnostics/TraceLevel.hpp>
#include <cppdotnet/System/Diagnostics/Debug.hpp>
#include <cstdlib>
#include <format>
#include <mutex>


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

DefaultTracer::DefaultTracer()
{
    _indentString.resize( _indentLevel * _indentSize, ' ' );
}

DefaultTracer::DefaultTracer(std::string_view name)
    :
    ITracer(name)
{
    _indentString.resize( _indentLevel * _indentSize, ' ' );
}

int DefaultTracer::IndentLevel()
{
    return _indentLevel;
}

void DefaultTracer::IndentLevel(int new_value)
{
    if ( new_value != _indentLevel )
    {
        _indentLevel = std::max( new_value, 0 );
        _indentString.resize( _indentLevel * _indentSize, ' ' );
        // TODO: emit provider's OnIndentLevelChanged()
    }
}

int DefaultTracer::IndentSize()
{
    return _indentSize;
}

void DefaultTracer::IndentSize(int new_value)
{
    if ( new_value != _indentSize )
    {
        _indentSize = std::max( new_value, 0 );
        _indentString.resize( _indentLevel * _indentSize, ' ' );
        // TODO: emit provider's OnIndentSizeChanged()
    }
}

void DefaultTracer::Indent()
{
    IndentLevel( IndentLevel() + 1 );
    for (TraceListener *iCurrentListener : Listeners() )
        iCurrentListener->IndentLevel( IndentLevel() );
}

void DefaultTracer::Unindent()
{
    IndentLevel( IndentLevel() - 1 );
    for (TraceListener *iCurrentListener : Listeners() )
        iCurrentListener->IndentLevel( IndentLevel() );
}

bool DefaultTracer::AutoFlush()
{
    return _autoFlush;
}

void DefaultTracer::AutoFlush(bool new_value)
{
    _autoFlush = new_value;
}

void DefaultTracer::Flush()
{
    for (auto iCurrentListener : Listeners() )
        iCurrentListener->Flush();
}

void DefaultTracer::Close()
{
    for (auto iCurrentListener : Listeners() )
        iCurrentListener->Close();
}

void DefaultTracer::Write(std::string_view message)
{
    for (auto iCurrentListener : Listeners() )
        iCurrentListener->Write( message );
    
    if ( AutoFlush() )
        Flush();
}

void DefaultTracer::Write(std::string_view message, std::string_view category)
{
    for (auto iCurrentListener : Listeners() )
        iCurrentListener->Write( message, category );
    
    if ( AutoFlush() )
        Flush();
}

void DefaultTracer::WriteLine(std::string_view message)
{
    for (auto iCurrentListener : Listeners() )
        iCurrentListener->WriteLine( message );
    
    if ( AutoFlush() )
        Flush();
}

void DefaultTracer::WriteLine(std::string_view message, std::string_view category)
{
    for (auto iCurrentListener : Listeners() )
        iCurrentListener->WriteLine( message, category );
    
    if ( AutoFlush() )
        Flush();
}

void DefaultTracer::Assert(bool condition, const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssert(location) );
}

void DefaultTracer::Assert(bool condition,
                          std::string_view message,
                          const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssertMessage(location, message) );
}

void DefaultTracer::Assert(bool condition,
                          std::string_view message,
                          std::string_view detail_message,
                          const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssertMessageCategory(location, message, detail_message) );
}

void DefaultTracer::Fail(std::string_view message)
{
    WriteLine( FormatFailMessage( message ) );
}

void DefaultTracer::Fail(std::string_view message, std::string_view category)
{
    WriteLine( FormatFailMessageCategory( message, category ) );
}

bool DefaultTracer::NeedIndent()
{
    return ( IndentLevel() > 0) && ( IndentSize() > 0);
}

std::unique_ptr<ITracer> DefaultTracerFactory::CreateTracer()
{
    return std::make_unique<DefaultTracer>();
}

std::unique_ptr<ITracer> DefaultTracerFactory::CreateTracer(std::string_view name)
{
    return std::make_unique<DefaultTracer>( name );
}

static void DefaultSetupGlobalTracer()
{
    GlobalTracerFactoryInstancePtr = std::make_unique<DefaultTracerFactory>();
    GlobalTracerInstancePtr        = GlobalTracerFactoryInstancePtr->CreateTracer();

    GlobalTracerInstancePtr->Listeners().Add( std::make_unique<DefaultTraceListener>() );
}

void InitializeGlobalTracer(std::function<void()> init_function)
{
    if ( init_function )
        init_function();
    else
        DefaultSetupGlobalTracer();
}

ITracer *GetGlobalTracer()
{
    static std::once_flag initFlag;

    std::call_once( initFlag, InitializeGlobalTracer, GlobalTracerInitFunction );
    return GlobalTracerInstancePtr.get();
}

std::unique_ptr<ITracerFactory> GlobalTracerFactoryInstancePtr;
std::unique_ptr<ITracer>        GlobalTracerInstancePtr;
std::function<void()>           GlobalTracerInitFunction;

}