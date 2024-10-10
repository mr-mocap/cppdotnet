#include "System/Console.hpp"
#include "System/IO/ConsoleStream.hpp"
#include "System/IO/StreamWriter.hpp"
#include <mutex>


namespace System
{

IO::TextWriter &Console::Out()
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

    return *StdOutTextWriter;
}

IO::TextWriter &Console::Error()
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

    return *StdErrTextWriter;
}

IO::TextWriter &Console::Log()
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

    return *StdLogTextWriter;
}

std::string Console::ReadLine()
{
    return {};
}

void Console::Write(bool value)
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

void Console::WriteLine(const std::string_view line)
{
    Out().WriteLine( line );
}

}