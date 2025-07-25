#pragma once

#include "System/IO/TextReader.hpp"
#include <memory>
#include <string_view>

namespace System::IO
{

class Stream;

class StreamReader : public TextReader
{
public:
    StreamReader();
    StreamReader(std::string_view filename);
    StreamReader(std::unique_ptr<Stream> stream)
        :
        _stream{ std::move(stream) }
    {
    }

   ~StreamReader();

    void Close() override;

    int Read() override;

    std::string ReadLine() override;

    Stream *BaseStream() const { return _stream.get(); }
protected:
    std::unique_ptr<Stream> _stream;
};

}