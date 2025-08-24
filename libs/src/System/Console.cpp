module System;

#include "System/Console.hpp"
#include "System/IO/ConsoleStream.hpp"
#include "System/IO/StreamWriter.hpp"
#include "System/IO/StreamReader.hpp"
#include "System/Exception.hpp"



namespace System
{

static bool InputRedirected  = false;
static bool OutputRedirected = false;
static bool ErrorRedirected  = false;

static std::unique_ptr<IO::TextReader> &GetIn()
{
    // This is guaranteed to be a thread-safe initialization by a
    // standard-conforming compiler
    static std::unique_ptr<IO::TextReader> StdInTextReader{ std::make_unique<IO::StreamReader>( Console::OpenStandardInput() ) };

    return StdInTextReader;
}

static std::unique_ptr<IO::TextWriter> &GetOut()
{
    // This is guaranteed to be a thread-safe initialization by a
    // standard-conforming compiler
    static std::unique_ptr<IO::TextWriter> StdOutTextWriter{ std::make_unique<IO::StreamWriter>( Console::OpenStandardOutput() ) };
    
    return StdOutTextWriter;
}

static std::unique_ptr<IO::TextWriter> &GetError()
{
    // This is guaranteed to be a thread-safe initialization by a
    // standard-conforming compiler
    static std::unique_ptr<IO::TextWriter> StdErrTextWriter{ std::make_unique<IO::StreamWriter>( Console::OpenStandardError() ) };

    return StdErrTextWriter;
}

static std::unique_ptr<IO::TextWriter> &GetLog()
{
    // This is guaranteed to be a thread-safe initialization by a
    // standard-conforming compiler
    static std::unique_ptr<IO::TextWriter> StdLogTextWriter{ std::make_unique<IO::StreamWriter>( Console::OpenStandardLog() ) };

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

void Console::SetIn(std::unique_ptr<IO::TextReader> new_input_reader)
{
    using namespace std::literals;

    if ( !new_input_reader )
        ThrowWithTarget( ArgumentNullException{ "new_input_reader"sv } );

    GetIn() = std::move(new_input_reader);
    InputRedirected = true;

    // Check to see if we are really setting back to the original.  If so, undo the InputRedirected.
    IO::StreamReader *specific_type = dynamic_cast<IO::StreamReader *>( GetIn().get() );

    if ( specific_type )
    {
        if ( specific_type->BaseStream() )
        {
            IO::ConsoleStream *specific_stream_type = dynamic_cast<IO::ConsoleStream *>(specific_type->BaseStream());

            if ( specific_stream_type && (specific_stream_type->Type() == IO::ConsoleStream::In) )
                InputRedirected = false;
        }
    }
}

void Console::SetOut(std::unique_ptr<IO::TextWriter> new_output_writer)
{
    using namespace std::literals;

    if ( !new_output_writer )
        ThrowWithTarget( ArgumentNullException{ "new_output_writer"sv } );

    GetOut() = std::move(new_output_writer);
    OutputRedirected = true;

    // Check to see if we are really setting back to the original.  If so, undo the OutputRedirected.
    IO::StreamWriter *specific_type = dynamic_cast<IO::StreamWriter *>( GetOut().get() );

    if ( specific_type )
    {
        if ( specific_type->BaseStream() )
        {
            IO::ConsoleStream *specific_stream_type = dynamic_cast<IO::ConsoleStream *>(specific_type->BaseStream());

            if ( specific_stream_type && (specific_stream_type->Type() == IO::ConsoleStream::Out) )
                OutputRedirected = false;
        }
    }
}

void Console::SetError(std::unique_ptr<IO::TextWriter> new_output_writer)
{
    using namespace std::literals;

    if ( !new_output_writer )
        ThrowWithTarget( ArgumentNullException{ "new_output_writer"sv } );

    GetError() = std::move(new_output_writer);
    ErrorRedirected = true;

    // Check to see if we are really setting back to the original.  If so, undo the ErrorRedirected.
    IO::StreamWriter *specific_type = dynamic_cast<IO::StreamWriter *>( GetError().get() );

    if ( specific_type )
    {
        if ( specific_type->BaseStream() )
        {
            IO::ConsoleStream *specific_stream_type = dynamic_cast<IO::ConsoleStream *>(specific_type->BaseStream());

            if ( specific_stream_type && (specific_stream_type->Type() == IO::ConsoleStream::Error) )
                ErrorRedirected = false;
        }
    }
}

bool Console::IsInputRedirected()
{
    return InputRedirected;
}

bool Console::IsOutputRedirected()
{
    return OutputRedirected;
}

bool Console::IsErrorRedirected()
{
    return ErrorRedirected;
}

void Console::SetLog(std::unique_ptr<IO::TextWriter> new_input_writer)
{
    using namespace std::literals;

    if ( !new_input_writer )
        ThrowWithTarget( ArgumentNullException{ "new_input_writer"sv } );

    GetLog() = std::move(new_input_writer);
}

std::unique_ptr<IO::Stream> Console::OpenStandardInput()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::In);
}

std::unique_ptr<IO::Stream> Console::OpenStandardOutput()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Out);
}

std::unique_ptr<IO::Stream> Console::OpenStandardError()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Error);
}

std::unique_ptr<IO::Stream> Console::OpenStandardLog()
{
    return std::make_unique<IO::ConsoleStream>(IO::ConsoleStream::Log);
}

std::string Console::ReadLine()
{
    return In().ReadLine();
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

void Console::Write(std::string_view data)
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

void Console::WriteLine(std::string_view line)
{
    Out().WriteLine( line );
}

}