#include "System/Diagnostics/TextWriterTraceListener.hpp"
#include "System/Diagnostics/Debugger.hpp"
#include "System/Convert.hpp"
#include "System/IO/StreamWriter.hpp"
#include <format>


namespace System::Diagnostics
{

TextWriterTraceListener::TextWriterTraceListener()
{
}

TextWriterTraceListener::TextWriterTraceListener(std::unique_ptr<System::IO::TextWriter> &&new_writer)
    :
    _text_writer{ std::move(new_writer) }
{
}

TextWriterTraceListener::TextWriterTraceListener(std::unique_ptr<System::IO::TextWriter> &&new_writer,
                                                 const std::string_view name)
    :
    TraceListener( name ),
    _text_writer{ std::move(new_writer) }
{
}

TextWriterTraceListener::TextWriterTraceListener(std::unique_ptr<System::IO::Stream> &&new_stream)
    :
    _text_writer{ std::make_unique<System::IO::StreamWriter>( std::move(new_stream) ) }
{

}

TextWriterTraceListener::TextWriterTraceListener(std::unique_ptr<System::IO::Stream> &&new_stream,
                                                 const std::string_view name)
    :
    TraceListener( name ),
    _text_writer{ std::make_unique<System::IO::StreamWriter>( std::move(new_stream) ) }
{

}

void TextWriterTraceListener::Close()
{
    if ( _text_writer )
    {
        _text_writer->Close();
    }
}

void TextWriterTraceListener::Flush()
{
    if ( _text_writer )
    {
        _text_writer->Flush();
    }
}

void TextWriterTraceListener::Write(const std::string_view message)
{
    Debugger::Log( message );
    WriteRaw( message );
}

void TextWriterTraceListener::Write(const std::string_view message, const std::string_view category)
{
    Debugger::Log( message );
    WriteRaw( std::format("[{}] {}", category, message ) );
}

void TextWriterTraceListener::WriteLine(const std::string_view message)
{
    Debugger::Log( message );
    WriteIndent();
    WriteLineRaw( message );
    SetNeedIndent();
}

void TextWriterTraceListener::WriteLine(const std::string_view message, const std::string_view category)
{
    Debugger::Log( message );
    WriteIndent();
    WriteLineRaw( std::format("[{}] {}", category, message ) );
    SetNeedIndent();
}

System::IO::TextWriter *TextWriterTraceListener::Writer()
{
    return _text_writer.get();
}

void TextWriterTraceListener::Fail(const std::string_view message)
{
    WriteLineRaw( std::format("{}: {}", "Fail", message ) );
}

void TextWriterTraceListener::Fail(const std::string_view message, const std::string_view detail)
{
    WriteLineRaw( std::format("{}: {} [Detail: {}]", "Fail", message, detail) );
}

void TextWriterTraceListener::WriteRaw(const std::string_view data)
{
    if ( _text_writer )
        _text_writer->Write( data );
}

void TextWriterTraceListener::WriteLineRaw(const std::string_view data)
{
    if ( _text_writer )
        _text_writer->WriteLine( data );
}

void TextWriterTraceListener::WriteIndent()
{
    if ( _needIndent )
    {
        WriteRaw( _indentString );
        _needIndent = false;
    }
}

}