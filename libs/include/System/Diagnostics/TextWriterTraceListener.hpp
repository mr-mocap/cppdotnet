#pragma once

#include "System/Diagnostics/TraceListener.hpp"
#include "System/IO/TextWriter.hpp"
#include "System/IO/Stream.hpp"
#include <memory>


namespace System::Diagnostics
{

class TextWriterTraceListener : public TraceListener
{
public:
    TextWriterTraceListener();
    TextWriterTraceListener(std::unique_ptr<System::IO::TextWriter> &&new_writer);
    TextWriterTraceListener(std::unique_ptr<System::IO::TextWriter> &&new_writer, const std::string_view name);
    TextWriterTraceListener(std::unique_ptr<System::IO::Stream> &&new_stream);
    TextWriterTraceListener(std::unique_ptr<System::IO::Stream> &&new_stream, const std::string_view name);

    void Close() override;
    void Flush() override;

    void Write(const std::string_view message) override;
    void Write(const std::string_view message, const std::string_view category) override;

    void WriteLine(const std::string_view message) override;
    void WriteLine(const std::string_view message, const std::string_view category) override;

    System::IO::TextWriter *Writer();
    
    void Fail(const std::string_view message) override;
    void Fail(const std::string_view message, const std::string_view detail) override;

    void WriteIndent() override;
protected:
    std::unique_ptr<System::IO::TextWriter> _text_writer;

    void WriteRaw(const std::string_view data);
    void WriteLineRaw(const std::string_view data);
};

}