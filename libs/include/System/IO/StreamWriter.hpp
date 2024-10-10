#pragma once

#include "System/IO/TextWriter.hpp"
#include "System/IO/Stream.hpp"

namespace System::IO
{

class StreamWriter : public TextWriter
{
public:
    StreamWriter();
    StreamWriter(const std::string_view filename);
    StreamWriter(std::unique_ptr<Stream> &&stream);
   ~StreamWriter();

    void Close() override;
    void Flush() override;

    void Write(char value) override;
    void Write(const std::string_view message) override;

protected:
    std::unique_ptr<Stream> _stream;
};

}