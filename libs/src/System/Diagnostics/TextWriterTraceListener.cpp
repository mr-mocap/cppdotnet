#include "System/Diagnostics/TextWriterTraceListener.hpp"
#include "System/Diagnostics/Debugger.hpp"
#include "System/Convert.hpp"
#include "System/IO/StreamWriter.hpp"


// TODO: Merge with DefaultTraceListener.cpp version
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
    WriteRaw( message );
}

void TextWriterTraceListener::Write(std::string_view message, std::string_view category)
{
    WriteRaw( GenerateMessage( message, category ) );
}

void TextWriterTraceListener::WriteLine(std::string_view message)
{
    WriteLineRaw( message );
}

void TextWriterTraceListener::WriteLine(std::string_view message, std::string_view category)
{
    WriteLineRaw( GenerateMessage( message, category ) );
}

System::IO::TextWriter *TextWriterTraceListener::Writer()
{
    return _text_writer.get();
}

void TextWriterTraceListener::Fail(std::string_view message)
{
    WriteLineRaw( GenerateFailMessage( message ) );
}

void TextWriterTraceListener::Fail(std::string_view message, std::string_view detail)
{
    WriteLineRaw( GenerateFailMessage( message, detail ) );
}

void TextWriterTraceListener::WriteRaw(std::string_view data)
{
    if ( _text_writer )
        _text_writer->Write( data );
}

void TextWriterTraceListener::WriteLineRaw(std::string_view data)
{
    if ( _text_writer )
    {
        _line_buffer.clear();

        // Write the indent if needed...
        if ( _needIndent )
            _line_buffer.append( _indentString );

        _text_writer->WriteLine( _line_buffer.append( data ) );
    }
}

void TextWriterTraceListener::WriteIndent()
{
    if ( _needIndent )
    {
        WriteRaw( _indentString );
    }
}

}