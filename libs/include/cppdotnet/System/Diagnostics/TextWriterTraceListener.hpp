#pragma once

#include <cppdotnet/System/TypeCode.hpp>
#include <cppdotnet/System/Diagnostics/TraceListener.hpp>
#include <cppdotnet/System/IO/TextWriter.hpp>
#include <cppdotnet/System/IO/Stream.hpp>
#include <memory>


namespace System::Diagnostics
{

class TextWriterTraceListener : public TraceListener
{
public:
    TextWriterTraceListener();
    TextWriterTraceListener(std::unique_ptr<System::IO::TextWriter> new_writer)
        :
        _text_writer{ std::move(new_writer) }
    {
    }
    TextWriterTraceListener(std::unique_ptr<System::IO::TextWriter> new_writer, std::string_view name)
        :
        TraceListener( name ),
        _text_writer{ std::move(new_writer) }
    {
    }

    TextWriterTraceListener(std::unique_ptr<System::IO::Stream> new_stream);
    TextWriterTraceListener(std::unique_ptr<System::IO::Stream> new_stream, std::string_view name);
   ~TextWriterTraceListener() = default;

    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }

    void Close() override;
    void Flush() override;

    void Write(std::string_view message) override;
    void Write(std::string_view message, std::string_view category) override;

    void WriteLine(std::string_view message) override;
    void WriteLine(std::string_view message, std::string_view category) override;

    System::IO::TextWriter *Writer();
    
    void Fail(std::string_view message) override;
    void Fail(std::string_view message, std::string_view detail) override;

    void WriteIndent() override;
protected:
    std::unique_ptr<System::IO::TextWriter> _text_writer;
    std::string _line_buffer;

    void WriteRaw(std::string_view data);
    void WriteLineRaw(std::string_view data);
};

}