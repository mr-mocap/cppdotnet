#pragma once

#include "System/IO/TextReader.hpp"
#include "System/IO/Stream.hpp"

namespace System::IO
{

class StreamReader : public TextReader
{
public:
    StreamReader();
    StreamReader(const std::string_view filename);
    StreamReader(std::unique_ptr<Stream> &&stream);
   ~StreamReader();

    void Close() override;

    int Read() override;

    std::string ReadLine() override;

protected:
    std::unique_ptr<Stream> _stream;
};

}