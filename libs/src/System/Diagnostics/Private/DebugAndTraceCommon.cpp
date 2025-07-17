#include "System/Diagnostics/Private/DebugAndTraceCommon.hpp"
#include "System/Diagnostics/TraceListener.hpp"
#include "System/Diagnostics/TraceLevel.hpp"
#include "System/Diagnostics/Debug.hpp"
#include <cstdlib>
#include <format>


namespace System::Diagnostics::Private
{

int  DebugAndTraceCommon::_indentLevel = 0;
int  DebugAndTraceCommon::_indentSize  = 4;
bool DebugAndTraceCommon::_autoFlush   = false;
std::string DebugAndTraceCommon::_indentString;

static std::unique_ptr<DebugAndTraceCommon> &GetSingleton()
{
    static std::unique_ptr<DebugAndTraceCommon>  instance{ std::make_unique<DebugAndTraceCommon>() };

    return instance;
}

static std::string FormatTraceType(TraceLevel level, std::string_view message)
{
    return std::format("[{}] [Message: \"{}\"]", level, message);
}

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

DebugAndTraceCommon::DebugAndTraceCommon()
{
    _indentString.resize( _indentLevel * _indentSize, ' ' );

    // Potential memory leak! TODO: FIXME
    DefaultTraceListener *dtl = new DefaultTraceListener();

    Listeners().Add( dtl );
}

DebugAndTraceCommon::~DebugAndTraceCommon()
{
}

DebugAndTraceCommon &DebugAndTraceCommon::Instance()
{
    return *GetSingleton();
}

bool DebugAndTraceCommon::UseGlobalLock()
{
    return _useGlobalLock;
}

void DebugAndTraceCommon::UseGlobalLock(bool new_value)
{
    _useGlobalLock = new_value;
}

int DebugAndTraceCommon::IndentLevel()
{
    return _indentLevel;
}

void DebugAndTraceCommon::IndentLevel(int new_value)
{
    if ( new_value != _indentLevel )
    {
        _indentLevel = std::max( new_value, 0 );
        _indentString.resize( _indentLevel * _indentSize, ' ' );
        // TODO: emit provider's OnIndentLevelChanged()
    }
}

int DebugAndTraceCommon::IndentSize()
{
    return _indentSize;
}

void DebugAndTraceCommon::IndentSize(int new_value)
{
    if ( new_value != _indentSize )
    {
        _indentSize = std::max( new_value, 0 );
        _indentString.resize( _indentLevel * _indentSize, ' ' );
        // TODO: emit provider's OnIndentSizeChanged()
    }
}

void DebugAndTraceCommon::Indent()
{
    IndentLevel( IndentLevel() + 1 );
}

void DebugAndTraceCommon::Unindent()
{
    IndentLevel( IndentLevel() - 1 );
}

bool DebugAndTraceCommon::AutoFlush()
{
    return _autoFlush;
}

void DebugAndTraceCommon::AutoFlush(bool new_value)
{
    _autoFlush = new_value;
}

void DebugAndTraceCommon::Write(std::string_view message)
{
    bool autoflush = AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners() )
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->Write( message );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

void DebugAndTraceCommon::Write(std::string_view message, std::string_view category)
{
    bool autoflush = Instance().AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners() )
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->Write( message, category );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

void DebugAndTraceCommon::WriteLine(std::string_view message)
{
    bool autoflush = Instance().AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners() )
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->WriteLine( message );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

void DebugAndTraceCommon::WriteLine(std::string_view message, std::string_view category)
{
    bool autoflush = Instance().AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners() )
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->WriteLine( message, category );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

void DebugAndTraceCommon::WriteIf(bool condition, std::string_view message)
{
    if ( condition )
        Write( message );
}

void DebugAndTraceCommon::WriteIf(bool condition, std::string_view message, std::string_view category)
{
    if ( condition )
        Write( message, category );
}

void DebugAndTraceCommon::WriteLineIf(bool condition, std::string_view message)
{
    if ( condition )
        WriteLine( message );
}

void DebugAndTraceCommon::WriteLineIf(bool condition, std::string_view message, std::string_view category)
{
    if ( condition )
        WriteLine( message, category );
}

void DebugAndTraceCommon::Assert(bool condition, const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssert(location) );
}

void DebugAndTraceCommon::Assert(bool condition,
                                 std::string_view message,
                                 const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssertMessage(location, message) );
}

void DebugAndTraceCommon::Assert(bool condition,
                                 std::string_view message,
                                 std::string_view detail_message,
                                 const std::source_location location)
{
    // TODO: Output the call stack

    // For now, just print souce code info
    WriteLineIf( !condition, FormatAssertMessageCategory(location, message, detail_message) );
}

void DebugAndTraceCommon::Fail(std::string_view message)
{
    WriteLine( FormatFailMessage( message ) );
}

void DebugAndTraceCommon::Fail(std::string_view message, std::string_view category)
{
    WriteLine( FormatFailMessageCategory( message, category ) );
}

void DebugAndTraceCommon::Flush()
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->Flush();
}

void DebugAndTraceCommon::Close()
{
    for (auto iCurrentListener : Instance().Listeners() )
        iCurrentListener->Close();
}

void DebugAndTraceCommon::Print(std::string_view message)
{
    bool autoflush = AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners())
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->WriteLine( message );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

void DebugAndTraceCommon::TraceError(std::string_view message)
{
    bool autoflush = AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners())
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->WriteLine( FormatTraceType( TraceLevel::Error, message ) );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

void DebugAndTraceCommon::TraceWarning(std::string_view message)
{
    bool autoflush = AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners())
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->WriteLine( FormatTraceType( TraceLevel::Warning, message ) );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

void DebugAndTraceCommon::TraceInformation(std::string_view message)
{
    bool autoflush = AutoFlush();
    bool needindent = NeedIndent();

    for (auto iCurrentListener : Instance().Listeners())
    {
        if ( needindent )
            iCurrentListener->Write( _indentString );
        iCurrentListener->WriteLine( FormatTraceType( TraceLevel::Info, message ) );
        if ( autoflush )
            iCurrentListener->Flush();
    }
}

bool DebugAndTraceCommon::NeedIndent()
{
    return ( IndentLevel() > 0) && ( IndentSize() > 0);
}

}