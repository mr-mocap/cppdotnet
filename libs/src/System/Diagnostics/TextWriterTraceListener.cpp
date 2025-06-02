#include "System/Diagnostics/TextWriterTraceListener.hpp"
#include "System/Diagnostics/Debugger.hpp"
#include "System/Convert.hpp"
#include "System/IO/StreamWriter.hpp"


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
                                                 std::string_view name)
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
                                                 std::string_view name)
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

void TextWriterTraceListener::Write(std::string_view message)
{
    Debugger::Log( message );
    WriteRaw( message );
}

void TextWriterTraceListener::Write(std::string_view message, std::string_view category)
{
    Debugger::Log( message );
    WriteRaw( std::string("[").append(category).append("] ").append(message) );
}

void TextWriterTraceListener::WriteLine(std::string_view message)
{
    Debugger::Log( message );
    WriteIndent();
    WriteLineRaw( message );
    SetNeedIndent();
}

void TextWriterTraceListener::WriteLine(std::string_view message, std::string_view category)
{
    Debugger::Log( message );
    WriteIndent();
    WriteLineRaw( std::string("[").append(category).append("] ").append(message) );
    SetNeedIndent();
}

System::IO::TextWriter *TextWriterTraceListener::Writer()
{
    return _text_writer.get();
}

void TextWriterTraceListener::Fail(std::string_view message)
{
    WriteLineRaw( std::string("Fail: ").append(message) );
}

void TextWriterTraceListener::Fail(std::string_view message, std::string_view detail)
{
    WriteLineRaw( std::string("Fail: ").append(message).append(" [Detail: ").append(detail).append("]") );
}

void TextWriterTraceListener::WriteRaw(std::string_view data)
{
    if ( _text_writer )
        _text_writer->Write( data );
}

void TextWriterTraceListener::WriteLineRaw(std::string_view data)
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