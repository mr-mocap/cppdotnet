#pragma once

#include "System/IO/TextWriter.hpp"

namespace System::IO
{

class Stream;

class StreamWriter : public TextWriter
{
public:
    StreamWriter();
    StreamWriter(std::string_view filename);
    StreamWriter(std::unique_ptr<Stream> stream)
        :
        _stream{ std::move(stream) }
    {
    }

   ~StreamWriter();

    void Close() override;
    void Flush() override;

    void Write(char value) override;
    void Write(std::string_view message) override;

    Stream *BaseStream() const { return _stream.get(); }
protected:
    std::unique_ptr<Stream> _stream;
};

}