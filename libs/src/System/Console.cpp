#include "System/Console.hpp"
#include "System/IO/ConsoleStream.hpp"
#include "System/IO/StreamWriter.hpp"
#include "System/IO/StreamReader.hpp"
#include "System/Exception.hpp"
#include <mutex>


namespace System
{

static std::unique_ptr<IO::TextReader> &GetIn()
{
    static std::unique_ptr<IO::TextReader> StdInTextReader;
    static std::unique_ptr<std::once_flag> InOnceFlag = std::make_unique<std::once_flag>();

    std::call_once( *InOnceFlag,
                    []
                    {
                        StdInTextReader = std::make_unique<IO::StreamReader>(
                                                std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::In)
                                                                             );
                    } );

    return StdInTextReader;
}

static std::unique_ptr<IO::TextWriter> &GetOut()
{
    static std::unique_ptr<IO::TextWriter> StdOutTextWriter;
    static std::unique_ptr<std::once_flag> OutOnceFlag = std::make_unique<std::once_flag>();

    std::call_once( *OutOnceFlag,
                    []
                    {
                        StdOutTextWriter = std::make_unique<IO::StreamWriter>(
                                                std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Out)
                                                                             );
                    } );
    
    return StdOutTextWriter;
}

static std::unique_ptr<IO::TextWriter> &GetError()
{
    static std::unique_ptr<IO::TextWriter> StdErrTextWriter;
    static std::unique_ptr<std::once_flag> ErrOnceFlag = std::make_unique<std::once_flag>();

    std::call_once( *ErrOnceFlag,
                    []
                    {
                        StdErrTextWriter = std::make_unique<IO::StreamWriter>(
                                                std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Error)
                                                                             );
                    } );
    
    return StdErrTextWriter;
}

static std::unique_ptr<IO::TextWriter> &GetLog()
{
    static std::unique_ptr<IO::TextWriter> StdLogTextWriter;
    static std::unique_ptr<std::once_flag> LogOnceFlag = std::make_unique<std::once_flag>();

    std::call_once( *LogOnceFlag,
                    []
                    {
                        StdLogTextWriter = std::make_unique<IO::StreamWriter>(
                                                std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Log)
                                                                             );
                    } );

    return StdLogTextWriter;
}

IO::TextReader &Console::In()
{

    return *GetIn();
}

IO::TextWriter &Console::Out()
{

    return *GetOut();
}

IO::TextWriter &Console::Error()
{

    return *GetError();
}

IO::TextWriter &Console::Log()
{
    return *GetLog();
}

void Console::SetIn(std::unique_ptr<IO::TextReader> &&new_input_reader)
{
    using namespace std::literals;

    if ( !new_input_reader )
        ThrowWithTarget( ArgumentNullException{ "new_input_reader"sv } );

    GetIn() = std::move(new_input_reader);
}

void Console::SetOut(std::unique_ptr<IO::TextWriter> &&new_input_writer)
{
    using namespace std::literals;

    if ( !new_input_writer )
        ThrowWithTarget( ArgumentNullException{ "new_input_writer"sv } );

    GetOut() = std::move(new_input_writer);
}

void Console::SetError(std::unique_ptr<IO::TextWriter> &&new_input_writer)
{
    using namespace std::literals;

    if ( !new_input_writer )
        ThrowWithTarget( ArgumentNullException{ "new_input_writer"sv } );

    GetError() = std::move(new_input_writer);
}

void Console::SetLog(std::unique_ptr<IO::TextWriter> &&new_input_writer)
{
    using namespace std::literals;

    if ( !new_input_writer )
        ThrowWithTarget( ArgumentNullException{ "new_input_writer"sv } );

    GetLog() = std::move(new_input_writer);
}

std::unique_ptr<IO::ConsoleStream> Console::OpenStandardInput()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::In);
}

std::unique_ptr<IO::ConsoleStream> Console::OpenStandardOutput()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Out);
}

std::unique_ptr<IO::ConsoleStream> Console::OpenStandardError()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Error);
}

std::unique_ptr<IO::ConsoleStream> Console::OpenStandardLog()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Log);
}

std::string Console::ReadLine()
{
    return {};
}

void Console::Write(bool value)
{
    Out().Write( value );
}

void Console::Write(char value)
{
    Out().Write( value );
}

void Console::Write(int32_t value)
{
    Out().Write( value );
}

void Console::Write(uint32_t value)
{
    Out().Write( value );
}

void Console::Write(int64_t value)
{
    Out().Write( value );
}

void Console::Write(uint64_t value)
{
    Out().Write( value );
}

void Console::Write(float value)
{
    Out().Write( value );
}

void Console::Write(double value)
{
    Out().Write( value );
}

void Console::Write(const std::string_view data)
{
    Out().Write( data );
}

void Console::WriteLine()
{
    Out().Write( Out().NewLine() );
}

void Console::WriteLine(bool value)
{
    Out().WriteLine( value );
}

void Console::WriteLine(char value)
{
    Out().WriteLine( value );
}

void Console::WriteLine(int32_t value)
{
    Out().WriteLine( value );
}

void Console::WriteLine(uint32_t value)
{
    Out().WriteLine( value );
}

void Console::WriteLine(uint64_t value)
{
    Out().WriteLine( value );
}

void Console::WriteLine(float value)
{
    Out().WriteLine( value );
}

void Console::WriteLine(double value)
{
    Out().WriteLine( value );
}

void Console::WriteLine(const std::string_view line)
{
    Out().WriteLine( line );
}

}